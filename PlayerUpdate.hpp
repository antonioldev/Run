#pragma once
#include <SFML/Graphics.hpp>
#include "Update.hpp"
#include "InputReceiver.hpp"

using namespace sf;

class PlayerUpdate : public Update
{
	private:
		const float PLAYER_WIDTH = 20.0f;
		const float PLAYER_HEIGHT = 16.0f;
		FloatRect _Position;

		bool* _IsPaused = nullptr;
		float _Gravity = 165;
		float _RunSpeed = 150;
		float _BoostSpeed = 250;
		InputReceiver _InputReceiver;

		Clock _JumpClock;
		bool _SpaceHeldDown = false;
		float _JumpDuration = 0.50f;
		float _JumpSpeed = 400.0f;
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
		void assemble(shared_ptr<LevelUpdate> levelUpdate,
			shared_ptr<PlayerUpdate> playerUpdate) override;
		void update(float fps) override;
};