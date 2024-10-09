#include "Animator.hpp"

Animator::Animator(
	int leftOffset, int topOffset,
	int frameCount,
	int textureWidth,
	int textureHeight,
	int fps)
{
	_LeftOffset = leftOffset;

	_CurrentFrame = 0;
	_FrameCount = frameCount;

	if (_FrameCount == 0)
		_FrameCount = 1;

	_FrameWidth = (float)textureWidth
		/ _FrameCount;
	_SourceRect.left = leftOffset;
	_SourceRect.top = topOffset;
	_SourceRect.width = _FrameWidth;
	_SourceRect.height = textureHeight;
	_FPS = fps;

	if (_FPS == 0)
		_FPS = 1;

	_FramePeriod = 1000 / _FPS;
	_Clock.restart();
}


IntRect* Animator::getCurrentFrame(bool reversed)
{
	// Reversed adds 1 to the frame number 
	// when drawing the texture reversed.
	// This works because reversed 
	// (flipped horizontally) textures 
	// are drawn pixels right to left

	if (_Clock.getElapsedTime().asMilliseconds()
		> _FramePeriod)
	{
		_CurrentFrame++;
		if (_CurrentFrame >= _FrameCount + reversed)
			_CurrentFrame = 0 + reversed;
		_Clock.restart();
	}

	_SourceRect.left = _LeftOffset + _CurrentFrame
		* _FrameWidth;

	return &_SourceRect;
}
