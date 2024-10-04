#pragma once

#include "SFML/Graphics.hpp"
#include "Component.hpp"
#include <vector>

using namespace sf;
using namespace std;

class GameObject
{
	private:
		vector <shared_ptr<Component>> _Components;
	public:
		void addComponents(shared_ptr<Component> new_component);
		void update(float elapsedTime);
		void draw(VertexArray& canvas);
};