#include "Square.h"

#include <glut.h>

Square::Square() :
	_width(1.0f),
	_managingCorners(true)
{
	_corners[0] = new Point(1, 1, 0);
	_corners[1] = new Point(1, -1, 0);
	_corners[2] = new Point(-1, -1, 0);
	_corners[3] = new Point(-1, 1, 0);
}

Square::Square(Point** const corners, double width, const Colour& colour, const Colour* const outlineColour, const double* outlineWidth)
	:
	_colour(colour),
	_width(width),
	_managingCorners(false)
{
	for (int i = 0; i < 4; i++)
		_corners[i] = corners[i];

	if (outlineColour)
	{
		_outlineColour = new Colour(*outlineColour);
		if (outlineWidth)
		{
			_outlineWidth = new double(*outlineWidth);
		}
		auto CONST_CORNERS = const_cast<const Point** const>(corners);
		_outline = new Outline(CONST_CORNERS, 4, *outlineColour, outlineWidth);
	}
	else
	{
		_outline = nullptr;
	}
}

Square::Square(const Square& copy) :
	_centre(copy._centre),
	_colour(copy._colour),
	_width(copy._width),
	_managingCorners(copy._managingCorners)
{
	for (int i = 0; i < 4; i++)
	{
		if (_managingCorners)
		{
			_corners[i] = new Point(*copy._corners[i]);
		}
		else
		{
			_corners[i] = copy._corners[i];
		}
	}

	if (copy._outlineColour)
	{
		_outlineColour = new Colour(*copy._outlineColour);
		if (_outlineWidth)
		{
			_outlineWidth = new double(*copy._outlineWidth);
		}
		_outline = new Outline(copy._corners._Elems, 4, *copy._outlineColour, copy._outlineWidth);
	}
	else
	{
		_outlineColour = nullptr;
		_outline = nullptr;
	}
}

Square::~Square()
{
	if (_outline)
		delete _outline;

	if (_outlineColour)
		delete _outlineColour;

	if (_outlineWidth)
		delete _outlineWidth;

	if (_managingCorners)
		for (int i = 0; i < 4; i++)
			delete _corners[i];
}

Square& Square::operator=(const Square& copy)
{
	_managingCorners = copy._managingCorners;
	_colour = copy._colour;

	for (int i = 0; i < 4; i++)
	{
		if (_managingCorners)
		{
			_corners[i] = new Point(*copy._corners[i]);
		}
		else
		{
			_corners[i] = copy._corners[i];
		}
	}

	if (copy._outline)
	{
		_outlineColour = new Colour(*copy._outlineColour);
		_outlineWidth = new double(copy._outlineWidth ? *copy._outlineWidth : OUTLINE_WIDTH);
		_outline = new Outline(copy._corners._Elems, 4, *copy._outlineColour, copy._outlineWidth);
	}
	return *this;
}

void Square::startRotation(RotationManager& manager, int axis, bool clockwise, const Point& centre)
{
	for (int i = 0; i < 4; i++)
	{
		manager.addRotation(_corners[i], centre, axis, 90.0, clockwise, ANIMATION_LENGTH);
	}
}

void Square::updateOutline()
{
	if (_outline)
	{
		_outline->setPoints<4>(_corners);
		_outline->setColour(_outlineColour);
		_outline->setWidth(_outlineWidth);
	}
}

void Square::draw(double zoom)
{
	if (_outline)
	{
		_outline->draw(zoom);
	}

	glBegin(GL_QUADS);
	setRenderColour(_colour);

	for (int i = 0; i < 4; i++)
	{
		_corners[i]->draw();
	}

	glEnd();
}

void Square::setColour(const Colour& colour)
{
	_colour = colour;
}