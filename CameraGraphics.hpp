#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.hpp"

using namespace sf;

class CameraGraphics : public Graphics
{
	private:
		RenderWindow* _Window;
		View _View;
		int _VertexStartIndex = -999;
		Texture* _Texture = nullptr;
		FloatRect* _Position = nullptr;
		bool _IsMiniMap = false;
		const float MIN_WIDTH = 640.0f;
		const float MAX_WIDTH = 2000.0f;

		//for the UI showing time
		Text _Text;
		Font _Font;
		int _TimeAtTheEndOfGame = 0;
		float _Time = 0;
	public:
		CameraGraphics(RenderWindow* window, Texture* texture,
			Vector2f viewSize, FloatRect viewport);
		float* getTimeConnection();
		void assemble(VertexArray& canvas,
			shared_ptr<Update> genericUpdate, IntRect texCoords) override;
		void draw(VertexArray& canvas) override;
};