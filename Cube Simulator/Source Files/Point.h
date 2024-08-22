#ifndef POINT_H
#define POINT_H

#include "Math.h"
#include "Cube Constants.h"

class Point
{
	double _x;
	double _y;
	double _z;

	double& operator[](const int index);

public:
	Point operator+(const Point& addend) const;

	void operator+=(const Point& addend);

	Point operator-(const Point& subtrahend) const;

	Point();

	Point(int x, int y, int z);

	Point(double x, double y, double z);

	explicit Point(const Point* copy);

	void setX(double x);

	void setX(int x);

	void setY(double y);

	void setY(int y);

	void setZ(double z);

	void setZ(int z);

	double getX() const;

	double getY() const;

	double getZ() const;

	double getCoordinate(int axis) const;
};

void drawPoint(const Point* point);

void rotatePoint(Point* point, const Point& centre, double degrees, int axis);

void snapPointToGrid(Point* point, double interval = 1.0);

#endif // !POINT_H