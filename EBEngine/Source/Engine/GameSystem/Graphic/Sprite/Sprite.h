/******************************************************************************/
/*!
\file   Sprite.h
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2016/07/24(yy/mm/dd)

\description
Contains Sprite class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "../../../Utilities/Time.h"
#include "../../../Component/Component.h"
#include "../../../Utilities/Math/MathUtils.h"
#include "../../../Component/ComponentBuilder.h"

class Object;
class Texture;

//! Sprite builder class
class SpriteBuilder : public ComponentBuilder
{
public:
	SpriteBuilder() {};
	virtual ~SpriteBuilder() {};
	virtual Component* BuildComponent(Object* Owner, ComponentType key) const;

};

class Sprite : public Component
{

public:

    Sprite(Object* Owner = 0, ComponentType key = CT_SPRITE);
	virtual ~Sprite(void) {};

    void SetColor(const vec4& color);
    vec4 GetColor(void) const;

    void SetTexture(Texture* texture);
    Texture* GetTexture(void) const;
    Texture* m_texture;

    bool GetDrawingCheck(void);
    void SetDrawingCheck(bool check);

    //Animation Function
    void SetAnimation(bool check);
    bool GetAnimation(void);
    void SetFrame(int frame);
    int GetFrame(void);
    void SetFrameSpd(float spd);
    float GetFrameSpd(void);
    void SetSpecificFrame(int frame);
    int GetCurrentFrame(void);
    int GetSpecificFrame(void);
    int GetFlip(void);
    void SetFlip(int value);

    //Animation
    bool current_ani_check;
    bool skipFirstAnimation;
	Timer m_timer;
	int m_frames;
	float m_frameUV;
	int currentFrame;
	float m_frameSpeed;

	// Effect helper function
	void SetBlurToggle(bool toggle);
	bool GetBlurToggle(void) const;
	float GetBlurAmount(void) const;
	void SetBlurAmount(float amount);
	void SetInverseToggle(bool toggle);
	bool GetInverseToggle(void) const;
	void SetSobelToggle(bool toggle);
	bool GetSobelToggle(void) const;
	float GetSobelAmount(void) const;
	void SetSobelAmount(float amount);
	void SetWaveToggle(bool toggle);
	bool GetWaveToggle(void) const;
	const vec2& GetWavePhase(void) const;
	void SetWavePhase(const vec2& phase);
	void SetRippleToggle(bool ripple);
	bool GetRippleToggle(void) const;

private:
    
	vec4 m_color;
	float m_dtOffset;

    bool animation_check;
    int specificFrame;
    int flip;
    bool drawingCheck;
	
	bool m_ripple;
	bool m_inverse;
	bool m_blur;
	bool m_sobel;
	bool m_wave;
	float m_sobelAmount;
	float m_blurAmount;
	vec2 m_phase;
};

#endif // _SPRITE_H_