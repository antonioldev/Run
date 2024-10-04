#pragma once
#include "Update.hpp"

using namespace sf;
using namespace std;

class LevelUpdate : public Update
{
	private:
		bool _IsPaused = true;
		vector<FloatRect*> _PlatformPosition;
		float* _CameraTime = new float;
		FloatRect* _PlayerPosition;
		float _PlatformCreationInterval = 0;
		float _TimeSinceLastPlatform = 0;
		int _NextPlatformToMove = 0;
		int _NumberOfPlatform = 0;
		int _MoveRelativeToPlatform = 0;
		bool _GameOver = true;
		void positionLevelAtStart();
	public:
		void addPlatformPosition(FloatRect* newPosition);
		void connectToCameraTime(float *cameraTime);
		bool* getIsPausedPointer();
		int getRandomNumber(int minHeight, int maxHeight);
		void update(float fpd) override;
		void assemble(shared_ptr<LevelUpdate> levelUpdate,
			shared_ptr<PlayerUpdate> playerUpdate) override;
};