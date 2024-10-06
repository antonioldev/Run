#pragma once
#include <SFML/Graphics.hpp>
#include "Update.hpp"
#include "InputReceiver.hpp"

using namespace sf;
class CameraUpdate : public Update
{
	private:
		FloatRect _Position;
		FloatRect* _PlayerPosition;
		bool _ReceivesInput = false;
		InputReceiver* _InputReceiver = nullptr;
	public:
		FloatRect* getPositionPointer();
		void handleInput();
		InputReceiver* getInputReceiver();
		void assemble(shared_ptr<LevelUpdate> levelUpdate,
			shared_ptr<PlayerUpdate> playerUpdate) override;
		void update(float timeSinceLastUpdate) override;
};