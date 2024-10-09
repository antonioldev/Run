#include "PlayerGraphics.hpp"
#include "PlayerUpdate.hpp"
#include "Animator.hpp"

void PlayerGraphics::assemble(VertexArray& canvas,
    shared_ptr<Update> genericUpdate,
    IntRect texCoords)
{

    _PlayerUpdate = static_pointer_cast<PlayerUpdate>(genericUpdate);
    _Position = _PlayerUpdate->getPositionPointer();

    _Animator = new Animator(
        texCoords.left,
        texCoords.top,
        6,// 6 frames
        texCoords.width * 6,
        texCoords.height,
        12);// FPS

    // Get the first frame of animation
    _SectionToDraw = _Animator->getCurrentFrame(false);
    _StandingStillSectionToDraw = _Animator->getCurrentFrame(false);

    _VertexStartIndex = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);
}


void PlayerGraphics::draw(VertexArray& canvas)
{
    const Vector2f& position =
        _Position->getPosition();
    const Vector2f& scale =
        _Position->getSize();

    canvas[_VertexStartIndex].position =
        position;
    canvas[_VertexStartIndex + 1].position =
        position + Vector2f(scale.x, 0);
    canvas[_VertexStartIndex + 2].position =
        position + scale;
    canvas[_VertexStartIndex + 3].position =
        position + Vector2f(0, scale.y);


    if (_PlayerUpdate->_RightIsHeldDown &&
        !_PlayerUpdate->_InJump &&
        !_PlayerUpdate->_BoostIsHeldDown &&
        _PlayerUpdate->_IsGrounded)
    {
        _SectionToDraw = _Animator->getCurrentFrame(false);
    }

    if (_PlayerUpdate->_LeftIsHeldDown &&
        !_PlayerUpdate->_InJump &&
        !_PlayerUpdate->_BoostIsHeldDown &&
        _PlayerUpdate->_IsGrounded)
    {
        _SectionToDraw = _Animator->getCurrentFrame(true);// reversed
    }
    else
    {
        // Test the players facing position
        // in case it changed while jumping or boosting
        // This value is used in the final animation option
        if (_PlayerUpdate->_LeftIsHeldDown)
        {
            _LastFacingRight = false;
        }
        else
        {
            _LastFacingRight = true;
        }
    }

    const int uPos = _SectionToDraw->left;
    const int vPos = _SectionToDraw->top;
    const int texWidth = _SectionToDraw->width;
    const int texHeight = _SectionToDraw->height;

    if (_PlayerUpdate->_RightIsHeldDown &&
        !_PlayerUpdate->_InJump &&
        !_PlayerUpdate->_BoostIsHeldDown)
    {
        canvas[_VertexStartIndex].texCoords.x
            = uPos;
        canvas[_VertexStartIndex].texCoords.y
            = vPos;
        canvas[_VertexStartIndex + 1].texCoords.x
            = uPos + texWidth;
        canvas[_VertexStartIndex + 1].texCoords.y
            = vPos;
        canvas[_VertexStartIndex + 2].texCoords.x
            = uPos + texWidth;
        canvas[_VertexStartIndex + 2].texCoords.y
            = vPos + texHeight;
        canvas[_VertexStartIndex + 3].texCoords.x
            = uPos;
        canvas[_VertexStartIndex + 3].texCoords.y
            = vPos + texHeight;
    }

    else if (_PlayerUpdate->_LeftIsHeldDown &&
        !_PlayerUpdate->_InJump &&
        !_PlayerUpdate->_BoostIsHeldDown)
    {
        canvas[_VertexStartIndex].texCoords.x
            = uPos;
        canvas[_VertexStartIndex].texCoords.y
            = vPos;
        canvas[_VertexStartIndex + 1].texCoords.x
            = uPos - texWidth;
        canvas[_VertexStartIndex + 1].texCoords.y
            = vPos;
        canvas[_VertexStartIndex + 2].texCoords.x
            = uPos - texWidth;
        canvas[_VertexStartIndex + 2].texCoords.y
            = vPos + texHeight;
        canvas[_VertexStartIndex + 3].texCoords.x
            = uPos;
        canvas[_VertexStartIndex + 3].texCoords.y
            = vPos + texHeight;
    }


    else if (_PlayerUpdate->_RightIsHeldDown &&
        _PlayerUpdate->_BoostIsHeldDown)
    {
        canvas[_VertexStartIndex].texCoords.x =
            BOOST_TEX_LEFT;
        canvas[_VertexStartIndex].texCoords.y =
            BOOST_TEX_TOP;
        canvas[_VertexStartIndex + 1].texCoords.x =
            BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[_VertexStartIndex + 1].texCoords.y =
            BOOST_TEX_TOP;
        canvas[_VertexStartIndex + 2].texCoords.x =
            BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[_VertexStartIndex + 2].texCoords.y =
            BOOST_TEX_TOP + BOOST_TEX_HEIGHT;
        canvas[_VertexStartIndex + 3].texCoords.x =
            BOOST_TEX_LEFT;
        canvas[_VertexStartIndex + 3].texCoords.y =
            BOOST_TEX_TOP + BOOST_TEX_HEIGHT;
    }
    else if (_PlayerUpdate->_LeftIsHeldDown &&
        _PlayerUpdate->_BoostIsHeldDown)
    {
        canvas[_VertexStartIndex].texCoords.x =
            BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[_VertexStartIndex].texCoords.y = 0;
        canvas[_VertexStartIndex + 1].texCoords.x =
            BOOST_TEX_LEFT;
        canvas[_VertexStartIndex + 1].texCoords.y = 0;
        canvas[_VertexStartIndex + 2].texCoords.x =
            BOOST_TEX_LEFT;
        canvas[_VertexStartIndex + 2].texCoords.y = 100;
        canvas[_VertexStartIndex + 3].texCoords.x =
            BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[_VertexStartIndex + 3].texCoords.y = 100;
    }

    else if (_PlayerUpdate->_BoostIsHeldDown)
    {
        canvas[_VertexStartIndex].texCoords.x = 536;
        canvas[_VertexStartIndex].texCoords.y = 0;
        canvas[_VertexStartIndex + 1].texCoords.x = 605;
        canvas[_VertexStartIndex + 1].texCoords.y = 0;
        canvas[_VertexStartIndex + 2].texCoords.x = 605;
        canvas[_VertexStartIndex + 2].texCoords.y = 100;
        canvas[_VertexStartIndex + 3].texCoords.x = 536;
        canvas[_VertexStartIndex + 3].texCoords.y = 100;
    }
    else
    {
        if (_LastFacingRight)
        {
            canvas[_VertexStartIndex].texCoords.x =
                _StandingStillSectionToDraw->left;
            canvas[_VertexStartIndex].texCoords.y =
                _StandingStillSectionToDraw->top;
            canvas[_VertexStartIndex + 1].texCoords.x =
                _StandingStillSectionToDraw->left + texWidth;
            canvas[_VertexStartIndex + 1].texCoords.y =
                _StandingStillSectionToDraw->top;
            canvas[_VertexStartIndex + 2].texCoords.x =
                _StandingStillSectionToDraw->left + texWidth;
            canvas[_VertexStartIndex + 2].texCoords.y =
                _StandingStillSectionToDraw->top + texHeight;
            canvas[_VertexStartIndex + 3].texCoords.x =
                _StandingStillSectionToDraw->left;
            canvas[_VertexStartIndex + 3].texCoords.y =
                _StandingStillSectionToDraw->top + texHeight;
        }
        else
        {
            canvas[_VertexStartIndex].texCoords.x =
                _StandingStillSectionToDraw->left + texWidth;
            canvas[_VertexStartIndex].texCoords.y =
                _StandingStillSectionToDraw->top;
            canvas[_VertexStartIndex + 1].texCoords.x =
                _StandingStillSectionToDraw->left;
            canvas[_VertexStartIndex + 1].texCoords.y =
                _StandingStillSectionToDraw->top;
            canvas[_VertexStartIndex + 2].texCoords.x =
                _StandingStillSectionToDraw->left;
            canvas[_VertexStartIndex + 2].texCoords.y =
                _StandingStillSectionToDraw->top + texHeight;
            canvas[_VertexStartIndex + 3].texCoords.x =
                _StandingStillSectionToDraw->left + texWidth;
            canvas[_VertexStartIndex + 3].texCoords.y =
                _StandingStillSectionToDraw->top + texHeight;
        }
    }
}

