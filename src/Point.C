#include "Point.h"
#include <iostream>
using namespace std;

Point::Point (double x_in, double y_in) {
	x = x_in;
	y = y_in;
}

Point::Point (const Point& Obj) {
	x = Obj.x;
	y = Obj.y;
}

double Point::X() const {
	return x;
}

double Point::Y() const {
	return y;
}

double& Point::X() {
	return x;
}

double& Point::Y() {
	return y;
}

bool Point::operator==(const Point& a) const {
	if ((x == a.X()) && (y == a.Y()))
		return true;
	else
		return false;
}

bool Point::operator!=(const Point& a) const {
	if ((x == a.X()) && (y == a.Y()))
		return false;
	else
		return true;
}

Point& Point::operator=(const Point& a) {
	x = a.X();
	y = a.Y();

	return *this;
}

Point Point::operator-(const Point& a) const {
	return Point(x - a.X(),y - a.Y());
}

Point Point::operator+(const Point& a) const {
	return Point(x + a.X(),y + a.Y());
}

Point& Point::operator-=(const Point& a) {
	x -= a.X();
	y -= a.Y();

	return *this;
}

Point& Point::operator+=(const Point& a) {
	x += a.X();
	y += a.Y();

	return *this;
}

Point Point::operator*(const Point& a) const {
	return Point(x*a.X(),y*a.Y());
}
Point Point::operator*(const double b) const {
	return Point(x*b,y*b);
}

Point operator*(double b, Point& a) {
	return a*b;
}

Point Point::operator-() {
	return Point(-x,-y);
}

void Point::Print() const {
	cout << "( " << x << " , " << y << " )" << endl;
}
