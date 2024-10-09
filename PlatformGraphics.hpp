#pragma once
#include "Graphics.hpp"
#include "SFML/Graphics.hpp"

using namespace sf;

class PlatformGraphics : public Graphics
{
private:
	FloatRect* _Position = nullptr;
	int _VertexStartIndex = -1;

public:

	//From Graphics : Component
	void draw(VertexArray& canvas) override;

	void assemble(VertexArray& canvas,
		shared_ptr<Update> genericUpdate,
		IntRect texCoords) override;

};
