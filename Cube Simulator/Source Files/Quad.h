#ifndef QUAD_H
#define QUAD_H
#define NULL 0

#include "Point.h"
#include "Colour.h"
#include "Outline.h"

class Quad
{
	Point _corners[4];
	Outline* _outline = nullptr;
	Colour _colour;
	Colour _outlineColour;
	bool _outlined = false;

public:

	Quad();

	Quad(const Colour& colour, const Point corners[4], bool outlined = false, const Colour& outlineColour = Colour());

	Quad(const Quad& copy);

	~Quad();

	Quad& operator=(const Quad& copy);

	void enableOutline(const Colour& colour = Colour(), double outlineWidth = OUTLINE_WIDTH);

	void disableOutline();

	void setOutlineColour(const Colour& outlineColour);

	void setOutlineWidth(double outlineWidth);

	void draw(double zoom) const;

	void setColour(const Colour& colour);

	void setColour(double red, double green, double blue);

	void setColour(int red, int green, int blue);
};

#endif // !QUAD_H