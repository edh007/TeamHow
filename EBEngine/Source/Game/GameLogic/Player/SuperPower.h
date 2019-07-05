/******************************************************************************/
/*!
\file   SuperPower.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/11/28(yy/mm/dd)

\description
Contains SuperPower logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _SUPERPOWER_H_
#define _SUPERPOWER_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"
#include <vector>

class SuperPowerBuilder : public LogicBuilder
{

public:
	SuperPowerBuilder() {};
	virtual ~SuperPowerBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};


class SuperPower : public GameLogic
{
public:

	SuperPower(Object* Owner, LogicType key);
	virtual ~SuperPower(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

	void Punch(void);
	void Search(void);
	
	std::vector<Object*> m_enemies;
	vec3 m_position, m_scale;
	Object* m_fist;
	
	// Search info
	bool m_search, m_init;
	float dt_Stack;
};

#endif // _SUPERPOWER_H_
