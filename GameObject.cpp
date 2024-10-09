#include "GameObject.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Update.hpp"
#include "Graphics.hpp"

using namespace std;
using namespace sf;

void GameObject::addComponent(
	shared_ptr<Component> newComponent)
{
	_Components.push_back(newComponent);
}

void GameObject::update(float elapsedTime)
{
	for (auto component : _Components)
	{
		if (component->_IsUpdate)
		{
			static_pointer_cast<Update>
				(component)->update(elapsedTime);
		}
	}
}

void GameObject::draw(VertexArray& canvas)
{
	for (auto component : _Components)
	{
		if (component->_IsGraphics)
		{
			static_pointer_cast<Graphics>
				(component)->draw(canvas);
		}
	}
}
