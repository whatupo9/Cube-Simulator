#ifndef ROTATION_MANAGER_H
#define ROTATION_MANAGER_H

#include <vector>
#include "Rotation.h"

class RotationManager
{
	std::vector<Rotation*> _rotations;

public:

	RotationManager();

	RotationManager(const RotationManager& copy);

	~RotationManager();

	RotationManager& operator=(const RotationManager& copy);

	void addRotation(Point* point, const Point& centre, int axis, double degrees, bool clockwise, double duration = ANIMATION_LENGTH);

	void update(double elapsed);

	bool isRotating() const;

	void speedUp(const Point* point, int size, double factor);
};

#endif // !ROTATION_MANAGER_H
