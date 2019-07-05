/******************************************************************************/
/*!
\file   Web.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/10/11(yy/mm/dd)

\description
Contains Web logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _WEB_H_
#define _WEB_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class WebBuilder : public LogicBuilder
{

public:
	WebBuilder() {};
	virtual ~WebBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class RigidBody;
//! class Web from web shooter
class Web : public GameLogic
{
public:

	Web(Object* Owner, LogicType key);
	virtual ~Web(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	void SetRoot(bool from_spider);

	void SetDenominator(float dnmt);

private:

	// Shooting animation 
	RigidBody* m_body;

	vec3 m_scale;
	vec4 m_color;
	float m_scaleSpeed;
	float m_size;
	bool  m_undone, m_vanish;
	float m_dnmt;

	// Either from spider or not
	bool m_root;

	// Vainish animation
	//float dt_Stack;
};

#endif // _WEB_H_
