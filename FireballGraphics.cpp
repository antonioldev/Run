#include "FireballGraphics.hpp"
#include "FireballUpdate.hpp"
#include "Animator.hpp"

void FireballGraphics::assemble(VertexArray & canvas,
		shared_ptr<Update> genericUpdate, IntRect texCoords)
{
	shared_ptr<FireballUpdate> fu =
		static_pointer_cast<FireballUpdate>(genericUpdate);
	_Position = fu->getPositionPointer();
	_FacingRight = fu->getFacingRightPointer();
	_Animator = new Animator(texCoords.left, texCoords.top, 3,
		texCoords.width * 3, texCoords.height, 6);
	_SectionToDraw = _Animator->getCurrentFrame(false);
	_VertexStartIndex = canvas.getVertexCount();
	canvas.resize(canvas.getVertexCount() + 4);
	const int uPos = texCoords.left;
	const int vPos = texCoords.top;
	const int texWidth = texCoords.width;
	const int texHeight = texCoords.height;
	canvas[_VertexStartIndex].texCoords.x = uPos;
	canvas[_VertexStartIndex].texCoords.y = vPos;
	canvas[_VertexStartIndex + 1].texCoords.x = uPos + texWidth;
	canvas[_VertexStartIndex + 1].texCoords.y = vPos;
	canvas[_VertexStartIndex + 2].texCoords.x = uPos + texWidth;
	canvas[_VertexStartIndex + 2].texCoords.y = vPos + texHeight;
	canvas[_VertexStartIndex + 3].texCoords.x = uPos;
	canvas[_VertexStartIndex + 3].texCoords.y = vPos + texHeight;
}

void FireballGraphics::draw(VertexArray & canvas)
{
	const Vector2f& position = _Position->getPosition();
	const Vector2f& scale = _Position->getSize();
	canvas[_VertexStartIndex].position = position;
	canvas[_VertexStartIndex + 1].position = position + Vector2f(scale.x, 0);
	canvas[_VertexStartIndex + 2].position = position + scale;
	canvas[_VertexStartIndex + 3].position = position + Vector2f(0, scale.y);
	if (*_FacingRight)
	{
		_SectionToDraw =
				_Animator->getCurrentFrame(false);
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
	else
	{
		_SectionToDraw = _Animator->getCurrentFrame(true);
		const int uPos = _SectionToDraw->left;
		const int vPos = _SectionToDraw->top;
		const int texWidth = _SectionToDraw->width;
		const int texHeight = _SectionToDraw->height;
		canvas[_VertexStartIndex].texCoords.x = uPos;
		canvas[_VertexStartIndex].texCoords.y = vPos;
		canvas[_VertexStartIndex + 1].texCoords.x = uPos - texWidth;
		canvas[_VertexStartIndex + 1].texCoords.y = vPos;
		canvas[_VertexStartIndex + 2].texCoords.x = uPos - texWidth;
		canvas[_VertexStartIndex + 2].texCoords.y = vPos + texHeight;
		canvas[_VertexStartIndex + 3].texCoords.x = uPos;
		canvas[_VertexStartIndex + 3].texCoords.y = vPos + texHeight;
	}
}