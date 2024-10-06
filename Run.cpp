// Run.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "SFML/Graphics.hpp"
//#include "SFML/Audio.hpp"
#include <vector>
#include "GameObject.hpp"
#include "Factory.hpp"
#include "InputDispatcher.hpp"


using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode::getDesktopMode(), "Run", Style::Fullscreen);
	VertexArray canvas(Quads, 0);
	InputDispatcher inputDispatcher(&window); //Dispatch event to any objects
	vector <GameObject> gameObjects; //Vector that contains all objects for the game
	Factory factory(&window); //Class used to construct all the objects
	factory.loadLevel(gameObjects, canvas, inputDispatcher);

	Clock clock;

	const Color BACKGROUND_COLOR(100, 100, 100, 255);

	while (window.isOpen())
	{
		float time = clock.restart().asSeconds();
		inputDispatcher.dispatchInputEvents();
		window.clear(BACKGROUND_COLOR);

		//update game objects
		for (auto& gameObject : gameObjects)
			gameObject.update(time);
		for (auto& gameObject : gameObjects)
			gameObject.draw(canvas);
		window.display();
	}
	return 0;
}
