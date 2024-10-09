#include "CameraUpdate.hpp"
#include "PlayerUpdate.hpp"

FloatRect* CameraUpdate::getPositionPointer()
{
    return &_Position;
}

void CameraUpdate::assemble(
    shared_ptr<LevelUpdate> levelUpdate,
    shared_ptr<PlayerUpdate> playerUpdate)
{
    _PlayerPosition =
        playerUpdate->getPositionPointer();
}

InputReceiver* CameraUpdate::getInputReceiver()
{
    _InputReceiver = new InputReceiver;
    _ReceivesInput = true;
    return _InputReceiver;
}

void CameraUpdate::handleInput()
{
    _Position.width = 1.0f;

    for (const Event& event : _InputReceiver->getEvents())
    {

        // Handle mouse wheel event for zooming
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.wheel ==
                sf::Mouse::VerticalWheel)
            {
                // Accumulate the zoom factor based on delta
                _Position.width *=
                    (event.mouseWheelScroll.delta > 0)
                    ? 0.95f : 1.05f;
            }

        }

        _InputReceiver->clearEvents();
    }
}

void CameraUpdate::update(float fps)
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
