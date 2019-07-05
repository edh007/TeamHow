/******************************************************************************/
/*!
\file   Player.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/09/26(yy/mm/dd)

\description
Contains Player logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"
#include "../../../Engine/Utilities/Time.h"

enum PlayerCondition {SNEAK, RUN, STOP};
class RigidBody;
class PlayerBuilder : public LogicBuilder
{

public:
	PlayerBuilder() {};
	virtual ~PlayerBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;
};

class Audio;
class Texture;

class Player : public GameLogic
{
public:

	Player(Object* Owner, LogicType key);
	virtual ~Player(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	void SetSpeed(float speed);
	float GetSpeed(void) const;
	int GetLife(void) const;
	void SetLife(int life);
	float GetSlow(void) const;
    bool GetDamage(void) const;

	PlayerCondition GetConidition(void) const;
	
private:

	void DamagedEffect(float dt);
	void Controller(float dt);
	void FootStack(float dt);
	void SuperPunchEffect(float dt);
	vec4 m_color;
	bool tc[3];

	// Player chracter info
	int m_life, comeback;
	float m_slow, m_accel, m_footstack, 
		m_fsOffset;
	bool m_playToggle, m_frameChecker;
	PlayerCondition m_condition;

	// Audio info
	Audio* footstep, *death;
	int sound_term;
	
	// Player damage info
	Timer m_timer;
	float dt_Stack, m_respone, m_blink;
	bool m_damaged, m_colorToggle, m_shakeToggle;

	// Player physics info
	float m_speed;
	vec3 velocity;
	vec3 m_position;

	// Player assistants
	RigidBody* m_body;
	Object* m_foot, *m_now;
};

#endif // _PLAYER_H_
