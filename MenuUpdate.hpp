#pragma once
#include <SFML/Graphics.hpp>
#include "Update.hpp"
#include "InputReceiver.hpp"

using namespace sf;
using namespace std;

class MenuUpdate : public Update
{
	private:
		FloatRect _Position;
		InputReceiver _InputReceiver;
		FloatRect* _PlayerPosition = nullptr;
		bool _IsVisible = false;
		bool* _IsPaused;
		bool _GameOver;
		RenderWindow* _Window;
	public:
		MenuUpdate(RenderWindow* window);
		void handleInput();
		FloatRect* getPositionPointer();
		bool* getGameOverPointer();
		InputReceiver* getInputReceiver();
		void assemble(shared_ptr<LevelUpdate> levelUpdate,
			shared_ptr<PlayerUpdate> playerUpdate) override;
		void update(float fps) override;
};