#include "ICS_Animation.h"

/**
 * The constructor
 *
 * @param frames			The sequence of frame indexes that make the animation.
 * @param framesPerSecond	The number of frame to render per second.
 */
ICS_Animation::ICS_Animation(std::vector<ICS_Pair<int>> frames, int framesPerSecond)
	:
	_frames(frames),
	_framesPerSecond(framesPerSecond)
{
}

/**
 * Gets the animation frame corresponding to the frame index.
 *
 * @param index		The index of the frame in the animation sequence.
 *
 * @returns			The frame number (referring to its location in the texture).
 */
ICS_Pair<int>
ICS_Animation::getFrame(unsigned int index)
{
	// return the frame number if the index is valid
	if (index >= 0 && index < _frames.size())
	{
		return _frames[index];
	}

	// if the index is not valid, return 0
	return ICS_Pair<int>(0, 0);
}