#ifndef __POINT__
#define __POINT__

class Point {

public:
	Point(double x_in = 0, double y_in = 0);
	Point(const Point&);
	~Point() {;}

	double X() const;
	double Y() const;

	double& X();
	double& Y();

	Point& operator=(const Point&);

	Point operator-(const Point&) const;
	Point operator+(const Point&) const;
	Point& operator-=(const Point&);
	Point& operator+=(const Point&);

	Point operator*(const Point&) const;
	Point operator*(const double) const;
	friend Point operator*(double, Point&);

	Point operator-();

	bool operator==(const Point&) const;
	bool operator!=(const Point&) const;

	void Print() const;

private:
	double x;
	double y;
};


#endif
