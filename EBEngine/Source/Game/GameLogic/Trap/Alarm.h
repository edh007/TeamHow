/******************************************************************************/
/*!
\file   Alarm.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/08(yy/mm/dd)

\description
Contains Alarm logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _ALARM_H_
#define _ALARM_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class AlarmBuilder : public LogicBuilder
{

public:
	AlarmBuilder() {};
	virtual ~AlarmBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Sprite;
class RigidBody;
class Transform;
class Audio;

class Alarm : public GameLogic
{
public:

	Alarm(Object* Owner, LogicType key);
	virtual ~Alarm(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:
    //float m_range;
    bool m_Active;

    Object* m_object;
    Sprite* m_sprite;
    Transform* m_trs;
    RigidBody* m_body;

    float searchSpd;

	Audio* m_sound;
	float soundTime;
	bool soundToggle;
};

#endif // _ALARM_H_
