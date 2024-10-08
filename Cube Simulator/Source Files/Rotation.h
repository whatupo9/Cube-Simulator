#ifndef ROTATION_H
#define ROTATION_H

#include <memory>
#include "Cube Constants.h"
#include "Point.h"

class Rotation
{
	Point* _point = nullptr;
	Point _centre;
	int _axis = 0;
	double _degrees = 0.0;
	double _degreesRotated = 0.0;
	double _duration = ANIMATION_LENGTH;
	const std::shared_ptr<Rotation> _preceedingRotation = nullptr;
	bool _clockwise = false;

public:

	Rotation() = default;

	Rotation(Point* point, const Point& centre, int axis, double degrees, bool clockwise, const std::shared_ptr<Rotation> preceedingRotation = nullptr);

	bool rotate(double elapsed);

	void speedUp(double factor);

	Point* getPoint() const;

	double getRemainingDuration() const;
};

#endif // !ROTATION_H