/*

ICS_AnimatedSprite

	Created: ???

	Change log:

		2024-02-09
			- animation frames are now ordered pairs (x, y)

*/
#pragma once

#include <vector>		// for std::vector (used to store animation frames)
#include "ICS_Pair.h"	// for ICS_Pair (used to store animation frames)

class ICS_Animation
{

private:

// member attributes

	std::vector<ICS_Pair<int>>	_frames;			// The sequence of frame indexes that make the animation.
	int							_framesPerSecond;	// The number of frame to render per second.

public:

// constructors

	/**
	 * The constructor
	 *
	 * @param frames			The sequence of frame indexes that make the animation.
	 * @param framesPerSecond	The number of frame to render per second.
	 */
	ICS_Animation(std::vector<ICS_Pair<int>> frames, int framesPerSecond);

// getters

	/**
	 * Gets the animation frame corresponding to the frame index.
	 *
	 * @param index		The index of the frame in the animation sequence.
	 *
	 * @returns			The frame number (referring to its location in the texture).
	 */
	ICS_Pair<int> getFrame(unsigned int index);

	/**
	 * Gets the number of frames in the animation sequence.
	 *
	 * @returns		The number of frames in the animation sequence.
	 */
	int getFrameCount()
	{
		return (int)_frames.size();
	}

	/**
	 * Gets the number of frame to render per second.
	 *
	 * @returns		The number of frame to render per second.
	 */
	int getFramesPerSecond()
	{
		return _framesPerSecond;
	}

	/**
	 * Gets the number of seconds it takes to render a full loop of the animation.
	 *
	 * @returns		The number of seconds it takes to render a full loop of the animation.
	 */
	float getLoopTime()
	{
		return (1.0f / _framesPerSecond) * _frames.size();
	}

};