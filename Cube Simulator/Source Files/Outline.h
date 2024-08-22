#ifndef OUTLINE_H
#define OUTLINE_H

#include "Point.h"
#include "Colour.h"
#include <array>
#include <vector>

class Outline
{
	std::vector<const Point*> _points;
	int _pointsNum;
	Colour _colour;
	double _outlineWidth = OUTLINE_WIDTH;

public:

	Outline();

	Outline(const Point* const* const points, int pointsNum, const Colour& colour, const double* outlineWidth = nullptr);

	void draw(double zoom) const;

	void setColour(const Colour* colour);

	void setWidth(const double* outlineWidth);

	template<size_t SIZE>
	void setPoints(std::array<Point*, SIZE> points)
	{
		_pointsNum = SIZE;
		for (int i = 0; i < SIZE; i++)
		{
			_points[i] = points[i];
		}
	}
};

#endif // !OUTLINE_H