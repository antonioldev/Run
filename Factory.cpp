#include "Factory.hpp"
#include <iostream>
#include "LevelUpdate.hpp"
#include "PlayerGraphics.hpp"
#include "PlayerUpdate.hpp"
#include "InputDispatcher.hpp"

Factory::Factory(RenderWindow* window)
{
	_window = window;
	_Texture = new Texture();
	if (!_Texture->loadFromFile("graphics/texture.png"))
	{
		cout << "Texture not loaded" << endl;
		return ;
	}
}

void Factory::loadLevel(vector<GameObject>& gameObjects, VertexArray& canvas, InputDispatcher& inputDispatcher)
{
	GameObject level;
	shared_ptr<LevelUpdate> levelUpdate = make_shared<LevelUpdate>();
	level.addComponents(levelUpdate);
	gameObjects.push_back(level);

	GameObject player;
	shared_ptr<PlayerUpdate> playerUpdate = make_shared<PlayerUpdate>();
	playerUpdate->assemble(levelUpdate, nullptr);
	player.addComponents(playerUpdate);

	inputDispatcher.registerNewInputReceiver(playerUpdate->getInputReceiver());

	shared_ptr<PlayerGraphics> playerGraphics = make_shared<PlayerGraphics>();
	playerGraphics->assemble(canvas, playerUpdate, 
		IntRect(PLAYER_TEX_LEFT, PLAYER_TEX_TOP,
		PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT));
	player.addComponents(playerGraphics);
	gameObjects.push_back(player);

	levelUpdate->assemble(nullptr, playerUpdate);
}


Texture* _Texture;