#ifndef ROTATION_MANAGER_H
#define ROTATION_MANAGER_H

#include <vector>
#include <memory>
#include "Rotation.h"

class RotationManager
{
	std::vector<std::shared_ptr<Rotation>> _rotations;

public:

	RotationManager();

	void addRotation(Point* point, const Point& centre, int axis, double degrees, bool clockwise, double duration = ANIMATION_LENGTH);

	void update(double elapsed);

	bool isRotating() const;

	void speedUp(const Point* point, int size, double factor);

	std::shared_ptr<Rotation> getRotation() const;
};

#endif // !ROTATION_MANAGER_H
