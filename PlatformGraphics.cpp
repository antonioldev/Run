#include "PlatformGraphics.hpp"
#include "PlatformUpdate.hpp"

void PlatformGraphics::draw(VertexArray& canvas)
{
    const Vector2f& position = _Position->getPosition();
    const Vector2f& scale = _Position->getSize();

    canvas[_VertexStartIndex].position = position;
    canvas[_VertexStartIndex + 1].position =
        position + Vector2f(scale.x, 0);
    canvas[_VertexStartIndex + 2].position =
        position + scale;
    canvas[_VertexStartIndex + 3].position =
        position + Vector2f(0, scale.y);
}

void PlatformGraphics::assemble(VertexArray& canvas,
    shared_ptr<Update> genericUpdate,
    IntRect texCoords)
{
    shared_ptr<PlatformUpdate> platformUpdate =
        static_pointer_cast<PlatformUpdate>(genericUpdate);

    _Position = platformUpdate->getPositionPointer();

    _VertexStartIndex = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);

    const int uPos = texCoords.left;
    const int vPos = texCoords.top;
    const int texWidth = texCoords.width;
    const int texHeight = texCoords.height;

    canvas[_VertexStartIndex].texCoords.x = uPos;
    canvas[_VertexStartIndex].texCoords.y = vPos;
    canvas[_VertexStartIndex + 1].texCoords.x =
        uPos + texWidth;
    canvas[_VertexStartIndex + 1].texCoords.y =
        vPos;
    canvas[_VertexStartIndex + 2].texCoords.x =
        uPos + texWidth;
    canvas[_VertexStartIndex + 2].texCoords.y =
        vPos + texHeight;
    canvas[_VertexStartIndex + 3].texCoords.x =
        uPos;
    canvas[_VertexStartIndex + 3].texCoords.y =
        vPos + texHeight;

}
