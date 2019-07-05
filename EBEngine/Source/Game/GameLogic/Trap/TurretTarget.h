/******************************************************************************/
/*!
\file   TurretTarget.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/04/05(yy/mm/dd)

\description
Contains TurretTarget logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _TURRETTARGET_H_
#define _TURRETTARGET_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class TurretTargetBuilder : public LogicBuilder
{

public:
	TurretTargetBuilder() {};
	virtual ~TurretTargetBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Transform;
class Sprite;
class RigidBody;
class Audio;

class TurretTarget : public GameLogic
{
public:

	TurretTarget(Object* Owner, LogicType key);
	virtual ~TurretTarget(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	void SetActiveToggle(bool _gettor);
	bool GetActiveToggle(void);
	void SetActiveAttackToggle(bool _gettor);
	bool GetActiveAttackToggle(void);
	void SetPosition(vec3 _gettor);
	vec3 GetPosition(void);

private:
	bool m_AttackActive;
	bool m_Active;
	Sprite* m_sprite;
	Object* m_object;
	Transform* m_trs;
	RigidBody* m_body;

	float m_time;
	float m_waitingTime;
	float m_runningTime;

	Audio* m_sound;
	float soundTime;
	bool soundToggle;

	float m_rotSpeed;
};

#endif // _TURRETTARGET_H_
