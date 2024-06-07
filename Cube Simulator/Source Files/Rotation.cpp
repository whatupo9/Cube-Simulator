#include "Rotation.h"

Rotation::Rotation(Point* point, const Point& centre, int axis, double degrees, bool clockwise, double duration, const Rotation* preceedingRotation) :
	_point(point),
	_centre(centre),
	_target(*_point),
	_axis(axis),
	_degrees(degrees),
	_duration(duration),
	_clockwise(clockwise)
{
	if (preceedingRotation)
	{
		_preceedingRotation = preceedingRotation;
	}

	if (clockwise)
	{
		degrees *= -1;
	}
	_target.rotate(_centre, degrees, axis);
}

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

	double realDegrees = degrees;
	if (_clockwise)
	{
		realDegrees *= -1;
	}

	_point->rotate(_centre, realDegrees, _axis);

	_degreesRotated += degrees;

	if (_degreesRotated >= _degrees)
	{
		*_point = _target;
		return true;
	}
	return false;
}

void Rotation::speedUp(double factor)
{
	_duration /= factor;
}

void Rotation::setStartingPoint(const Point& point)
{
	_target = point;
	double degree = _clockwise ? -_degrees : _degrees;
	_target.rotate(_centre, degree, _axis);
}

Point* Rotation::getPoint() const
{
	return _point;
}

Point Rotation::getTarget() const
{
	return _target;
}

double Rotation::getRemainingDuration() const
{
	double delay = _preceedingRotation ? _preceedingRotation->getRemainingDuration() : 0.0;
	return _duration - (_degreesRotated / _degrees * _duration) + delay;
}