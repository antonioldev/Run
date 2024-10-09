#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.hpp"

class MenuGraphics : public Graphics
{
	private:
		FloatRect* _MenuPosition = nullptr;
		int _VertexStartIndex;
		RenderWindow* _Window;
		bool* _GameOver;
		bool _CurrentStatus = false;
		int uPos;
		int vPos;
		int texWidth;
		int texHeight;
	public:
		void draw(VertexArray& canvas) override;
		void assemble(VertexArray& canvas,
			shared_ptr<Update> genericUpdate,
			IntRect texCoords) override;

};