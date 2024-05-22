#ifndef SQUARE_H
#define SQUARE_H

#include <array>
#include "Outline.h"
#include "RotationManager.h"

const std::array<Point, 4> DEFAULT_SQUARE_CORNERS =
{ {
	Point(1, 0, 0),
	Point(1, 1, 0),
	Point(0, 1, 0),
	Point(0, 0, 0)
} };

class Square
{
	std::array<Point*, 4> _corners;
	Point _centre;
	Colour _colour;
	Outline* _outline = nullptr;
	Colour* _outlineColour = nullptr;

	double _width;
	double* _outlineWidth = nullptr;
	bool _rotating = false;
	bool _managingCorners;

public:

	Square();

	Square(Point** const corners, double width, const Colour& colour, const Colour* const outlineColour = nullptr, const double* outlineWidth = nullptr);

	Square(const Square& copy);

	~Square();

	Square& operator=(const Square& copy);

	void startRotation(RotationManager& manager, int axis, bool clockwise = true, const Point& centre = Point());

	void updateOutline();

	void draw(double zoom);

	void setColour(const Colour& colour);
};

#endif // !SQUARE_H