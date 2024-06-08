#include "Cube Constants.h"

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

ICS_Pair<int> calculateNewPositionOnCube(int width, int move, int index)
{
	if (move == L_PRIME)
	{
		if (index == 0)
		{
			return ICS_Pair<int>((width - 1) * width, (width - 2) * width);
		}
		else if (index == width - (width - 1))
		{
			if (width)
			{
				return ICS_Pair<int>((width - 2) * width, (width - 3) * width);
			}
		}
	}
}