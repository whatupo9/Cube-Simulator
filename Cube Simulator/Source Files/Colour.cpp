#include "Colour.h"
#include "Cube Constants.h"
#include "Math.h"

#include <glut.h>

Colour::Colour() :
	_red(0.0f),
	_green(0.0f),
	_blue(0.0f)
{
}

Colour::Colour(float red, float green, float blue) :
	_red(clamp(red, 0.0f, 1.0f)),
	_green(clamp(green, 0.0f, 1.0f)),
	_blue(clamp(blue, 0.0f, 1.0f))
{
}

Colour::Colour(int red, int green, int blue)
{
	float newRed = float(red) / MAX_COLOUR;
	clamp(newRed, 0.0f, 1.0f);
	_red = newRed;

	float newGreen = float(green) / MAX_COLOUR;
	clamp(newGreen, 0.0f, 1.0f);
	_green = newGreen;

	float newBlue = float(blue) / MAX_COLOUR;
	clamp(newBlue, 0.0f, 1.0f);
	_blue = newBlue;
}

Colour::Colour(const Colour* copy)
{
	if (copy)
	{
		_red = copy->_red;
		_green = copy->_green;
		_blue = copy->_blue;
	}
	else
	{
		*this = Colour();
	}
}

void Colour::setColour(const Colour* colour)
{
	_red = colour->getRed();
	clamp(_red, 0.0f, 1.0f);
	_green = colour->getGreen();
	clamp(_green, 0.0f, 1.0f);
	_blue = colour->getBlue();
	clamp(_blue, 0.0f, 1.0f);
}

float Colour::getRed() const
{
	return _red;
}

float Colour::getGreen() const
{
	return _green;
}

float Colour::getBlue() const
{
	return _blue;
}

void setRenderColour(const Colour& colour)
{
	glColor3f(colour.getRed(), colour.getGreen(), colour.getBlue());
}