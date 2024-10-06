#include "PlayerUpdate.hpp"
#include "SounddEngine.hpp"
#include "LevelUpdate.hpp"

FloatRect* PlayerUpdate::getPositionPointer()
{
	return &_Position;
}

bool* PlayerUpdate::getGroundedPointer()
{
	return &_IsGrounded;
}

void PlayerUpdate::handleInput()
{
	_InputReceiver.clearEvents();
}

InputReceiver* PlayerUpdate::getInputReceiver()
{
	return &_InputReceiver;
}

void PlayerUpdate::assemble(shared_ptr<LevelUpdate> levelUpdate,
	shared_ptr<PlayerUpdate> playerUpdate)
{
	SoundEngine::SoundEngine();
	_Position.width = PLAYER_WIDTH;
	_Position.height = PLAYER_HEIGHT;
	_IsPaused = levelUpdate->getIsPausedPointer();
}

void PlayerUpdate::update(float fps)
{
	handleInput();
}