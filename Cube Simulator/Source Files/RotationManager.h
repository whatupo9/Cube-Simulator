#ifndef ROTATION_MANAGER_H
#define ROTATION_MANAGER_H

#include <vector>
#include <memory>
#include "Rotation.h"

class RotationManager
{
	std::vector<std::shared_ptr<Rotation>> _rotations;
	std::vector<int> _turnsNum;
	int _currentTurn = 0;
	int _highestTurn = 0;

public:

	RotationManager();

	void addRotation(Point* point, const Point& centre, int axis, double degrees, bool clockwise, int turnNum);

	void update(double elapsed);

private:

	void speedUp(int turnNum);
};

#endif // !ROTATION_MANAGER_H