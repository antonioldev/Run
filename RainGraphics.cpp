#include "RainGraphics.hpp"
#include "Animator.hpp"

RainGraphics::RainGraphics(FloatRect* playerPosition, float horizontalOffset,
	float verticalOffset, int rainCoveragePerObject)
{
	_PlayerPosition = playerPosition;
	_HorizontalOffset = horizontalOffset;
	_VerticalOffset = verticalOffset;
	_Scale.x = rainCoveragePerObject;
	_Scale.y = rainCoveragePerObject;
}

void RainGraphics::draw(VertexArray& canvas)
{
	const Vector2f& position = _PlayerPosition->getPosition()
		- Vector2f(_Scale.x / 2 + _HorizontalOffset, _Scale.y / 2 + _VerticalOffset);
	canvas[_VertexStartIndex].position = position;
	canvas[_VertexStartIndex + 1].position = position + Vector2f(_Scale.x, 0);
	canvas[_VertexStartIndex + 2].position = position + _Scale;
	canvas[_VertexStartIndex + 3].position = position + Vector2f(0, _Scale.y);

	//Cycle trough the frames
	_SectionToDraw = _Animator->getCurrentFrame(false);

	// Remember the section of the texture to draw
	const int uPos = _SectionToDraw->left;
	const int vPos = _SectionToDraw->top;
	const int texWidth = _SectionToDraw->width;
	const int texHeight = _SectionToDraw->height;

	canvas[_VertexStartIndex].texCoords.x = uPos;
	canvas[_VertexStartIndex].texCoords.y = vPos;
	canvas[_VertexStartIndex + 1].texCoords.x = uPos + texWidth;
	canvas[_VertexStartIndex + 1].texCoords.y = vPos;
	canvas[_VertexStartIndex + 2].texCoords.x = uPos + texWidth;
	canvas[_VertexStartIndex + 2].texCoords.y = vPos + texHeight;
	canvas[_VertexStartIndex + 3].texCoords.x = uPos;
	canvas[_VertexStartIndex + 3].texCoords.y = vPos + texHeight;
}

void RainGraphics::assemble(VertexArray& canvas,
	shared_ptr<Update> genericUpdate, IntRect texCoords)
{
	_Animator = new Animator(texCoords.left, texCoords.top, 4,
		texCoords.width * 4, texCoords.height, 8);
	_VertexStartIndex = canvas.getVertexCount();
	canvas.resize(canvas.getVertexCount() + 4);
}