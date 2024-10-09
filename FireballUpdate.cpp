#include "FireballUpdate.hpp"
#include <random>
#include "PlayerUpdate.hpp"
#include "SoundEngine.hpp"

FireballUpdate::FireballUpdate(bool* pausedPointer)
{
	_GameIsPaused = pausedPointer;
	_PauseDurationTarget = getRandomNumber(_MinPause, _MaxPause);
}

bool* FireballUpdate::getFacingRightPointer()
{
	return &_LeftToRight;
}

FloatRect* FireballUpdate::getPositionPointer()
{
	return &_Position;
}

void FireballUpdate::assemble(
	shared_ptr<LevelUpdate> levelUpdate,
	shared_ptr<PlayerUpdate> playerUpdate)
{
	_PauseDurationTarget = getRandomNumber(_MinPause, _MaxPause);
	_PlayerPosition = playerUpdate->getPositionPointer();
	_Position.top = getRandomNumber(
		_PlayerPosition->top - _MaxSpawnDistanceFromPlayer,
		_PlayerPosition->top + _MaxSpawnDistanceFromPlayer);
	_Position.left = _PlayerPosition->left - getRandomNumber(200, 400);
	_Position.width = 10;
	_Position.height = 10;
}

int FireballUpdate::getRandomNumber(int minHeight, int maxHeight)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(minHeight, maxHeight);
	int randomHeight = distribution(gen);
	return randomHeight;
}

void FireballUpdate::update(float fps)
{
	if (!*_GameIsPaused)
	{
		if (!_MovementPaused)
		{
			if (_LeftToRight)
			{
				_Position.left += _Speed * fps;
				if (_Position.left - _PlayerPosition->left > _Range)
				{
					_MovementPaused = true;
					_PauseClock.restart();
					_LeftToRight = !_LeftToRight;
					_Position.top = getRandomNumber(
						_PlayerPosition->top - _MaxSpawnDistanceFromPlayer,
						_PlayerPosition->top + _MaxSpawnDistanceFromPlayer);
					_PauseDurationTarget = getRandomNumber(_MinPause, _MaxPause);
				}
			}
			else
			{
				_Position.left -= _Speed * fps;

				if (_PlayerPosition->left - _Position.left > _Range)
				{
					_MovementPaused = true;
					_PauseClock.restart();
					_LeftToRight = !_LeftToRight;
					_Position.top = getRandomNumber(
						_PlayerPosition->top - _MaxSpawnDistanceFromPlayer,
						_PlayerPosition->top + _MaxSpawnDistanceFromPlayer);
					_PauseDurationTarget = getRandomNumber(_MinPause, _MaxPause);
				}
			}
			if (_PlayerPosition->intersects(_Position))
			{
				_PlayerPosition->top = _PlayerPosition->top + _PlayerPosition->height * 2;
			}
		}
		else
		{
			if (_PauseClock.getElapsedTime().asSeconds() > _PauseDurationTarget)
			{
				_MovementPaused = false;
				SoundEngine::playFireballLaunch( _PlayerPosition->getPosition(),
					_Position.getPosition());
			}
		}
	}
}