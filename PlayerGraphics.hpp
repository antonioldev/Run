#pragma once
#include "Graphics.hpp"

class Animator;
class PlayerUpdate;

class PlayerGraphics : public Graphics
{
private:
	FloatRect* _Position = nullptr;
	int _VertexStartIndex = -999;
	Animator* _Animator;
	IntRect* _SectionToDraw = new IntRect;
	IntRect* _StandingStillSectionToDraw = new IntRect;
	std::shared_ptr<PlayerUpdate> _PlayerUpdate;
	const int BOOST_TEX_LEFT = 536;
	const int BOOST_TEX_TOP = 0;
	const int BOOST_TEX_WIDTH = 69;
	const int BOOST_TEX_HEIGHT = 100;
	bool _LastFacingRight = true;

public:
	void assemble(VertexArray& canvas,
		shared_ptr<Update> genericUpdate, IntRect texCoords) override;
	void draw(VertexArray& canvas) override;
};
