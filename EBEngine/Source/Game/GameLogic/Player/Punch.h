/******************************************************************************/
/*!
\file   Punch.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/02/22(yy/mm/dd)

\description
Contains Punch logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _PUNCH_H_
#define _PUNCH_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class RigidBody;
class PunchBuilder : public LogicBuilder
{

public:
	PunchBuilder() {};
	virtual ~PunchBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Audio;

class Punch : public GameLogic
{
public:

	Punch(Object* Owner, LogicType key);
	virtual ~Punch(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

	
	RigidBody* m_body;

	Audio* m_hit[4];
	Audio* m_sound;
	float soundTime, hitTime;
	bool soundToggle, hitToggle;
	std::vector<Object*> wall;
	
};

#endif // _PUNCH_H_
