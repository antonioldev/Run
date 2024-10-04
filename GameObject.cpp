#include "GameObject.hpp"
#include "Update.hpp"
#include "Graphics.hpp"
#include <iostream>

using namespace sf;
using namespace std;

void GameObject::addComponents(shared_ptr<Component> new_component)
{
	_Components.push_back(new_component);
}

void GameObject::update(float elapsedTime)
{
	for (auto component : _Components)
	{
		if (component->_IsUpdate)
			static_pointer_cast<Update>(component)->update(elapsedTime);
	}
}

void GameObject::draw(VertexArray& canvas)
{
	for (auto component : _Components)
	{
		if (component->_IsGraphics)
			static_pointer_cast<Graphics>(component)->draw(canvas);
	}
}