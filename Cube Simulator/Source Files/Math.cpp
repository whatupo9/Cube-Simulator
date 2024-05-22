#include "Math.h"

int rotations;
int corners;

double degreesToRadians(double degrees)
{
	return degrees * M_PI / 180.0;
}

void rotatePoint(double& x, double& y, double degrees, double centreX, double centreY)
{
	double theta = degreesToRadians(degrees);
	x = centreX + (x - centreX) * std::cos(theta) - (y - centreY) * std::sin(theta);
	y = centreY + (x - centreX) * std::sin(theta) + (y - centreY) * std::cos(theta);
}

void rotatePoint(double& x, double& y, double& z, double cx, double cy, double cz, double degrees, int axis)
{
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
}