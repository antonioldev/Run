#include "SoundEngine.hpp"
#include <assert.h>

SoundEngine* SoundEngine::_s_Instance = nullptr;
bool SoundEngine::mMusicIsPlaying = false;
Music SoundEngine::music;

SoundBuffer SoundEngine::_ClickBuffer;
Sound SoundEngine::_ClickSound;
SoundBuffer SoundEngine::_JumpBuffer;
Sound SoundEngine::_JumpSound;
SoundBuffer SoundEngine::_FireballLaunchBuffer;
Sound SoundEngine::_FireballLaunchSound;

SoundEngine::SoundEngine()
{
	assert(_s_Instance == nullptr);
	_s_Instance = this;

	_ClickBuffer.loadFromFile("sound/click.wav");
	_ClickSound.setBuffer(_ClickBuffer);

	_JumpBuffer.loadFromFile("sound/jump.wav");
	_JumpSound.setBuffer(_JumpBuffer);

	Listener::setDirection(1.0f, 0.f, 1.0f);
	Listener::setUpVector(1.0f, 1.0f, 0.0f);
	Listener::setGlobalVolume(100.0f);
	_FireballLaunchBuffer.loadFromFile("sound/fireballLaunch.wav");
	_FireballLaunchSound.setBuffer(_FireballLaunchBuffer);
}

void SoundEngine::playClick()
{
	_ClickSound.play();
}

void SoundEngine::playJump()
{
	_JumpSound.play();
}

void SoundEngine::startMusic()
{
	music.openFromFile("music/music.wav");
	_s_Instance->music.play();
	_s_Instance->music.setLoop(true);
	mMusicIsPlaying = true;
}

void SoundEngine::pauseMusic()
{
	_s_Instance->music.pause();
	mMusicIsPlaying = false;
}

void SoundEngine::resumeMusic()
{
	_s_Instance->music.play();
	mMusicIsPlaying = true;
}

void SoundEngine::stopMusic()
{
	_s_Instance->music.stop();

	mMusicIsPlaying = false;
}

void SoundEngine::playFireballLaunch(Vector2f playerPosition, Vector2f soundLocation)
{
	_FireballLaunchSound.setRelativeToListener(true);
	if (playerPosition.x > soundLocation.x)
	{
		Listener::setPosition(0.0f, 0.0f, 0.0f);
		_FireballLaunchSound.setPosition(-100.0f, 0.0f, 0.0f);
		_FireballLaunchSound.setMinDistance(100);
		_FireballLaunchSound.setAttenuation(0);
	}
	else
	{
		Listener::setPosition(0.0f, 0.0f, 0.0f);
		_FireballLaunchSound.setPosition(100.0f, 0.0f, 0.0f);
		_FireballLaunchSound.setMinDistance(100);
		_FireballLaunchSound.setAttenuation(0);
	}
	_FireballLaunchSound.play();
}