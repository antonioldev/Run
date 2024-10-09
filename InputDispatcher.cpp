#include "InputDispatcher.hpp"

InputDispatcher::InputDispatcher(RenderWindow* window)
{
	_Window = window;
}

void InputDispatcher::dispatchInputEvents()
{
	sf::Event event;
	while (_Window->pollEvent(event))
	{
		/*if (event.type == Event::KeyPressed && 
			event.key.code == Keyboard::Escape)
		{
			_Window->close();
		}*/

		for (const auto& ir : _InputReceivers)
		{
			ir->addEvent(event);
		}
	}
}

void InputDispatcher::registerNewInputReceiver(InputReceiver* ir)
{
	_InputReceivers.push_back(ir);
}
