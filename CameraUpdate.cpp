#include "CameraUpdate.hpp"
#include "PlayerUpdate.hpp"

FloatRect* CameraUpdate::getPositionPointer()
{
	return &_Position;
}

void CameraUpdate::handleInput()
{
	_Position.width = 1.0f;
	for (const Event& event : _InputReceiver->getEvents())
	{
		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				_Position.width *= (event.mouseWheelScroll.delta > 0) ? 0.95f : 1.05f;
		}
		_InputReceiver->clearEvents();
	}
}

InputReceiver* CameraUpdate::getInputReceiver()
{
	_InputReceiver = new InputReceiver;
	_ReceivesInput = true;
	return _InputReceiver;
}

void CameraUpdate::assemble(shared_ptr<LevelUpdate> levelUpdate,
	shared_ptr<PlayerUpdate> playerUpdate)
{
	_PlayerPosition = playerUpdate->getPositionPointer();
}

void CameraUpdate::update(float timeSinceLastUpdate)
{
	if (_ReceivesInput)
	{
		handleInput();
		_Position.left = _PlayerPosition->left;
		_Position.top = _PlayerPosition->top;
	}
	else
	{
		_Position.left = _PlayerPosition->left;
		_Position.top = _PlayerPosition->top;
		_Position.width = 1;
	}
}