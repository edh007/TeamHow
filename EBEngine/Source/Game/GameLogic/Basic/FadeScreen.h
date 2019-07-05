/******************************************************************************/
/*!
\file   FadeScreen.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/04/04(yy/mm/dd)

\description
Contains FadeScreen logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _FADESCREEN_H_
#define _FADESCREEN_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

enum FADE_CONDITION {FADE_IN, FADE_ON, FADE_OUT};
class FadeScreenBuilder : public LogicBuilder
{

public:
	FadeScreenBuilder() {};
	virtual ~FadeScreenBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

//! Fade Screen class
class FadeScreen : public GameLogic
{
public:

	FadeScreen(Object* Owner, LogicType key);
	virtual ~FadeScreen(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	void SetGameOn(bool toggle);

private:

	bool m_gameOn;
	vec2 m_res;
	vec3 m_pos;
	vec4 m_color;
	float m_speed;
	FADE_CONDITION m_condition;
	Object* fade;
};

#endif // _FADESCREEN_H_
