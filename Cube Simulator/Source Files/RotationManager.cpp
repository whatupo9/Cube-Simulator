#include "RotationManager.h"

RotationManager::RotationManager()
{
	_rotations.resize(0);
}

void RotationManager::addRotation(Point* point, const Point& centre, int axis, double degrees, bool clockwise, double duration)
{
	for (int i = _rotations.size() - 1; i >= 0; i--)
	{
		if (_rotations[i]->getPoint() == point)
		{
			_rotations.push_back(std::make_shared<Rotation>(point, centre, axis, degrees, clockwise, duration, _rotations[i]));
			_rotations[_rotations.size() - 1]->setStartingPoint(_rotations[i]->getTarget());
			_rotations[i]->speedUp(ROTATION_SPEED_UP_FACTOR);
			speedUp(point, i, ROTATION_SPEED_UP_FACTOR);
			return;
		}
	}
	_rotations.push_back(std::make_shared<Rotation>(point, centre, axis, degrees, clockwise, duration));
}

void RotationManager::update(double elapsed)
{
	for (int i = _rotations.size() - 1; i >= 0; i--)
	{
		if (not _rotations[i]->rotate(elapsed))
		{
			continue;
		}
		_rotations.erase(_rotations.begin() + i);
	}
}

bool RotationManager::isRotating() const
{
	return !_rotations.empty();
}

void RotationManager::speedUp(const Point* point, int size, double factor)
{
	for (int i = 0; i < size; i++)
	{
		if (_rotations[i]->getPoint() == point)
		{
			_rotations[i]->speedUp(factor);
		}
	}
}

std::shared_ptr<Rotation> RotationManager::getRotation() const
{
	return _rotations[_rotations.size() - 1];
}