#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.hpp"

class Animator;
class PlayerUpdate;

class FireballGraphics : public Graphics
{
	private:
		FloatRect* _Position;
		int _VertexStartIndex;
		bool* _FacingRight = nullptr;
		Animator* _Animator;
		IntRect* _SectionToDraw;
		std::shared_ptr<PlayerUpdate> _PlayerUpdate;
	public:
		void assemble(VertexArray& canvas,
			shared_ptr<Update> genericUpdate, IntRect texCoords) override;
		void draw(VertexArray& canvas) override;
};