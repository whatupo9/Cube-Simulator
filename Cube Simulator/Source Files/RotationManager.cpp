#include <memory>
#include "Cube Constants.h"
#include "Point.h"
#include "Rotation.h"
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

	double timeLeft = 0.0;

	do
	{
		double otherTimeLeft = _rotations[0]->getRemainingDuration();
		timeLeft = elapsed - otherTimeLeft;
		clamp(timeLeft, 0.0, elapsed);

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