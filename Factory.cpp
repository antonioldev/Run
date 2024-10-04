#include "Factory.hpp"
#include <iostream>

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

}


Texture* _Texture;