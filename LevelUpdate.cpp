#include "LevelUpdate.hpp"
#include<Random>
#include "SoundEngine.hpp"
#include "PlayerUpdate.hpp"

void LevelUpdate::assemble(
	shared_ptr<LevelUpdate> levelUpdate,
	shared_ptr<PlayerUpdate> playerUpdate)
{
	_PlayerPosition = playerUpdate->getPositionPointer();

	//temp
	//SoundEngine::startMusic();
}

void LevelUpdate::connectToCameraTime(float* cameraTime)
{
	_CameraTime = cameraTime;
}

void LevelUpdate::addPlatformPosition(FloatRect* newPosition)
{
	_PlatformPositions.push_back(newPosition);
	_NumberOfPlatforms++;
}

bool* LevelUpdate::getIsPausedPointer()
{
	return &_IsPaused;
}

void LevelUpdate::positionLevelAtStart()
{
	float startOffset = _PlatformPositions[0]->left;
	for (int i = 0; i < _NumberOfPlatforms; ++i)
	{
		_PlatformPositions[i]->left = i * 100 + startOffset;
		_PlatformPositions[i]->top = 0;
		_PlatformPositions[i]->width = 100;
		_PlatformPositions[i]->height = 20;
	}

	_PlayerPosition->left =
		_PlatformPositions[_NumberOfPlatforms / 2]->left + 2;
	_PlayerPosition->top =
		_PlatformPositions[_NumberOfPlatforms / 2]->top - 22;

	_MoveRelativeToPlatform = _NumberOfPlatforms - 1;
	_NextPlatformToMove = 0;
}

int LevelUpdate::getRandomNumber(int minHeight, int maxHeight)
{
#include <random>
	// Seed the random number generator with current time
	std::random_device rd;
	std::mt19937 gen(rd());

	// Define a uniform distribution for the desired range
	std::uniform_int_distribution<int>
		distribution(minHeight, maxHeight);

	// Generate a random height within the specified range
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
			int platformToPlacePlayerOn;
			positionLevelAtStart();
		}

		*_CameraTime += timeSinceLastUpdate;
		_TimeSinceLastPlatform += timeSinceLastUpdate;

		if (_TimeSinceLastPlatform > _PlatformCreationInterval)
		{
			_PlatformPositions[_NextPlatformToMove]->top =
				_PlatformPositions[_MoveRelativeToPlatform]->top +
				getRandomNumber(-40, 40);

			// How far away to create the next platform
			// Bigger gap if lower than previous
			if (_PlatformPositions[_MoveRelativeToPlatform]->top
				< _PlatformPositions[_NextPlatformToMove]->top)
			{
				_PlatformPositions[_NextPlatformToMove]->left =
					_PlatformPositions[_MoveRelativeToPlatform]->left +
					_PlatformPositions[_MoveRelativeToPlatform]->width +
					getRandomNumber(20, 40);
			}
			else
			{
				_PlatformPositions[_NextPlatformToMove]->left =
					_PlatformPositions[_MoveRelativeToPlatform]->left +
					_PlatformPositions[_MoveRelativeToPlatform]->width +
					getRandomNumber(0, 20);
			}

			_PlatformPositions[_NextPlatformToMove]->width =
				getRandomNumber(20, 200);

			_PlatformPositions[_NextPlatformToMove]->height =
				getRandomNumber(10, 20);

			// Base the time to create the next platform 
			// on the width of the one just created
			_PlatformCreationInterval =
				_PlatformPositions[_NextPlatformToMove]->width / 90;


			_MoveRelativeToPlatform = _NextPlatformToMove;
			_NextPlatformToMove++;

			if (_NextPlatformToMove == _NumberOfPlatforms)
			{
				_NextPlatformToMove = 0;
			}

			_TimeSinceLastPlatform = 0;

		}

		// Has the player lagged behind the furthest back platform
		bool laggingBehind = true;
		for (auto platformPosition : _PlatformPositions)
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
