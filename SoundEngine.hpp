#pragma once
#include <SFML/Audio.hpp>

using namespace sf;

class SoundEngine
{
private:
	static Music music;

	static SoundBuffer _ClickBuffer;
	static Sound _ClickSound;

	static SoundBuffer _JumpBuffer;
	static Sound _JumpSound;

	static SoundBuffer _FireballLaunchBuffer;
	static Sound _FireballLaunchSound;
public:
	SoundEngine();
	static SoundEngine* _s_Instance;

	static bool mMusicIsPlaying;

	static void startMusic();
	static void pauseMusic();
	static void resumeMusic();
	static void stopMusic();

	static void playClick();
	static void playJump();

	static void playFireballLaunch(Vector2f playerPosition, Vector2f soundLocation);
};
