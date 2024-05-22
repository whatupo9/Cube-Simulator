#ifndef CUBE_H
#define CUBE_H

#include "Square.h"

const std::array<Point, CORNERS_ON_A_CUBE> DEFAULT_CUBE_CORNERS =
{ {
	Point(-1, 1, -1),
	Point(1, 1, -1),
	Point(1, 1, 1),
	Point(-1, 1, 1),
	Point(-1, -1, -1),
	Point(1, -1, -1),
	Point(1, -1, 1),
	Point(-1, -1, 1)
} };

const std::array<Colour, 6> CUBE_COLOURS =
{ {
	Colour(255, 255, 255),
	Colour(0, 255, 0),
	Colour(255, 0, 0),
	Colour(0, 0, 255),
	Colour(255, 128, 0),
	Colour(255, 255, 0)
} };

class Cube
{
	std::array<Square, SIDES_ON_A_CUBE> _faces;
	std::array<Point*, CORNERS_ON_A_CUBE> _corners;
	std::array<Colour, SIDES_ON_A_CUBE> _faceColours;
	Colour* _outlineColour = nullptr;
	Point _centre;
	RotationManager _manager;

	double* _outlineWidth = nullptr;
	double _width;

public:
	Cube();

	Cube(const std::array<Colour, SIDES_ON_A_CUBE>& faceColours, double width, const Point& centre, const Colour* const outlineColour = nullptr);

	Cube(const Cube& copy);

	~Cube();

	Cube& operator=(const Cube& copy);

	void draw(double zoom);

	void update(double elapsed);

	void startRotation(int axis, bool clockwise = true, const Point& centre = Point());

	Point** findFaceCorners(int face) const;

	Cube& farthestCube(std::vector<Cube>& cubies, int width, int direction, int index);

	bool isRotating() const;
};

#endif // !CUBE_H