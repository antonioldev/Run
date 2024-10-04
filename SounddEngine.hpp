#pragma once
#include "SFML/Audio.hpp"

using namespace sf;

class SoundEngine
{
	private:
		static Music music;
		static Sound _ClickSound;
		static SoundBuffer _ClickBuffer;
		static Sound _JumpSound;
		static SoundBuffer _JumpBuffer;
	public:
		SoundEngine();
		static SoundEngine* _Instance;
		static bool musicIsPlaying;
		static void startMusic();
		static void stopMusic();
		static void pauseMusic();
		static void resumeMusic();
		static void playClick();
		static void playJump();
};