#include "LevelUpdate.hpp"
#include "PlayerUpdate.hpp"
#include "SounddEngine.hpp"
#include <Random>

void LevelUpdate::addPlatformPosition(FloatRect* newPosition)
{
	_PlatformPosition.push_back(newPosition);
	_NumberOfPlatform++;
}

void LevelUpdate::connectToCameraTime(float* cameraTime)
{
	_CameraTime = cameraTime;
}

bool* LevelUpdate::getIsPausedPointer()
{
	return &_IsPaused;
}

int LevelUpdate::getRandomNumber(int minHeight, int maxHeight)
{
	random_device rd;
	mt19937 gen(rd());

	//define a uniform distribution for the desired range
	uniform_int_distribution<int> distribution(minHeight, maxHeight);
	int randomHeight = distribution(gen);
	return randomHeight;
}

void LevelUpdate::update(float timeSinceLastUpdate)
{
	if (!_IsPaused)
	{
		if (_GameOver)
		{
			_GameOver = false;
			*_CameraTime = 0;
			_TimeSinceLastPlatform = 0;
			//int platformToPlacePlayerOn;
			positionLevelAtStart();
		}
		*_CameraTime += timeSinceLastUpdate;
		_TimeSinceLastPlatform += timeSinceLastUpdate;
		if (_TimeSinceLastPlatform > _PlatformCreationInterval)
		{
			_PlatformPosition[_NextPlatformToMove]->top =
				_PlatformPosition[_MoveRelativeToPlatform]->top + getRandomNumber(-40, 40);
			// How far away to create the next platform
			// Bigger gap if lower than previous
			if (_PlatformPosition[_MoveRelativeToPlatform]->top
				< _PlatformPosition[_NextPlatformToMove]->top)
			{
				_PlatformPosition[_NextPlatformToMove]->left =
					_PlatformPosition[_MoveRelativeToPlatform]->left +
					_PlatformPosition[_MoveRelativeToPlatform]->width +
					getRandomNumber(20, 40);
			}
			else
			{
				_PlatformPosition[_NextPlatformToMove]->left =
					_PlatformPosition[_MoveRelativeToPlatform]->left +
					_PlatformPosition[_MoveRelativeToPlatform]->width +
					getRandomNumber(0, 20);
			}
			_PlatformPosition[_NextPlatformToMove]->width = getRandomNumber(20, 200);
			_PlatformPosition[_NextPlatformToMove]->height = getRandomNumber(10, 20);
			_PlatformCreationInterval = _PlatformPosition[_NextPlatformToMove]->width / 90;
			_MoveRelativeToPlatform = _NextPlatformToMove;
			_NextPlatformToMove++;
			if (_NextPlatformToMove == _NumberOfPlatform)
				_NextPlatformToMove = 0;
			_TimeSinceLastPlatform = 0;
		}
		// Has the player lagged behind the furthest back platform
		bool laggingBehind = true;
		for (auto platformPosition : _PlatformPosition)
		{
			if (platformPosition->left < _PlayerPosition->left)
			{
				laggingBehind = false;
				break;// At least one platform is behind the player
			}
			else
			{
				laggingBehind = true;
			}
		}

		if (laggingBehind)
		{
			_IsPaused = true;
			_GameOver = true;

			SoundEngine::pauseMusic();
		}
	}
}

void LevelUpdate::assemble(shared_ptr<LevelUpdate> levelUpdate,
	shared_ptr<PlayerUpdate> playerUpdate)
{
	_PlayerPosition = playerUpdate->getPositionPointer();
	SoundEngine::startMusic();
}

void LevelUpdate::positionLevelAtStart()
{
	float startOffset = _PlatformPosition[0]->left;
	for (int i = 0; i < _NumberOfPlatform; i++)
	{
		_PlatformPosition[i]->left = i * 100 + startOffset;
		_PlatformPosition[i]->top = 0;
		_PlatformPosition[i]->width = 100;
		_PlatformPosition[i]->height = 20;
	}
	_PlayerPosition->left = _PlatformPosition[_NumberOfPlatform / 2]->left + 2;
	_PlayerPosition->top = _PlatformPosition[_NumberOfPlatform / 2]->top - 22;
	_MoveRelativeToPlatform = _NumberOfPlatform - 1;
	_NextPlatformToMove = 0;
}