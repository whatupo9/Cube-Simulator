#ifndef ROTATION_H
#define ROTATION_H

#include "Point.h"

class Rotation
{
	Point* _point = nullptr;
	Point _centre;
	Point _target;
	int _axis = 0;
	double _degrees = 0.0;
	double _degreesRotated = 0.0;
	double _duration = 0.0;
	double _delay = 0.0;
	bool _clockwise = false;

public:

	Rotation() = default;

	Rotation(Point* point, const Point& centre, int axis, double degrees, bool clockwise, double duration = ANIMATION_LENGTH, const Rotation* delay = nullptr);

	bool rotate(double elapsed);

	void speedUp(double factor);

	void setStartingPoint(const Point& point);

	Point* getPoint() const;

	Point getTarget() const;

	double getRemainingDuration() const;
};

#endif // !ROTATION_H