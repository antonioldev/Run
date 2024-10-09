#include "MenuGraphics.hpp"
#include "MenuUpdate.hpp"

void MenuGraphics::assemble(VertexArray& canvas,
	shared_ptr<Update> genericUpdate, IntRect texCoords)
{
	_MenuPosition = static_pointer_cast<MenuUpdate>
		(genericUpdate)->getPositionPointer();
	_GameOver = static_pointer_cast<MenuUpdate>
		(genericUpdate)->getGameOverPointer();
	_CurrentStatus = *_GameOver;
	_VertexStartIndex = canvas.getVertexCount();
	canvas.resize(canvas.getVertexCount() + 4);
	uPos = texCoords.left;
	vPos = texCoords.top;
	texWidth = texCoords.width;
	texHeight = texCoords.height;
	canvas[_VertexStartIndex].texCoords.x = uPos;
	canvas[_VertexStartIndex].texCoords.y = vPos + texHeight;
	canvas[_VertexStartIndex + 1].texCoords.x = uPos + texWidth;
	canvas[_VertexStartIndex + 1].texCoords.y = vPos + texHeight;
	canvas[_VertexStartIndex + 2].texCoords.x = uPos + texWidth;
	canvas[_VertexStartIndex + 2].texCoords.y = vPos + texHeight + texHeight;
	canvas[_VertexStartIndex + 3].texCoords.x = uPos;
	canvas[_VertexStartIndex + 3].texCoords.y = vPos + texHeight + texHeight;
}

void MenuGraphics::draw(VertexArray& canvas)
{

	if (*_GameOver && !_CurrentStatus)
		// current status has just switched to game over
	{
		// Each v coordinate is doubled to 
		// reference the texture below
		_CurrentStatus = *_GameOver;
		canvas[_VertexStartIndex].texCoords.x = uPos;
		canvas[_VertexStartIndex].texCoords.y = vPos + texHeight;
		canvas[_VertexStartIndex + 1].texCoords.x = uPos + texWidth;
		canvas[_VertexStartIndex + 1].texCoords.y = vPos + texHeight;
		canvas[_VertexStartIndex + 2].texCoords.x = uPos + texWidth;
		canvas[_VertexStartIndex + 2].texCoords.y = vPos + texHeight + texHeight;
		canvas[_VertexStartIndex + 3].texCoords.x = uPos;
		canvas[_VertexStartIndex + 3].texCoords.y = vPos + texHeight + texHeight;
	}
	else if (!*_GameOver && _CurrentStatus)
	{
		_CurrentStatus = *_GameOver;
		canvas[_VertexStartIndex].texCoords.x = uPos;
		canvas[_VertexStartIndex].texCoords.y = vPos;
		canvas[_VertexStartIndex + 1].texCoords.x = uPos + texWidth;
		canvas[_VertexStartIndex + 1].texCoords.y = vPos;
		canvas[_VertexStartIndex + 2].texCoords.x = uPos + texWidth;
		canvas[_VertexStartIndex + 2].texCoords.y = vPos + texHeight;
		canvas[_VertexStartIndex + 3].texCoords.x = uPos;
		canvas[_VertexStartIndex + 3].texCoords.y = vPos + texHeight;
	}

	const Vector2f& position = _MenuPosition->getPosition();
	canvas[_VertexStartIndex].position = position;
	canvas[_VertexStartIndex + 1].position =
		position + Vector2f(_MenuPosition->getSize().x, 0);
	canvas[_VertexStartIndex + 2].position =
		position + _MenuPosition->getSize();
	canvas[_VertexStartIndex + 3].position =
		position + Vector2f(0, _MenuPosition->getSize().y);
}