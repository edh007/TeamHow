/******************************************************************************/
/*!
\file   Target.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2016/11/08(yy/mm/dd)

\description
Contains Target logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Target.h"
#include "../../../BaseData/BaseEnigne.h"
#include "../HUD/Arrow.h"
#include "../Particle/ParticleManager.h"

/******************************************************************************/
/*!
\brief - TargetBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* TargetBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Target(Owner, key);
}

/******************************************************************************/
/*!
\brief - Target constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Target::Target(Object* Owner, LogicType key)
: GameLogic(Owner, key)
{}

/******************************************************************************/
/*!
\brief - Load Target info
\param data - json parser
*/
/******************************************************************************/
void Target::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize Target info
*/
/******************************************************************************/
void Target::Init(void)
{
	m_OBM->GetObjects(AT_PLAYER, player);

	if (player.size())
	{
		player_id = player[0]->GetID();
	}
	else
		player_id = 0;
	playerGet = false;
	
	// TODO
	// this is for test
	//m_GSM->GetGameData()->unlockTM = true;
	//m_GSM->GetGameData()->unlockSearch = true;

	// Set Sound
	std::string tmp("GettingItem");
	tmp += std::to_string(m_OwnerID);

	m_OBM->GetGameSound()->AddAudio(tmp.c_str(), "GettingItem");
	m_sound = m_OBM->GetGameSound()->GetAudio(tmp.c_str());
	m_sound->SetVolume(m_GSM->GetGameData()->volume);
	soundTime = 0.f;
	soundToggle = true;
	m_GSM->GetGameData()->createTablet = false;
}

/******************************************************************************/
/*!
\brief - Update Target info
\param dt - delta time
*/
/******************************************************************************/
void Target::Update(float /*dt*/)
{
	if (playerGet == false)
	{
		if (m_OBM->HasObject(player_id))
		{
			m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->Restore();

			if (player[0]->GetComponent<RigidBody>(CT_RIGIDBODY)->IsCollidedWith(m_Owner->GetID()))
			{
				m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->SetActive(false);
				playerGet = true;
				m_GSM->GetGameData()->createTablet = true;
				m_Owner->GetComponent<RigidBody>(CT_RIGIDBODY)->ActivateMove(false);
				m_Owner->GetComponent<RigidBody>(CT_RIGIDBODY)->ActivateCollider(false);
				m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(2000.f, 0.f, 0.f));
				m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(0.f,0.f,0.f,0.f));
				m_Owner->GetLogic<Arrow>(ARROW)->SetToggle(false);

				m_sound->SetPosition(m_GSM->GetGameData()->cameraPos);
				m_sound->Play();

				if (m_GSM->GetCurrentState() == ST_TUTORIALS_4
					&& !m_GSM->GetGameData()->unlockTM)
					m_GSM->GetGameData()->unlockTM = true;

				else if (m_GSM->GetCurrentState() == ST_TUTORIALS_6
					&& !m_GSM->GetGameData()->unlockSearch)
					m_GSM->GetGameData()->unlockSearch = true;
			}
		}
	}

	else
	{
		
		//m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(m_OBM->GetGameScene()->GetCameraPos() + vec3(-475.f, 180.f, 0.f));
	}
}

/******************************************************************************/
/*!
\brief - Shutdown Target info
*/
/******************************************************************************/
void Target::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload Target info
*/
/******************************************************************************/
void Target::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Check Player has Target or not to open the door
*/
/******************************************************************************/
bool Target::CheckItem(void)
{
	return playerGet;
}

/******************************************************************************/
/*!
\brief - set true if the player has the Target to open the door
*/
/******************************************************************************/
void Target::SetItem(bool value)
{
	playerGet = value;
}