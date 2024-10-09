#include "PlatformUpdate.hpp"
#include "PlayerUpdate.hpp"

FloatRect* PlatformUpdate::getPositionPointer()
{
    return &_Position;
}

void PlatformUpdate::assemble(
    shared_ptr<LevelUpdate> levelUpdate,
    shared_ptr<PlayerUpdate> playerUpdate)
{
    //mPosition = position;
    _PlayerPosition = playerUpdate->getPositionPointer();
    _PlayerIsGrounded = playerUpdate->getGroundedPointer();
}

void PlatformUpdate::update(float fps)
{

    if (_Position.intersects(*_PlayerPosition))
    {
        Vector2f playerFeet(_PlayerPosition->left +
            _PlayerPosition->width / 2,
            _PlayerPosition->top +
            _PlayerPosition->height);

        Vector2f playerRight(_PlayerPosition->left +
            _PlayerPosition->width,
            _PlayerPosition->top +
            _PlayerPosition->height / 2);

        Vector2f playerLeft(_PlayerPosition->left,
            _PlayerPosition->top +
            _PlayerPosition->height / 2);

        Vector2f playerHead(_PlayerPosition->left +
            _PlayerPosition->width / 2,
            _PlayerPosition->top);

        if (_Position.contains(playerFeet))
        {
            if (playerFeet.y > _Position.top)
            {
                _PlayerPosition->top =
                    _Position.top -
                    _PlayerPosition->height;

                *_PlayerIsGrounded = true;
            }
        }

        else if (_Position.contains(playerRight))
        {
            _PlayerPosition->left =
                _Position.left - _PlayerPosition->width;
        }

        else if (_Position.contains(playerLeft))
        {
            _PlayerPosition->left =
                _Position.left + _Position.width;
        }

        else if (_Position.contains(playerHead))
        {
            _PlayerPosition->top =
                _Position.top + _Position.height;
        }
    }
}
