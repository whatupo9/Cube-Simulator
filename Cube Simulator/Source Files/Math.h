double degreesToRadians(double degrees);

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
void swap(T& value1, T& value2) noexcept
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