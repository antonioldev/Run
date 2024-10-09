#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Animator
{
private:
	IntRect _SourceRect;
	int _LeftOffset;
	int _FrameCount;
	int _CurrentFrame;
	int _FramePeriod;
	int _FrameWidth;
	int _FPS = 12;
	Clock _Clock;

public:

	Animator(
		int leftOffset,
		int topOffset,
		int frameCount,
		int textureWidth,
		int textureHeight,
		int fps);

	IntRect* getCurrentFrame(bool reversed);
};
