#include "PlayerUpdate.hpp"
#include "SoundEngine.hpp"
#include "LevelUpdate.hpp"

FloatRect* PlayerUpdate::getPositionPointer()
{
	return &_Position;
}

bool* PlayerUpdate::getGroundedPointer()
{
	return &_IsGrounded;
}

InputReceiver* PlayerUpdate::getInputReceiver()
{
	return &_InputReceiver;

}

void PlayerUpdate::assemble(
	shared_ptr<LevelUpdate> levelUpdate,
	shared_ptr<PlayerUpdate> playerUpdate)
{
	SoundEngine::SoundEngine();

	_Position.width = PLAYER_WIDTH;
	_Position.height = PLAYER_HEIGHT;
	_IsPaused = levelUpdate->getIsPausedPointer();
}

void PlayerUpdate::handleInput()
{
	for (const Event& event : _InputReceiver.getEvents())
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::D)
			{
				_RightIsHeldDown = true;
			}
			if (event.key.code == Keyboard::A)
			{
				_LeftIsHeldDown = true;
			}

			if (event.key.code == Keyboard::W)
			{
				_BoostIsHeldDown = true;
			}

			if (event.key.code == Keyboard::Space)
			{
				_SpaceHeldDown = true;
			}
		}

		if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::D)
			{
				_RightIsHeldDown = false;
			}
			if (event.key.code == Keyboard::A)
			{
				_LeftIsHeldDown = false;
			}

			if (event.key.code == Keyboard::W)
			{
				_BoostIsHeldDown = false;
			}

			if (event.key.code == Keyboard::Space)
			{
				_SpaceHeldDown = false;
			}

		}
	}

	_InputReceiver.clearEvents();
}


void PlayerUpdate::update(float timeTakenThisFrame)
{
	if (!*_IsPaused)
	{
		// All the rest of the code is in here
		_Position.top += _Gravity *
			timeTakenThisFrame;

		handleInput();

		if (_IsGrounded)
		{
			if (_RightIsHeldDown)
			{
				_Position.left +=
					timeTakenThisFrame * _RunSpeed;
			}

			if (_LeftIsHeldDown)
			{
				_Position.left -=
					timeTakenThisFrame * _RunSpeed;
			}
		}

		if (_BoostIsHeldDown)
		{
			_Position.top -=
				timeTakenThisFrame * _BoostSpeed;

			if (_RightIsHeldDown)
			{
				_Position.left +=
					timeTakenThisFrame * _RunSpeed / 2;
			}

			if (_LeftIsHeldDown)
			{
				_Position.left -=
					timeTakenThisFrame * _RunSpeed / 4;
			}
		}

		// Handle Jumping
		if (_SpaceHeldDown && !_InJump && _IsGrounded)
		{
			SoundEngine::playJump();
			_InJump = true;
			_JumpClock.restart();
		}

		if (!_SpaceHeldDown)
		{
			//mInJump = false;
		}

		if (_InJump)
		{
			if (_JumpClock.getElapsedTime().asSeconds() <
				_JumpDuration / 2)
			{
				// Going up
				_Position.top -= _JumpSpeed *
					timeTakenThisFrame;
			}
			else
			{
				// Going down
				_Position.top +=
					_JumpSpeed * (timeTakenThisFrame / 4);
			}

			if (_JumpClock.getElapsedTime().asSeconds() >
				_JumpDuration)
			{
				_InJump = false;
			}

			if (_RightIsHeldDown)
			{
				_Position.left +=
					timeTakenThisFrame * _RunSpeed;
			}

			if (_LeftIsHeldDown)
			{
				_Position.left -=
					timeTakenThisFrame * _RunSpeed;
			}
		}// End if (_InJump)

		_IsGrounded = false;
	}
}



