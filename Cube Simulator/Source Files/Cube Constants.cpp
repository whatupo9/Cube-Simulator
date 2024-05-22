#include "Cube Constants.h"

int arrayChange(int move, int size)
{
	if (size % 2 == 0)
	{
	}
	return 0;
}

int directionIndexChange(int direction, int arrayWidth)
{
	if (direction == LEFT)
	{
		return -1;
	}
	if (direction == RIGHT)
	{
		return 1;
	}
	if (direction == UP)
	{
		return -(int)pow(arrayWidth, 2);
	}
	if (direction == DOWN)
	{
		return (int)pow(arrayWidth, 2);
	}
	if (direction == FRONT)
	{
		return arrayWidth;
	}
	if (direction == BACK)
	{
		return -arrayWidth;
	}
	return 0;
}

int directionToAxis(int direction)
{
	return (direction - (direction % 2)) / 2;
}