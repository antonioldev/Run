#pragma once
#include <SFML/Graphics.hpp>
#include "Update.hpp"

using namespace sf;

class PlatformUpdate : public Update
{
	private:
		FloatRect _Position;
		FloatRect* _PlayerPosition = nullptr;
		bool* _PlayerIsGrounded = nullptr;
	public:
		FloatRect* getPositionPointer();
		virtual void assemble(shared_ptr<LevelUpdate> levelUpdate,
			shared_ptr<PlayerUpdate> playerUpdate) = 0;
		virtual void update(float timeSinceLastUpdate) = 0;
};