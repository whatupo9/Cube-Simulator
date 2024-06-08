#include "RotationManager.h"

RotationManager::RotationManager()
{
	_rotations.resize(0);
	_turnsNum.resize(0);
}

void RotationManager::addRotation(Point* point, const Point& centre, int axis, double degrees, bool clockwise, int turnNum)
{
	_rotations.push_back(std::make_shared<Rotation>(point, centre, axis, degrees, clockwise));
	_turnsNum.push_back(turnNum);

	for (int i = _rotations.size() - 1; i >= 0; i--)
	{
		if (point == _rotations[i]->getPoint() and _turnsNum[i] != turnNum)
		{
			_rotations[_rotations.size() - 1]->setStartingPoint(_rotations[i]->getTarget());
		}
	}

	if (turnNum > _highestTurn)
	{
		_highestTurn = turnNum;
		speedUp(turnNum);
	}
}

void RotationManager::update(double elapsed)
{
	if (_rotations.empty())
	{
		return;
	}

	if (_rotations.size() > 8)
	{
		bool l = true;
	}

	double timeLeft = 0.0;

	do
	{
		double otherTimeLeft = _rotations[0]->getRemainingDuration();
		timeLeft = (otherTimeLeft < elapsed) ? elapsed - otherTimeLeft : 0.0;

		for (int i = 0; i < _rotations.size(); i++)
		{
			if (_turnsNum[i] == _currentTurn)
			{
				if (not _rotations[i]->rotate(elapsed))
				{
					continue;
				}
				_rotations.erase(_rotations.begin() + i);
				_turnsNum.erase(_turnsNum.begin() + i);
				i--;
			}
			else if (_turnsNum[0] == _currentTurn + 1)
			{
				_currentTurn++;
				break;
			}
		}
	} while (timeLeft != 0.0 and not _rotations.empty());
}

bool RotationManager::isRotating() const
{
	return !_rotations.empty();
}

void RotationManager::speedUp(int turnNum)
{
	for (int i = 0; i < _rotations.size(); i++)
	{
		if (_turnsNum[i] < turnNum)
		{
			_rotations[i]->speedUp(ROTATION_SPEED_UP_FACTOR);
		}
	}
}