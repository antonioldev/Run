#pragma once
#include "Graphics.hpp"

class Animator;

class RainGraphics : public Graphics
{
	private:
		FloatRect* _PlayerPosition;
		int _VertexStartIndex;
		Vector2f _Scale;
		float _HorizontalOffset;
		float _VerticalOffset;
		Animator* _Animator;
		IntRect* _SectionToDraw;
	public:
		RainGraphics(FloatRect* playerPosition, float horizontalOffset,
			float verticalOffset, int rainCoveragePerObject);
		void draw(VertexArray& canvas) override;
		void assemble(VertexArray& canvas,
			shared_ptr<Update> genericUpdate,
			IntRect texCoords) override;
};