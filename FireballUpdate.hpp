#pragma once
#include <SFML/Graphics.hpp>
#include "Update.hpp"

using namespace sf;

class FireballUpdate : public Update
{
	private:
		FloatRect _Position;
		FloatRect* _PlayerPosition;
		bool* _GameIsPaused = nullptr;
		float _Speed = 250;
		float _Range = 900;
		int _MaxSpawnDistanceFromPlayer = 250;
		bool _MovementPaused = true;
		Clock _PauseClock;
		float _PauseDurationTarget = 0;
		float _MaxPause = 6;
		float _MinPause = 1;
		bool _LeftToRight = true;
	public:
		FireballUpdate(bool* pausedPointer);
		bool* getFacingRightPointer();
		FloatRect* getPositionPointer();
		int getRandomNumber(int minHeight, int maxHeight);
		void update(float fps) override;
		void assemble(shared_ptr<LevelUpdate> levelUpdate,
			shared_ptr<PlayerUpdate> playerUpdate) override;
};