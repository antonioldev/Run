#include "PlayerGraphics.hpp"
#include "PlayerUpdate.hpp"

void PlayerGraphics::assemble(VertexArray& canvas,
	shared_ptr<Update> genericUpdate, IntRect texCoords)
{
	_PlayerUpdate = static_pointer_cast<PlayerUpdate>(genericUpdate);
	_Position = _PlayerUpdate->getPositionPointer();
	_VertexStartIndex = canvas.getVertexCount();
	canvas.resize(canvas.getVertexCount() + 4);
    canvas[_VertexStartIndex].texCoords.x = texCoords.left;
    canvas[_VertexStartIndex].texCoords.y = texCoords.top;
    canvas[_VertexStartIndex + 1].texCoords.x = texCoords.left + texCoords.width;
    canvas[_VertexStartIndex + 1].texCoords.y = texCoords.top;
    canvas[_VertexStartIndex + 2].texCoords.x = texCoords.left + texCoords.width;
    canvas[_VertexStartIndex + 2].texCoords.y = texCoords.top + texCoords.height;
    canvas[_VertexStartIndex + 3].texCoords.x = texCoords.left;
    canvas[_VertexStartIndex + 3].texCoords.y = texCoords.top + texCoords.height;
}

void PlayerGraphics::draw(VertexArray& canvas)
{
    const Vector2f& position = _Position->getPosition();
    const Vector2f& scale = _Position->getSize();
    canvas[_VertexStartIndex].position = position;
    canvas[_VertexStartIndex + 1].position = position + Vector2f(scale.x, 0);
    canvas[_VertexStartIndex + 2].position = position + scale;
    canvas[_VertexStartIndex + 3].position = position + Vector2f(0, scale.y);
}