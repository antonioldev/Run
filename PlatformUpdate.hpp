#pragma once
#include "Update.hpp"
#include "SFML/Graphics.hpp"

using namespace sf;

class PlatformUpdate : 
	public Update
{
private:
	FloatRect _Position;
	FloatRect* _PlayerPosition = nullptr;
	bool* _PlayerIsGrounded = nullptr;
public:
	FloatRect* getPositionPointer();

	// From Update : Component
	void update(float fps) override;
	void assemble(shared_ptr<LevelUpdate> levelUpdate,
		shared_ptr<PlayerUpdate> playerUpdate)
		override;
};
