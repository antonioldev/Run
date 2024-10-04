#pragma once
#include "SFML/Graphics.hpp"
#include "Component.hpp"

using namespace sf;

class PlayerUpdate;
class LevelUpdate;

class Update : public Component
{
private:

public:
	Update() { _IsUpdate = true; }
	virtual void assemble(shared_ptr<LevelUpdate> levelUpdate,
		shared_ptr<PlayerUpdate> playerUpdate) = 0;
	virtual void update(float timeSinceLastUpdate) = 0;
};