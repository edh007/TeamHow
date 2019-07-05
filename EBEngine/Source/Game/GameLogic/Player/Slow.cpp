/******************************************************************************/
/*!
\file   Slow.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/11/07(yy/mm/dd)

\description
Contains Slow logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Slow.h"
#include "../Player/SuperPower.h"
#include "../../../BaseData/BaseEnigne.h"
#include "../Enemy/Enemy.h"

/******************************************************************************/
/*!
\brief - SlowBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* SlowBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Slow(Owner, key);
}

/******************************************************************************/
/*!
\brief - Slow constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Slow::Slow(Object* Owner, LogicType key)
: GameLogic(Owner, key), 
m_slowActivated(false), m_offset(.5f),m_toggle(true), gauge(0)
{}

/******************************************************************************/
/*!
\brief - Load Slow info
\param data - json parser
*/
/******************************************************************************/
void Slow::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize Slow info
*/
/******************************************************************************/
void Slow::Init(void)
{

}

/******************************************************************************/
/*!
\brief - Update Slow info
\param dt - delta time
*/
/******************************************************************************/
void Slow::Update(float /*dt*/)
{
	// Make sure that there is a player
	if (m_OBM->HasObject(m_GSM->GetGameData()->player_id))
	{
		float offset = 1.f;

		// Make every objects contains this logic
		// will be slow
		if (m_GSM->GetGameData()->tmToggle
			&& m_toggle)
		{
			// Player gets speed advantage
			if (m_OwnerID ==
				m_GSM->GetGameData()->player_id)
				offset = .5f;

			// If ther object is enemy and the type is anti slow,
			// boost the speed!
			else if (m_Owner->HasLogic(ENEMY)
				&& m_Owner->GetLogic<Enemy>(ENEMY)->GetEnemyType() == ANTI_TIMER)
				offset = 20.f;

			// And the others...
			else
				offset = .1f;
			m_slowActivated = true;
		}

		else
			m_slowActivated = false;

		m_Owner->SetdtOffset(offset);
	}
}

/******************************************************************************/
/*!
\brief - Shutdown Slow info
*/
/******************************************************************************/
void Slow::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload Slow info
*/
/******************************************************************************/
void Slow::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Activate Slow
\param toggle
*/
/******************************************************************************/
void Slow::ActivateSlow(bool toggle)
{
	m_toggle = toggle;
}

/******************************************************************************/
/*!
\brief - Get Slow Toggle
\return m_toggle
*/
/******************************************************************************/
bool Slow::GetSlowToggle(void) const
{
	return m_toggle;
}

/******************************************************************************/
/*!
\brief - Get Slow toggle
\return m_slowActivated
*/
/******************************************************************************/
bool Slow::IsSlow(void) const
{
	return m_slowActivated;
}

/******************************************************************************/
/*!
\brief - Set Slow Offset
\param offset
*/
/******************************************************************************/
void Slow::SetSlowOffset(float offset)
{
	m_offset = offset;
}

/******************************************************************************/
/*!
\brief - Get Slow Offset
\return m_offset
*/
/******************************************************************************/
float Slow::GetSlowOffset(void) const
{
	return m_offset;
}
