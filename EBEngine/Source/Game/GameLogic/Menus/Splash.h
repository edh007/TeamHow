/******************************************************************************/
/*!
\file   Splash.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/11/15(yy/mm/dd)

\description
Contains Splash logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _SPLASH_H_
#define _SPLASH_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class SplashBuilder : public LogicBuilder
{

public:
	SplashBuilder() {};
	virtual ~SplashBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

//! Splash screen
class Splash : public GameLogic
{
public:

	Splash(Object* Owner, LogicType key);
	virtual ~Splash(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

	vec3 m_res;
	vec4 m_color;
	bool toggle;
	int m_order;

};

#endif // _SPLASH_H_
