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
{
}

Point::Point(int x, int y, int z) :
	_x(double(x)),
	_y(double(y)),
	_z(double(z))
{
}

Point::Point(double x, double y, double z) :
	_x(x),
	_y(y),
	_z(z)
{
}

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

double Point::getPoint(int axis) const
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

void Point::draw() const
{
	glVertex3d(_x, _y, _z);
}

void Point::rotate(const Point& centre, double degrees, int axis)
{
	rotatePoint(_x, _y, _z, centre.getX(), centre.getY(), centre.getZ(), degrees, axis);
}

void Point::snapToGrid(double interval)
{
	if (interval > 0)
	{
		_x = round(_x / interval) * interval;
		_y = round(_y / interval) * interval;
		_z = round(_z / interval) * interval;
	}
}