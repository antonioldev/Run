#pragma once
#include "Update.hpp"
#include "InputReceiver.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayerUpdate :
	public Update
{
private:
	const float PLAYER_WIDTH = 20.f;
	const float PLAYER_HEIGHT = 16.f;
	FloatRect _Position;

	bool* _IsPaused = nullptr;
	float _Gravity = 165;
	float _RunSpeed = 100;
	float _BoostSpeed = 250;
	InputReceiver _InputReceiver;

	Clock _JumpClock;
	bool _SpaceHeldDown = false;
	float _JumpDuration = .50;
	float _JumpSpeed = 400;

public:
	bool _RightIsHeldDown = false;
	bool _LeftIsHeldDown = false;
	bool _BoostIsHeldDown = false;

	bool _IsGrounded;
	bool _InJump = false;

	FloatRect* getPositionPointer();

	bool* getGroundedPointer();
	void handleInput();
	InputReceiver* getInputReceiver();

	// From Update : Component
	void assemble(
		shared_ptr<LevelUpdate> levelUpdate,
		shared_ptr<PlayerUpdate> playerUpdate)
		override;

	void update(float fps) override;

};
