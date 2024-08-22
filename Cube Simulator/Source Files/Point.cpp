#include "Point.h"

#include <glut.h>

double& Point::operator[](const int index)
{
	if (index == 0)
		return _x;
	if (index == 1)
		return _y;
	if (index == 2)
		return _z;
}

Point Point::operator+(const Point& addend) const
{
	Point newPoint;
	newPoint._x = _x + addend._x;
	newPoint._y = _y + addend._y;
	newPoint._z = _z + addend._z;
	return newPoint;
}

void Point::operator+=(const Point& addend)
{
	_x += addend._x;
	_y += addend._z;
	_z += addend._z;
}

Point Point::operator-(const Point& subtrahend) const
{
	Point newPoint;
	newPoint._x = _x - subtrahend._x;
	newPoint._y = _y - subtrahend._y;
	newPoint._z = _z - subtrahend._z;
	return newPoint;
}

Point::Point() :
	_x(0),
	_y(0),
	_z(0)
{}

Point::Point(int x, int y, int z) :
	_x(double(x)),
	_y(double(y)),
	_z(double(z))
{}

Point::Point(double x, double y, double z) :
	_x(x),
	_y(y),
	_z(z)
{}

Point::Point(const Point* copy)
{
	if (copy)
	{
		_x = copy->_x;
		_y = copy->_y;
		_z = copy->_z;
	}
	else
	{
		*this = Point();
	}
}

void Point::setX(double x)
{
	_x = x;
}

void Point::setX(int x)
{
	_x = double(x);
}

void Point::setY(double y)
{
	_y = y;
}

void Point::setY(int y)
{
	_y = double(y);
}

void Point::setZ(double z)
{
	_z = z;
}

void Point::setZ(int z)
{
	_z = double(z);
}

double Point::getX() const
{
	return _x;
}

double Point::getY() const
{
	return _y;
}

double Point::getZ() const
{
	return _z;
}

double Point::getCoordinate(int axis) const
{
	if (axis == X_AXIS)
	{
		return _x;
	}
	if (axis == Y_AXIS)
	{
		return _y;
	}
	if (axis == Z_AXIS)
	{
		return _z;
	}
	return 0;
}

void drawPoint(const Point* point)
{
	glVertex3d(point->getX(), point->getY(), point->getZ());
}

void rotatePoint(Point& point, const Point& centre, double degrees, int axis)
{
	double theta = degreesToRadians(degrees);
	point.setX(centre.getX() + (point.getX() - centre.getX()) * std::cos(theta) - (point.getY() - centre.getY()) * std::sin(theta));
	point.setY(centre.getY() + (point.getX() - centre.getX()) * std::sin(theta) + (point.getY() - centre.getY()) * std::cos(theta));
}

void snapPointToGrid(Point& point, double interval)
{
	if (interval > 0)
	{
		point.setX(round(point.getX() / interval) * interval);
		point.setY(round(point.getY() / interval) * interval);
		point.setZ(round(point.getZ() / interval) * interval);
	}
}