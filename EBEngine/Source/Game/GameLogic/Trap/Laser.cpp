/******************************************************************************/
/*!
\file   Laser.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2016/12/04(yy/mm/dd)

\description
Contains Laser logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Laser.h"
#include "../../../BaseData/BaseEnigne.h"
#include "BasicTrap.h"
#include "../Particle/ParticleManager.h"
#include <string>

/******************************************************************************/
/*!
\brief - LaserBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* LaserBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Laser(Owner, key);
}

/******************************************************************************/
/*!
\brief - Laser constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Laser::Laser(Object* Owner, LogicType key)
: GameLogic(Owner, key), m_LaserOwner(nullptr)
{}

/******************************************************************************/
/*!
\brief - Load Laser info
\param data - json parser
*/
/******************************************************************************/
void Laser::Load(const Json::Value& data)
{
    // Set Range
    if (data.isMember("Range") &&
        data["Range"].isNumeric())
        m_range = data["Range"].asFloat();
}

/******************************************************************************/
/*!
\brief - Initialize Laser info
*/
/******************************************************************************/
void Laser::Init(void)
{
    if (!m_LaserOwner)
    {
        if (m_range == 0)
            m_range = 200;

        //Get the player data
        m_OBM->GetObjects(AT_PLAYER, player);
        if (player.size())
            player_id = player[0]->GetID();
        else
            player_id = 0;

		vec3 pos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
		m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(pos.x + 75, pos.y, pos.z));

        m_LaserOwner = new Object(AT_NONE, m_OBM);

        m_LaserOwner->AddComponent(ComponentFactory::CreateComponent(m_LaserOwner, CT_TRANSFORM));
        m_LaserOwner->AddComponent(ComponentFactory::CreateComponent(m_LaserOwner, CT_SPRITE));
        m_LaserOwner->AddComponent(ComponentFactory::CreateComponent(m_LaserOwner, CT_RIGIDBODY));

		m_LaserOwner->GetComponent<RigidBody>(CT_RIGIDBODY)->ActivateResponse(false);

        m_LaserOwner->AddLogic(LogicFactory::CreateLogic(m_LaserOwner, DAMAGE));

        m_rayTrnsfrm = m_LaserOwner->GetComponent<Transform>(CT_TRANSFORM);
        m_rayTrnsfrm->SetScale(vec3(m_range, 10, 0));

        m_Ray = m_LaserOwner->GetComponent<Sprite>(CT_SPRITE);
        m_Ray->SetTexture(m_OBM->GetTexture("Laser"));
        m_Ray->SetColor(vec4(1, 1, 1, 1));
        m_Ray->SetFrame(10);
        m_Ray->SetFrameSpd(100.f);
        m_Ray->SetAnimation(false);

        vec3 tmpPos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
        vec3 tmpScl = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetScale();

        m_OBM->AddObject(m_LaserOwner);

		// Set Sound
		std::string tmp("laser");
		tmp += std::to_string(m_OwnerID);

		m_OBM->GetGameSound()->AddAudio(tmp.c_str(), "laser");
		m_sound = m_OBM->GetGameSound()->GetAudio(tmp.c_str());
		m_sound->SetVolume(m_GSM->GetGameData()->volume);
		soundTime = 0.f;
		soundToggle = true;
		runningTime = m_Owner->GetLogic<BasicTrap>(TRAP)->GetRunningTime();

		m_time = 0;
    }
}

/******************************************************************************/
/*!
\brief - Update Laser info
\param dt - delta time
*/
/******************************************************************************/
void Laser::Update(float dt)
{
	if (m_GSM->GetGameData()->immortal == false)
	{
		if (m_Owner->GetLogic<BasicTrap>(TRAP)->CheckActive() == true)
		{
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetSpecificFrame(1);
			m_time = 0;
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(2, 1.f, 1.f, 1.f));

			vec3 tmpPos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
			vec3 tmpScl = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetScale();
			m_Ray->SetAnimation(true);

			//Play the sound
			if (soundToggle == true && m_GSM->GetGameData()->player_Active == true)
			{
				m_sound->SetPosition(tmpPos);
				m_sound->Play();
				soundToggle = false;
			}
			else
			{
				// If the sound is playing.
				soundTime += dt;
				if (soundTime > runningTime)
				{
					soundTime = 0.f;
					m_sound->Stop();
					soundToggle = true;
				}
			}

			if (m_rayTrnsfrm->GetRotation() == 90)
				m_rayTrnsfrm->SetPosition(vec3(tmpPos.x, tmpPos.y + ((m_range + tmpScl.y) / 2), tmpPos.z));
			else if (m_rayTrnsfrm->GetRotation() == 180)
				m_rayTrnsfrm->SetPosition(vec3(tmpPos.x - ((m_range + tmpScl.x) / 2), tmpPos.y, tmpPos.z));
			else if (m_rayTrnsfrm->GetRotation() == 270)
				m_rayTrnsfrm->SetPosition(vec3(tmpPos.x, tmpPos.y - ((m_range + tmpScl.y) / 2), tmpPos.z));
			else
			{
				m_rayTrnsfrm->SetPosition(vec3(tmpPos.x, tmpPos.y, tmpPos.z));
				//m_rayTrnsfrm->SetPosition(vec3(tmpPos.x + ((m_range + tmpScl.x) / 2), tmpPos.y, tmpPos.z));
			}
			m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->Restore();

		}
		else
		{
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetSpecificFrame(0);
			soundTime = 0.f;
			soundToggle = true;
			m_sound->Stop();
			m_Ray->SetAnimation(false);
			m_rayTrnsfrm->SetPosition(vec3(1, 1000, 0));

			m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->SetParticleQuit(true);

			m_time += dt;
			float c1 = (m_time / m_Owner->GetLogic<BasicTrap>(TRAP)->GetWaitingTime()) * 2;

			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(c1, 1.f, 1.f, 1.f));
		}
	}

}

/******************************************************************************/
/*!
\brief - Shutdown Laser info
*/
/******************************************************************************/
void Laser::Shutdown(void)
{
}

/******************************************************************************/
/*!
\brief - Unload Laser info
*/
/******************************************************************************/
void Laser::Unload(void)
{
}
