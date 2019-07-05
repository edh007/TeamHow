/******************************************************************************/
/*!
\file   Damage.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/10/27(yy/mm/dd)

\description
Contains Damage logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _DAMAGE_H_
#define _DAMAGE_H_

#include "../../../Engine/Utilities/Time.h"
#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class DamageBuilder : public LogicBuilder
{

public:
	DamageBuilder() {};
	virtual ~DamageBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Damage : public GameLogic
{
public:

	Damage(Object* Owner, LogicType key);
	virtual ~Damage(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	void SetDamage(int damage);
	int GetDamage(void) const;

	void SetSlow(float slow);
	float GetSlow(void) const;

	void SetLife(int life);
	int GetLife(void) const;

	bool GetPermanent(void) const;
	void SetPermanent(bool permanent);

	bool GetMaintain(void) const;
	float GetMaintainTime(void) const;
	void SetMaintain(bool maintain, float time = 0.f);

	void ActivateDamage(bool active);
	bool GetActiveToggle(void) const;

private:

	Timer m_timer;
	float m_time;
	bool m_permanent;
	bool m_maintain;
	bool m_active;
	int m_life;
	int m_damage;
	float m_slow;

};

#endif // _DAMAGE_H_
