#include "Quad.h"
#include <glut.h>

Quad::Quad()
{
	for (int i = 0; i < 4; i++)
	{
		_corners[i] = Point();
	}
}

Quad::Quad(const Colour& colour, const Point corners[4], bool outlined, const Colour& outlineColour) :
	_colour(colour),
	_outlined(outlined)
{
	if (_outlined)
	{
		_outline = new Outline(corners, 4, outlineColour);
	}
	else
	{
		_outline = nullptr;
	}
	for (int i = 0; i < 4; i++)
	{
		_corners[i] = corners[i];
	}
}

Quad::Quad(const Quad& copy) :
	_outline(copy._outline),
	_colour(copy._colour),
	_outlined(copy._outlined)
{
	for (int i = 0; i < 4; i++)
	{
		_corners[i] = copy._corners[i];
	}
}

Quad::~Quad()
{
	if (_outlined and _outline != nullptr)
	{
		delete _outline;
	}
}

Quad& Quad::operator=(const Quad& copy)
{
	for (int i = 0; i < 4; i++)
	{
		_corners[i] = copy._corners[i];
	}
	_colour = copy._colour;
	_outlined = copy._outlined;
	_outline = new Outline(const_cast<Point*>(copy._corners), 4, copy._outlineColour);
	*_outline = *copy._outline;
	return *this;
}

void Quad::enableOutline(const Colour& colour, double outlineWidth)
{
	_outlined = true;
	_outline = new Outline(_corners, 4, colour);
	_outline->setColour(colour);
	_outline->setWidth(outlineWidth);
}

void Quad::disableOutline()
{
	_outlined = false;
	delete _outline;
	_outline = nullptr;
}

void Quad::setOutlineColour(const Colour& outlineColour)
{
	if (_outlined)
	{
		_outline->setColour(outlineColour);
	}
}

void Quad::setOutlineWidth(double outlineWidth)
{
	if (_outlined)
	{
		_outline->setWidth(outlineWidth);
	}
}

void Quad::draw(double zoom) const
{
	if (_outlined)
	{
		_outline->draw(zoom);
	}

	glBegin(GL_QUADS);
	setRenderColour(_colour);

	for (int i = 0; i < 4; i++)
	{
		_corners[i].draw();
	}

	glEnd();
}

void Quad::setColour(const Colour& colour)
{
	_colour = colour;
}

void Quad::setColour(double red, double green, double blue)
{
	_colour.setRed(red);
	_colour.setGreen(green);
	_colour.setBlue(blue);
}

void Quad::setColour(int red, int green, int blue)
{
	_colour.setRed(red);
	_colour.setGreen(green);
	_colour.setBlue(blue);
}