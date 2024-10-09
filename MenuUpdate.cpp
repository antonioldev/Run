#include "MenuUpdate.hpp"
#include "LevelUpdate.hpp"
#include "PlayerUpdate.hpp"
#include "SoundEngine.hpp"

MenuUpdate::MenuUpdate(RenderWindow* window)
{
	_Window = window;
}

void MenuUpdate::handleInput()
{
	for (const Event& event : _InputReceiver.getEvents())
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::F1 && _IsVisible)
			{
				if (SoundEngine::mMusicIsPlaying)
				{
					SoundEngine::stopMusic();
				}
				_Window->close();
			}
		}
		if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::Escape)
			{
				_IsVisible = !_IsVisible;
				*_IsPaused = !*_IsPaused;
				if (_GameOver)
					_GameOver = false;
				if (!*_IsPaused)
				{
					SoundEngine::resumeMusic();
					SoundEngine::playClick();
				}
				if (!*_IsPaused)
				{
					SoundEngine::pauseMusic();
					SoundEngine::playClick();
				}
			}
		}
	}
	_InputReceiver.clearEvents();
}

FloatRect* MenuUpdate::getPositionPointer()
{
	return &_Position;
}

bool* MenuUpdate::getGameOverPointer()
{
	return &_GameOver;
}

InputReceiver* MenuUpdate::getInputReceiver()
{
	return &_InputReceiver;
}

void MenuUpdate::assemble(shared_ptr<LevelUpdate> levelUpdate,
	shared_ptr<PlayerUpdate> playerUpdate)
{
	_PlayerPosition = playerUpdate->getPositionPointer();
	_IsPaused = levelUpdate->getIsPausedPointer();
	_Position.width = 75;
	_Position.height = 75;
	SoundEngine::startMusic();
	SoundEngine::pauseMusic();

}

void MenuUpdate::update(float fps)
{
	handleInput();
	if (*_IsPaused && !_IsVisible)
	{
		_IsVisible = true;
		_GameOver = true;
	}
	if (_IsVisible)
	{
		_Position.left = _PlayerPosition->getPosition().x - _Position.width / 2;
		_Position.top = _PlayerPosition->getPosition().y - _Position.height / 2;
	}
	else
	{
		_Position.left = -999;
		_Position.top = -999;
	}
}