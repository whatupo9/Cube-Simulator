#include "Outline.h"

#include <glut.h>

Outline::Outline() :
	_pointsNum(0)
{
	_points.clear();
	_points.resize(0);
}

Outline::Outline(const Point* const* const points, int pointsNum, const Colour& colour, const double* outlineWidth) :
	_pointsNum(pointsNum),
	_colour(colour)
{
	if (outlineWidth)
	{
		_outlineWidth = *outlineWidth;
	}

	_points.resize(pointsNum);
	for (int i = 0; i < pointsNum; i++)
	{
		_points[i] = points[i];
	}
}

void Outline::draw(double zoom) const
{
	setRenderColour(_colour);
	glLineWidth(float(_outlineWidth / -zoom));
	glBegin(GL_LINES);

	for (int i = 0; i < _pointsNum - 1; i++)
	{
		_points[i]->draw();
		_points[i + 1]->draw();
	}
	_points[0]->draw();
	_points[_pointsNum - 1]->draw();
	glEnd();
}

void Outline::setColour(const Colour* colour)
{
	if (colour)
	{
		_colour = *colour;
	}
}

void Outline::setWidth(const double* outlineWidth)
{
	_outlineWidth = *outlineWidth;
}