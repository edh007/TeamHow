/******************************************************************************/
/*!
\file   Laser.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2016/12/04(yy/mm/dd)

\description
Contains Laser logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _LASER_H_
#define _LASER_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class LaserBuilder : public LogicBuilder
{

public:
	LaserBuilder() {};
	virtual ~LaserBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Sprite;
class Transform;
class RigidBody;
class Audio;

class Laser : public GameLogic
{
public:

	Laser(Object* Owner, LogicType key);
	virtual ~Laser(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:
    std::vector<Object*> player;
    int player_id;

	float m_time;
    Sprite* m_Ray;
    Transform* m_rayTrnsfrm;
    RigidBody* m_body;
    float waitTime;

    Object* m_LaserOwner;
    float m_range;

	Audio* m_sound;
	float soundTime;
	bool soundToggle;
	float runningTime;
};

#endif // _LASER_H_
