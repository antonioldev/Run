#include "SounddEngine.hpp"
#include <assert.h>

SoundEngine* SoundEngine::_Instance = nullptr;
bool SoundEngine::musicIsPlaying = false;
Music SoundEngine::music;

SoundEngine::SoundEngine()
{
	assert(_Instance == nullptr);
	_Instance = this;

	_ClickBuffer.loadFromFile("sound/click.wav");
	_ClickSound.setBuffer(_ClickBuffer);
	_JumpBuffer.loadFromFile("sound/jump.wav");
	_JumpSound.setBuffer(_JumpBuffer);
}

void SoundEngine::startMusic()
{
	music.openFromFile("music/music.wav");
	_Instance->music.play();
	_Instance->music.setLoop(true);
	musicIsPlaying = true;
}

void SoundEngine::stopMusic()
{
	_Instance->music.stop();
	musicIsPlaying = false;
}

void SoundEngine::pauseMusic()
{
	_Instance->music.pause();
	musicIsPlaying = false;
}

void SoundEngine::resumeMusic()
{
	_Instance->music.play();
	musicIsPlaying = true;
}

void SoundEngine::playClick()
{
	_ClickSound.play();
}

void SoundEngine::playJump()
{
	_JumpSound.play();
}