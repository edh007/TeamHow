/******************************************************************************/
/*!
\file   Damage.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/10/27(yy/mm/dd)

\description
Contains Damage logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Damage.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - DamageBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* DamageBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Damage(Owner, key);
}

/******************************************************************************/
/*!
\brief - Damage constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Damage::Damage(Object* Owner, LogicType key)
: GameLogic(Owner, key), m_damage(1), m_slow(1.f),
	m_permanent(true), m_life(1), m_maintain(false),
	m_time(0), m_active(true)
{}

/******************************************************************************/
/*!
\brief - Load Damage info
\param data - json parser
*/
/******************************************************************************/
void Damage::Load(const Json::Value& data)
{
	if (data.isMember("Active") &&
		data["Active"].isBool())
		m_active = data["Active"].asBool();

	if (data.isMember("Life") &&
		data["Life"].isInt())
		m_life = data["Life"].asInt();

	if (data.isMember("Damage") &&
		data["Damage"].isInt())
		m_damage = data["Damage"].asInt();

	if (data.isMember("Slow") &&
		data["Slow"].isNumeric())
		m_slow = data["Slow"].asFloat();

	if (data.isMember("Time") &&
		data["Time"].isNumeric())
		m_time = data["Time"].asFloat();

	if (data.isMember("Permanent") &&
		data["Permanent"].isBool())
		m_permanent = data["Permanent"].asBool();

	if (data.isMember("Maintain") &&
		data["Maintain"].isBool())
		m_maintain = data["Maintain"].asBool();
}

/******************************************************************************/
/*!
\brief - Initialize Damage info
*/
/******************************************************************************/
void Damage::Init(void)
{
	if (m_maintain)
		m_timer.StartTime();
}

/******************************************************************************/
/*!
\brief - Update Damage info
\param dt - delta time
*/
/******************************************************************************/
void Damage::Update(float /*dt*/)
{
	if (!m_permanent && m_maintain && m_timer.GetElapsedTime() > m_time)
		m_life = 0;
}

/******************************************************************************/
/*!
\brief - Shutdown Damage info
*/
/******************************************************************************/
void Damage::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload Damage info
*/
/******************************************************************************/
void Damage::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Settor life
\param life
*/
/******************************************************************************/
void Damage::SetLife(int life)
{
	m_life = life;
}

/******************************************************************************/
/*!
\brief - Gettor life
\return m_life
*/
/******************************************************************************/
int Damage::GetLife(void) const
{
	return m_life;
}

/******************************************************************************/
/*!
\brief - Settor permanent
\param permanent
*/
/******************************************************************************/
void Damage::SetPermanent(bool permanent)
{
	m_permanent = permanent;
}

/******************************************************************************/
/*!
\brief - Gettor permanent
\return m_permanent
*/
/******************************************************************************/
bool Damage::GetPermanent(void) const
{
	return m_permanent;
}

/******************************************************************************/
/*!
\brief - Settor damage
\param damage
*/
/******************************************************************************/
void Damage::SetDamage(int damage)
{
	m_damage = damage;
}

/******************************************************************************/
/*!
\brief - Gettor damage
\return m_damage
*/
/******************************************************************************/
int Damage::GetDamage(void) const
{
	return m_damage;
}

/******************************************************************************/
/*!
\brief - Settor slow
\param slow
*/
/******************************************************************************/
void Damage::SetSlow(float slow)
{
	m_slow = slow;
}

/******************************************************************************/
/*!
\brief - Gettor slow
\return m_slow
*/
/******************************************************************************/
float Damage::GetSlow(void) const
{
	return m_slow;
}

/******************************************************************************/
/*!
\brief - Settor maintain, and time
\param maintain
\param time
*/
/******************************************************************************/
void Damage::SetMaintain(bool maintain, float time)
{
	m_time = time;
	m_maintain = maintain;
}

/******************************************************************************/
/*!
\brief - Settor active
\param active
*/
/******************************************************************************/
void Damage::ActivateDamage(bool active)
{
	m_active = active;
}

/******************************************************************************/
/*!
\brief - Gettor active toggle
\return m_active
*/
/******************************************************************************/
bool Damage::GetActiveToggle(void) const
{
	return m_active;
}

/******************************************************************************/
/*!
\brief - Gettor maintain
\return m_maintain
*/
/******************************************************************************/
bool Damage::GetMaintain(void) const
{
	return m_maintain;
}

/******************************************************************************/
/*!
\brief - Gettor time
\return m_time
*/
/******************************************************************************/
float Damage::GetMaintainTime(void) const
{
	return m_time;
}
