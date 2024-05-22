#include "RotationManager.h"

RotationManager::RotationManager()
{
	_rotations.resize(0);
}

void RotationManager::addRotation(Point* point, const Point& centre, int axis, double degrees, bool clockwise, double duration)
{
	int i = 0;
	for (auto it = _rotations.begin(); it < _rotations.end(); it++)
	{
		if (_rotations[i][0].getPoint() == point)
		{
			it->emplace_back(point, centre, axis, degrees, clockwise, duration, _rotations[i][0]);
			_rotations[i][it->size() - 1].setStartingPoint(_rotations[i][it->size() - 2].getTarget());
			for (auto it2 = _rotations[i].begin(); it2 < _rotations[i].end(); it2++)
			{
				it2->speedUp(1.5);
			}
			return;
		}
		i++;
	}

	std::vector<Rotation> newRotation(0);
	newRotation.emplace_back(point, centre, axis, degrees, clockwise, duration);
	_rotations.emplace_back(newRotation);
}

void RotationManager::update(double elapsed)
{
	for (size_t i = 0; i < _rotations.size(); i++)
	{
		if (not _rotations[i][0].rotate(elapsed))
		{
			continue;
		}

		//Delete the entire vector because the only rotation in it just finished
		if (_rotations[i].size() == 1)
		{
			_rotations.erase(_rotations.begin() + i);
			i--;
			continue;
		}

		//Delete the first rotation in the vector, and the queued ones will be automatically moved forward
		_rotations[i].erase(_rotations[i].begin());
	}
}

bool RotationManager::isRotating() const
{
	return !_rotations.empty();
}