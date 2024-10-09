#pragma once
#include "SFML/Graphics.hpp"
#include "InputReceiver.hpp"

using namespace sf;

class InputDispatcher
{
private:
	RenderWindow* _Window;
	vector <InputReceiver*> _InputReceivers;

public:
	InputDispatcher(RenderWindow* window);
	void dispatchInputEvents();

	void registerNewInputReceiver(InputReceiver* ir);
};
