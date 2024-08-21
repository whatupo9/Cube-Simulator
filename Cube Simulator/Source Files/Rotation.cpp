#include "Rotation.h"

Rotation::Rotation(Point* point, const Point& centre, int axis, double degrees, bool clockwise, const std::shared_ptr<Rotation> preceedingRotation) :
	_point(point),
	_centre(centre),
	_axis(axis),
	_degrees(degrees),
	_preceedingRotation(preceedingRotation),
	_clockwise(clockwise)
{}

bool Rotation::rotate(double elapsed)
{
	if (_preceedingRotation)
	{
		double delay = _preceedingRotation->getRemainingDuration();
		if (elapsed - delay < 0)
		{
			return false;
		}
		elapsed -= delay;
	}
	clamp(elapsed, 0.0, _duration);
	double degrees = elapsed / _duration * _degrees;
	clamp(degrees, 0.0, _degrees - _degreesRotated);

	double realDegrees = _clockwise ? -degrees : degrees;

	//TODO change rotations to use new function
	_point->rotate(_centre, realDegrees, _axis);

	_degreesRotated += degrees;

	if (_degreesRotated >= _degrees)
	{
		return true;
	}
	return false;
}

void Rotation::speedUp(double factor)
{
	_duration /= factor;
}

Point* Rotation::getPoint() const
{
	return _point;
}

double Rotation::getRemainingDuration() const
{
	double delay = _preceedingRotation ? _preceedingRotation->getRemainingDuration() : 0.0;
	return _duration - (_degreesRotated / _degrees * _duration) + delay;
}