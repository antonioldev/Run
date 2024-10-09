#include "CameraGraphics.hpp"
#include "CameraUpdate.hpp"

CameraGraphics::CameraGraphics(
	RenderWindow* window, Texture* texture,
	Vector2f viewSize, FloatRect viewport)
{
	_Window = window;
	_Texture = texture;

	_View.setSize(viewSize);
	_View.setViewport(viewport);

	// The mini map viewport is less than 1
	if (viewport.width < 1)
	{
		_IsMiniMap = true;
	}
	else
	{
		// Only the full screen camera has the time text
		_Font.loadFromFile("fonts/KOMIKAP_.ttf");
		_Text.setFont(_Font);
		_Text.setFillColor(Color(255, 0, 0, 255));
		_Text.setScale(0.2f, 0.2f);
	}

	// Init Background sprite
	_BackgroundTexture.loadFromFile("graphics/backgroundTexture.png");
	_BackgroundSprite.setTexture(_BackgroundTexture);
	_BackgroundSprite2.setTexture(_BackgroundTexture);
	_BackgroundSprite.setPosition(0, -200);

	// Init the shader
	/*_Shader.loadFromFile("shaders/glslsandbox109644", sf::Shader::Fragment);
	if (!_Shader.isAvailable())
		std::cout << "Shader is not avaible\n";
	_Shader.setUniform("resolution", sf::Vector2f(2500, 2500));
	_ShaderClock.restart();*/
}

void CameraGraphics::assemble(
	VertexArray& canvas,
	shared_ptr<Update> genericUpdate,
	IntRect texCoords)
{
	shared_ptr<CameraUpdate> cameraUpdate =
		static_pointer_cast<CameraUpdate>(genericUpdate);
	_Position = cameraUpdate->getPositionPointer();

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

float* CameraGraphics::getTimeConnection()
{
	return &_Time;
}

void CameraGraphics::draw(VertexArray& canvas)
{
	_View.setCenter(_Position->getPosition());

	Vector2f startPosition;
	startPosition.x = _View.getCenter().x -
		_View.getSize().x / 2;
	startPosition.y = _View.getCenter().y -
		_View.getSize().y / 2;

	Vector2f scale;
	scale.x = _View.getSize().x;
	scale.y = _View.getSize().y;

	canvas[_VertexStartIndex].position = startPosition;
	canvas[_VertexStartIndex + 1].position =
		startPosition + Vector2f(scale.x, 0);
	canvas[_VertexStartIndex + 2].position =
		startPosition + scale;
	canvas[_VertexStartIndex + 3].position =
		startPosition + Vector2f(0, scale.y);


	if (_IsMiniMap)
	{
		if (_View.getSize().x <
			MAX_WIDTH && _Position->width > 1)
		{
			_View.zoom(_Position->width);
		}
		else if (_View.getSize().x >
			MIN_WIDTH && _Position->width < 1)
		{
			_View.zoom(_Position->width);
		}
	}

	_Window->setView(_View);

	Vector2f movement;
	movement.x = _Position->left - _PlayerPrviousPosition.x;
	movement.y = _Position->top - _PlayerPrviousPosition.y;
	if (_BackgroundAreFlipped)
	{
		_BackgroundSprite2.setPosition(
			_BackgroundSprite2.getPosition().x + movement.x / 6,
			_BackgroundSprite2.getPosition().y + movement.y / 6);

		_BackgroundSprite.setPosition(
			_BackgroundSprite2.getPosition().x + _BackgroundSprite2.getTextureRect().getSize().x,
			_BackgroundSprite2.getPosition().y);

		if (_Position->left >
			_BackgroundSprite.getPosition().x + (_BackgroundSprite.getTextureRect().getSize().x / 2))
		{
			_BackgroundAreFlipped = !_BackgroundAreFlipped;
			_BackgroundSprite2.setPosition(_BackgroundSprite.getPosition());
		}
	}
	else
	{
		_BackgroundSprite.setPosition(
			_BackgroundSprite.getPosition().x + movement.x / 6,
			_BackgroundSprite.getPosition().y + movement.y / 6);

		_BackgroundSprite2.setPosition(
			_BackgroundSprite.getPosition().x + _BackgroundSprite.getTextureRect().getSize().x,
			_BackgroundSprite.getPosition().y);

		if (_Position->left >
			_BackgroundSprite2.getPosition().x + (_BackgroundSprite2.getTextureRect().getSize().x / 2))
		{
			_BackgroundAreFlipped = !_BackgroundAreFlipped;
			_BackgroundSprite.setPosition(_BackgroundSprite2.getPosition());
		}
	}

	_PlayerPrviousPosition.x = _Position->left;
	_PlayerPrviousPosition.y = _Position->top;

	/*_Shader.setUniform("time", _ShaderClock.getElapsedTime().asSeconds());
	sf::Vector2i mousePos = _Window->mapCoordsToPixel(_Position->getPosition());
	_Shader.setUniform("mouse", sf::Vector2f(mousePos.x, mousePos.y + 1000));

	if (_ShaderClock.getElapsedTime().asSeconds() > 10)
	{
		_ShaderClock.restart();
		_ShowShader = !_ShowShader;
	}
	if (!_ShowShader)
	{
		_Window->draw(_BackgroundSprite, &_Shader);
		_Window->draw(_BackgroundSprite2, &_Shader);
	}
	else
	{*/
		_Window->draw(_BackgroundSprite);
		_Window->draw(_BackgroundSprite2);

	//}

	// Draw the time UI but only in the main camera
	if (!_IsMiniMap)
	{
		_Text.setString(std::to_string(_Time));
		_Text.setPosition(
			_Window->mapPixelToCoords(Vector2i(5, 5)));
		_Window->draw(_Text);
	}

	// Draw the main canvas
	_Window->draw(canvas, _Texture);
}
