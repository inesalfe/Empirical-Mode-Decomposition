CC := g++
CCFLAGS := -std=c++11
INC := -I src

ROOTINC = $(shell root-config --cflags)
ROOTLIB = $(shell root-config --libs)

VPATH = src/:.

SRC = $(notdir $(wildcard src/*.C))
OBJ = $(addprefix bin/, $(SRC:.C=.o))
HHH = $(wildcard src/*.h)
MAIN := $(notdir $(wildcard *.C))
EXE := $(addprefix bin/, $(MAIN:.C=.exe))

all: allexe allobj

allexe: $(EXE)
allobj: $(OBJS)

obj: $(OBJ)

main: bin/main.o bin/main.exe

# --- now I need to make the rules to compile and link

bin/%.exe: bin/%.o $(OBJ)
	@echo "making executable $^... [$@]"
	$(CC) $(CCFLAGS) -o $@ $< $(INC) $(OBJ) $(ROOTINC) $(ROOTLIB) -g -Wall

bin/%.o: %.C
	@echo "compiling $<... [$@]"
	$(CC) $(CCFLAGS) -c -o $@ $< $(INC) $(ROOTINC) -g

clean:
	rm -fv bin/*.o bin/*.exe

test:
	@echo "Test 1"
	@echo $(ROOTINC)
	@echo $(INC)
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(SRCSPROG) $(EXE)

run:
	./bin/main.exe
