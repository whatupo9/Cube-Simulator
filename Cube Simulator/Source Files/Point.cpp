#include <corecrt_math_defines.h>
#include <glut.h>
#include "Cube Constants.h"
#include "Point.h"

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

double degreesToRadians(double degrees)
{
	return degrees * M_PI / 180.0;
}

void rotatePoint(Point* point, const Point& centre, double degrees, int axis)
{
	double x = point->getX();
	double y = point->getY();
	double z = point->getZ();

	double cx = centre.getX();
	double cy = centre.getY();
	double cz = centre.getZ();

	double theta = degreesToRadians(degrees);

	// Translation to center point
	x -= cx;
	y -= cy;
	z -= cz;

	double cosTheta = cos(theta);
	double sinTheta = sin(theta);

	double newX;
	double newY;
	double newZ;

	switch (axis)
	{
	case 0:
		newX = x;
		newY = cosTheta * y - sinTheta * z;
		newZ = sinTheta * y + cosTheta * z;
		break;
	case 1:
		newX = cosTheta * x + sinTheta * z;
		newY = y;
		newZ = -sinTheta * x + cosTheta * z;
		break;
	case 2:
		newX = cosTheta * x - sinTheta * y;
		newY = sinTheta * x + cosTheta * y;
		newZ = z;
		break;
	default:
		return;
	}

	// Translation back from center point
	x = newX + cx;
	y = newY + cy;
	z = newZ + cz;

	point->setX(x);
	point->setY(y);
	point->setZ(z);
}

void snapPointToGrid(Point* point, double interval)
{
	if (interval > 0)
	{
		point->setX(round(point->getX() / interval) * interval);
		point->setY(round(point->getY() / interval) * interval);
		point->setZ(round(point->getZ() / interval) * interval);
	}
}