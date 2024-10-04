#pragma once
#include "SFML/Graphics.hpp"
#include "Component.hpp"

using namespace sf;

class Update;

class Graphics : public Component
{
	private:

	public:
		Graphics() {_IsGraphics = true;}
		virtual void assemble(VertexArray& canvas, 
			shared_ptr<Update> genericUpdate, IntRect texCoords) = 0;
		virtual void draw(VertexArray& canvas) = 0;
};