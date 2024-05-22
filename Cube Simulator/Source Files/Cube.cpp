#include "Cube.h"
#include "Square.h"

Cube::Cube()
	:
	_width(0.5f)
{
	for (int i = 0; i < CORNERS_ON_A_CUBE; i++)
	{
		_corners[i] = new Point(DEFAULT_CUBE_CORNERS[i]);
	}

	for (int i = 0; i < SIDES_ON_A_CUBE; i++)
	{
		_faceColours[i] = CUBE_COLOURS[i];
		_faces[i] = Square(findFaceCorners(i), _width, _faceColours[i]);
	}
}

Cube::Cube(const std::array<Colour, SIDES_ON_A_CUBE>& faceColours, double width, const Point& centre, const Colour* const outlineColour) :
	_outlineColour(outlineColour ? new Colour(outlineColour) : nullptr),
	_centre(centre),
	_width(width / 2)
{
	for (int i = 0; i < CORNERS_ON_A_CUBE; i++)
	{
		int xOffset = 0;
		int yOffset = 0;
		int zOffset = 0;

		if (i == 1 or i == 2 or i == 5 or i == 6)
			xOffset = 1;
		else
			xOffset = -1;

		if (i < 4)
			yOffset = 1;
		else
			yOffset = -1;

		if (i == 2 or i == 3 or i == 6 or i == 7)
			zOffset = 1;
		else
			zOffset = -1;

		_corners[i] = new Point(centre.getX() + (_width * xOffset), centre.getY() + (_width * yOffset), centre.getZ() + (_width * zOffset));
	}

	for (int i = 0; i < SIDES_ON_A_CUBE; i++)
	{
		_faceColours[i] = faceColours[i];
		_faces[i] = Square(findFaceCorners(i), _width, faceColours[i], outlineColour);
	}
}

Cube::Cube(const Cube& copy) :
	_faceColours(copy._faceColours),
	_outlineColour(copy._outlineColour ? new Colour(copy._outlineColour) : nullptr),
	_centre(copy._centre),
	_manager(copy._manager),
	_width(copy._width)
{
	for (int i = 0; i < CORNERS_ON_A_CUBE; i++)
	{
		_corners[i] = new Point(*copy._corners[i]);
	}

	for (int i = 0; i < SIDES_ON_A_CUBE; i++)
	{
		_faces[i] = Square(findFaceCorners(i), _width, copy._faceColours[i], _outlineColour);
	}
}

Cube::~Cube()
{
	for (auto i : _corners)
	{
		delete i;
	}

	if (_outlineColour)
	{
		delete _outlineColour;
	}

	if (_outlineWidth)
	{
		delete _outlineWidth;
	}
}

Cube& Cube::operator=(const Cube& copy)
{
	_width = copy._width;
	_centre = copy._centre;
	_manager = copy._manager;
	_faceColours = copy._faceColours;

	if (_outlineColour)
	{
		delete _outlineColour;
	}
	if (_outlineWidth)
	{
		delete _outlineWidth;
	}
	_outlineColour = copy._outlineColour ? new Colour(copy._outlineColour) : nullptr;
	_outlineWidth = copy._outlineWidth ? new double(*copy._outlineWidth) : nullptr;

	for (int i = 0; i < CORNERS_ON_A_CUBE; i++)
	{
		_corners[i] = new Point(*copy._corners[i]);
	}

	for (int i = 0; i < SIDES_ON_A_CUBE; i++)
	{
		_faces[i] = Square(findFaceCorners(i), _width, _faceColours[i], copy._outlineColour);
	}
	return *this;
}

void Cube::draw(double zoom)
{
	for (int i = 0; i < SIDES_ON_A_CUBE; i++)
	{
		_faces[i].draw(zoom);
	}
}

void Cube::update(double elapsed)
{
	_manager.update(elapsed);
}

void Cube::startRotation(int axis, bool clockwise, const Point& centre)
{
	if (axis == X_AXIS)
	{
		_faces[2].startRotation(_manager, axis, clockwise, centre);
		_faces[4].startRotation(_manager, axis, clockwise, centre);
	}
	else if (axis == Y_AXIS)
	{
		_faces[0].startRotation(_manager, axis, clockwise, centre);
		_faces[5].startRotation(_manager, axis, clockwise, centre);
	}
	else if (axis == Z_AXIS)
	{
		_faces[1].startRotation(_manager, axis, clockwise, centre);
		_faces[3].startRotation(_manager, axis, clockwise, centre);
	}
}

Point** Cube::findFaceCorners(int face) const
{
	static std::array<Point*, 4> corners;

	for (int i = 0; i < 4; i++)
	{
		corners[i] = _corners[FACE_CORNERS[face][i]];
	}

	return corners._Elems;
}

Cube& Cube::farthestCube(std::vector<Cube>& cubies, int width, int direction, int index)
{
	auto size = (int)pow(width, 3);
	int newIndex = directionIndexChange(direction, width) + index;

	if (newIndex >= size or newIndex < 0)
	{
		return *this;
	}

	Cube& nextCube = cubies[newIndex];
	int axis = directionToAxis(direction);

	bool positive = true;
	if (direction % 2 == 0)
	{
		positive = false;
	}

	if (nextCube._centre.getPoint(axis) > this->_centre.getPoint(axis) and positive)
	{
		return nextCube.farthestCube(cubies, width, direction, index);
	}
	else if (positive)
	{
		return *this;
	}

	if (nextCube._centre.getPoint(axis) < this->_centre.getPoint(axis) and not positive)
	{
		return nextCube.farthestCube(cubies, width, direction, index);
	}
	return *this;
}

bool Cube::isRotating() const
{
	return _manager.isRotating();
}