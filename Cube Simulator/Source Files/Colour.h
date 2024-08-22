#ifndef COLOUR_H
#define COLOUR_H

class Colour
{
	float _red = 0.0f;
	float _green = 0.0f;
	float _blue = 0.0f;

public:

	Colour() = default;

	Colour(float red, float green, float blue);

	Colour(int red, int green, int blue);

	explicit Colour(const Colour* copy);

	void setColour(const Colour* colour);

	float getRed() const;

	float getGreen() const;

	float getBlue() const;
};

void setRenderColour(const Colour& colour);

#endif // !COLOUR_H
