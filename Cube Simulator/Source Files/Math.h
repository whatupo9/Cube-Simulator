#include <cmath>
#include <corecrt_math_defines.h>
#include <vector>

// Rotate a point (x, y) by an angle theta (in radians)
void rotatePoint(double& x, double& y, double degrees, double centreX, double centreY);

void rotatePoint(double& x, double& y, double& z, double cx, double cy, double cz, double degrees, int axis);

double degreesToRadians(double degrees);

/**
 * Finds the absolute value of a number
 *
 * @param value:	The value to find the absolute of
*/
template <typename T>
T absolute(T value)
{
	if (value < 0)
	{
		return -value;
	}
	return value;
}

template <typename T>
void swap(T& value1, T& value2)
{
	T temp = value1;
	value1 = value2;
	value2 = temp;
}

template <typename T>
T clamp(T& value, T min, T max)
{
	if (value > max)
	{
		value = max;
	}
	if (value < min)
	{
		value = min;
	}
	return value;
}

template <typename T>
void findObjects(T** const ptrArr, T* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = *ptrArr[i];
	}
}

template <typename T>
T* findObjects(T** ptrArr, int size)
{
	static std::vector<T> arr(size);
	for (int i = 0; i < size; i++)
	{
		arr[i] = *ptrArr[i];
	}
	return &*arr.begin();
}