/******************************************************************************/
/*!
\file   Sprite.cpp
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2016/07/23(yy/mm/dd)

\description
Contains sprite's class member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Sprite.h"
#include "../Texture/Texture.h"
#include "../../../ObjectManager/Object/Object.h"
#include "../../../Component/ComponentFactory/ComponentFactory.h"

/******************************************************************************/
/*!
\brief - SpriteBuilder constructor
\param Owner - Owner of this Component
\param key - ComponentType
\return new Sprite
*/
/******************************************************************************/
Component* SpriteBuilder::BuildComponent(Object* Owner, ComponentType key) const {
	return new Sprite(Owner, key);
};

/******************************************************************************/
/*!
\brief - Sprite constructor
\param Owner - Owner of this Component
\param key - ComponentType
*/
/******************************************************************************/
Sprite::Sprite(Object* Owner, ComponentType key)
    : Component(Owner, key), 
	m_texture(0), current_ani_check(false),  skipFirstAnimation(false),
	animation_check(false), drawingCheck(true), m_blur(false), m_inverse(false),
    m_frames(1), m_frameSpeed(1.f), m_frameUV(0.f), currentFrame(0),m_dtOffset(1.f),
    specificFrame(0), flip(1), m_blurAmount(50.f), m_color(vec4(1, 1, 1, 1)), m_sobel(false),
	m_sobelAmount(800.f), m_wave(false), m_phase(vec2(1.f, 1.f)), m_ripple(false)
{
	// Preset transform
	if (!m_Owner->HasComponent(CT_TRANSFORM))
		m_Owner->AddComponent(ComponentFactory::CreateComponent(m_Owner, CT_TRANSFORM));
}

/******************************************************************************/
/*!
\brief - setting color
\param color - setting the color
*/
/******************************************************************************/
void Sprite::SetColor(const vec4& color)
{
	m_color = color;
}

/******************************************************************************/
/*!
\brief - getting color
\return m_color - getting the color
*/
/******************************************************************************/
vec4 Sprite::GetColor(void) const
{
	return m_color;
}

/******************************************************************************/
/*!
\brief - setting the drawingCheck with input
\param check - drawing the sprite or not
*/
/******************************************************************************/
void Sprite::SetDrawingCheck(bool check)
{
    drawingCheck = check;
}

/******************************************************************************/
/*!
\brief - getting the drawingCheck
\return drawingCheck - drawing the sprite or not
*/
/******************************************************************************/
bool Sprite::GetDrawingCheck(void)
{
    return drawingCheck;
}

/******************************************************************************/
/*!
\brief - setting the animation_check with input
\param check - working animation or not
*/
/******************************************************************************/
void Sprite::SetAnimation(bool check)
{
    animation_check = check;
}

/******************************************************************************/
/*!
\brief - getting the animation check
\return animation_check - working animation or not
*/
/******************************************************************************/
bool Sprite::GetAnimation(void)
{
    return animation_check;
}

/******************************************************************************/
/*!
\brief - setting the m_frames with input
\param frame - setting frame
*/
/******************************************************************************/
void Sprite::SetFrame(int frame)
{
    m_frames = frame;
}

/******************************************************************************/
/*!
\brief - getting the m_frames check
\return m_frames - get the what frames on the sprite
*/
/******************************************************************************/
int Sprite::GetFrame(void)
{
    return m_frames;
}
/******************************************************************************/
/*!
\brief - setting the m_frames with input
\param frame - setting specific frame
*/
/******************************************************************************/
void Sprite::SetSpecificFrame(int frame)
{
    current_ani_check = true;
    specificFrame = frame;
}
/******************************************************************************/
/*!
\brief - getting the specific frames check
\return m_frames - get the specific frame
*/
/******************************************************************************/
int Sprite::GetSpecificFrame(void)
{
    return specificFrame;
}

