#ifndef ROTATION_MANAGER_H
#define ROTATION_MANAGER_H

#include <vector>
#include "Rotation.h"

class RotationManager
{
	std::vector<std::vector<Rotation>> _rotations;

public:

	RotationManager();

	void addRotation(Point* point, const Point& centre, int axis, double degrees, bool clockwise, double duration = ANIMATION_LENGTH);

	void update(double elapsed);

	bool isRotating() const;

	double timeRemaining(int queueIndex, int rotation);
};

#endif // !ROTATION_MANAGER_H
