/******************************************************************************/
/*!
\file   Turret.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2016/12/04(yy/mm/dd)

\description
Contains Turret logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _TURRET_H_
#define _TURRET_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"
#include "../../../Engine/GameSystem/Physics/RigidBody/RigidBody.h"

class TurretBuilder : public LogicBuilder
{

public:
	TurretBuilder() {};
	virtual ~TurretBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Turret : public GameLogic
{
public:

	Turret(Object* Owner, LogicType key);
	virtual ~Turret(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:
    bool active;
    int player_id;
    std::vector<Object*> player;
    float activeTime;
    float collidedTime;
    //Sprite* shooter;
    RigidBody* body;
};

#endif // _TURRET_H_