/******************************************************************************/
/*!
\brief - getting the current frame
\return currentFrame - getting the current frame
*/
/******************************************************************************/
int Sprite::GetCurrentFrame(void)
{
    return currentFrame;
}
/******************************************************************************/
/*!
\brief - setting the frame speed
\param spd - setting the frame speed
*/
/******************************************************************************/
void Sprite::SetFrameSpd(float spd)
{
    m_frameSpeed = spd;
}
/******************************************************************************/
/*!
\brief - return the frame speed
\return m_frameSpeed - return the frame speed
*/
/******************************************************************************/
float Sprite::GetFrameSpd(void)
{
    return m_frameSpeed;
}
/******************************************************************************/
/*!
\brief - setting flip
\param value - with this value
*/
/******************************************************************************/
void Sprite::SetFlip(int value)
{
    flip = value;
}
/******************************************************************************/
/*!
\brief - setting blur toggle
\param toggle - true or false
*/
/******************************************************************************/
void Sprite::SetBlurToggle(bool toggle)
{
	m_blur = toggle;
}
/******************************************************************************/
/*!
\brief - getting the blur toggle
\return m_blur - true or false
*/
/******************************************************************************/
bool Sprite::GetBlurToggle(void) const
{
	return m_blur;
}
/******************************************************************************/
/*!
\brief - getting the blur amount
\return m_blurAmount - return blur amount
*/
/******************************************************************************/
float Sprite::GetBlurAmount(void) const
{
	return m_blurAmount;
}
/******************************************************************************/
/*!
\brief - setting the blur amount
\param amount - setting the blur amount
*/
/******************************************************************************/
void Sprite::SetBlurAmount(float amount)
{
	m_blurAmount = amount;
}
/******************************************************************************/
/*!
\brief - setting the inverse toggle
\param toggle - true or false
*/
/******************************************************************************/
void Sprite::SetInverseToggle(bool toggle)
{
	m_inverse = toggle;
}
/******************************************************************************/
/*!
\brief - getting the inverse toggle
\return m_inverse - true or false
*/
/******************************************************************************/
bool Sprite::GetInverseToggle(void) const
{
	return m_inverse;
}
/******************************************************************************/
/*!
\brief - setting the sobel toggle
\param toggle - true or false
*/
/******************************************************************************/
void Sprite::SetSobelToggle(bool toggle)
{
	m_sobel = toggle;
}
/******************************************************************************/
/*!
\brief - getting the sobel toggle
\return m_sobel - true or false
*/
/******************************************************************************/
bool Sprite::GetSobelToggle(void) const
{
	return m_sobel;
}
/******************************************************************************/
/*!
\brief - getting the sobel amout
\return m_sobelAmount - return the sobel amount
*/
/******************************************************************************/
float Sprite::GetSobelAmount(void) const
{
	return m_sobelAmount;
}
/******************************************************************************/
/*!
\brief - setting the sobel amount
\param amount - setting sobel amount with this
*/
/******************************************************************************/
void Sprite::SetSobelAmount(float amount)
{
	m_sobelAmount = amount;
}
/******************************************************************************/
/*!
\brief - setting the wave toggle
\param toggle - true or false
*/
/******************************************************************************/
void Sprite::SetWaveToggle(bool toggle)
{
	m_wave = toggle;
}
/******************************************************************************/
/*!
\brief - geting the wave toggle
\return m_wave - true or false
*/
/******************************************************************************/
bool Sprite::GetWaveToggle(void) const
{
	return m_wave;
}
/******************************************************************************/
/*!
\brief - getting the wave phase
\return m_phase - get the phase of wave
*/
/******************************************************************************/
const vec2 & Sprite::GetWavePhase(void) const
{
	return m_phase;
}
/******************************************************************************/
/*!
\brief - setting the wave phase with input
\param phase - set with this value
*/
/******************************************************************************/
void Sprite::SetWavePhase(const vec2& phase)
{
	m_phase = phase;
}
/******************************************************************************/
/*!
\brief - setting the ripple toggle with input
\param m_ripple - true or false
*/
/******************************************************************************/
void Sprite::SetRippleToggle(bool ripple)
{
	m_ripple = ripple;
}
/******************************************************************************/
/*!
\brief - getting the ripple toggle
\return - true or false
*/
/******************************************************************************/
bool Sprite::GetRippleToggle(void) const
{
	return m_ripple;
}
/******************************************************************************/
/*!
\brief - getting the flip value
\return flip - flip value
*/
/******************************************************************************/
int Sprite::GetFlip(void)
{
    return flip;
}
/******************************************************************************/
/*!
\brief - setting texture with input
\param texture - set sprite's texture
*/
/******************************************************************************/
void Sprite::SetTexture(Texture* texture)
{
    m_texture = texture;
}
/******************************************************************************/
/*!
\brief - getting texture of sprite
\return m_texture - get the sprite's texture
*/
/******************************************************************************/
Texture* Sprite::GetTexture(void) const
{
    return m_texture;
}
