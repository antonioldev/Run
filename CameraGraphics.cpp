#include "CameraGraphics.hpp"
#include "CameraUpdate.hpp"

CameraGraphics::CameraGraphics(RenderWindow* window, Texture* texture,
	Vector2f viewSize, FloatRect viewport)
{
	_Window = window;
	_Texture = texture;
	_View.setSize(viewSize);
	_View.setViewport(viewport);
	if (viewport.width < 1)
		_IsMiniMap = true;
	else
	{
		_Font.loadFromFile("fonts/KOMIKAP_.ttf");
		_Text.setFont(_Font);
		_Text.setFillColor(Color(255, 0, 0, 255));
		_Text.setScale(0.2f, 0.2f);
	}
}

float* CameraGraphics::getTimeConnection()
{
	return &_Time;
}

void CameraGraphics::assemble(VertexArray& canvas,
	shared_ptr<Update> genericUpdate, IntRect texCoords)
{
	shared_ptr<CameraUpdate> cameraUpdate = static_pointer_cast<CameraUpdate>(genericUpdate);
	_Position = cameraUpdate->getPositionPointer();
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

void CameraGraphics::draw(VertexArray& canvas)
{
	_View.setCenter(_Position->getPosition());
	Vector2f startPosition;
	startPosition.x = _View.getCenter().x - _View.getSize().x / 2;
	startPosition.y = _View.getCenter().y - _View.getSize().y / 2;

	Vector2f scale;
	scale.x = _View.getSize().x;
	scale.y = _View.getSize().y;

	canvas[_VertexStartIndex].position = startPosition;
	canvas[_VertexStartIndex + 1].position = startPosition + Vector2f(scale.x, 0);
	canvas[_VertexStartIndex + 2].position = startPosition + scale;
	canvas[_VertexStartIndex + 3].position = startPosition + Vector2f(0, scale.y);


	if (_IsMiniMap)
	{
		if (_View.getSize().x < MAX_WIDTH && _Position->width > 1)
			_View.zoom(_Position->width);
		else if (_View.getSize().x > MIN_WIDTH && _Position->width < 1)
			_View.zoom(_Position->width);
	}
	_Window->setView(_View);
	if (!_IsMiniMap)
	{
		_Text.setString(std::to_string(_Time));
		_Text.setPosition(_Window->mapPixelToCoords(Vector2i(5, 5)));
		_Window->draw(_Text);
	}
	_Window->draw(canvas, _Texture);
}