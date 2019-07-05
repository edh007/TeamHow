/******************************************************************************/
/*!
\file   TurretTarget.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/04/05(yy/mm/dd)

\description
Contains TurretTarget logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "TurretTarget.h"
#include "../../../BaseData/BaseEnigne.h"
#include "Lightning.h"
#include "../Enemy/Damage.h"

/******************************************************************************/
/*!
\brief - TurretTargetBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* TurretTargetBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new TurretTarget(Owner, key);
}

/******************************************************************************/
/*!
\brief - TurretTarget constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
TurretTarget::TurretTarget(Object* Owner, LogicType key)
: GameLogic(Owner, key)
{}

/******************************************************************************/
/*!
\brief - Load TurretTarget info
\param data - json parser
*/
/******************************************************************************/
void TurretTarget::Load(const Json::Value& data)
{
	if (data.isMember("WaitingTime") &&
		data["WaitingTime"].isNumeric())
		m_waitingTime = data["WaitingTime"].asFloat();

	if (data.isMember("RunningTime") &&
		data["RunningTime"].isNumeric())
		m_runningTime = data["RunningTime"].asFloat();
}

/******************************************************************************/
/*!
\brief - Initialize TurretTarget info
*/
/******************************************************************************/
void TurretTarget::Init(void)
{
	m_object = new Object(AT_NONE, m_OBM);

	m_object->AddComponent(ComponentFactory::CreateComponent(m_object, CT_TRANSFORM));
	m_object->AddComponent(ComponentFactory::CreateComponent(m_object, CT_SPRITE));
	m_object->AddComponent(ComponentFactory::CreateComponent(m_object, CT_RIGIDBODY));

	m_trs = m_object->GetComponent<Transform>(CT_TRANSFORM);
	m_sprite = m_object->GetComponent<Sprite>(CT_SPRITE);
	m_body  = m_object->GetComponent<RigidBody>(CT_RIGIDBODY);

	m_trs->SetScale(vec3(100, 100, 0));
	m_trs->SetPosition(vec3(1000, 1000, 0));
	m_trs->SetRotation(0.f);

	m_body->ActivateResponse(false);
	m_body->SetShape(BALL);
	m_body->SetScale(vec3(80,80,0));

	m_object->AddLogic(LogicFactory::CreateLogic(m_object, SLOW));
	m_object->AddLogic(LogicFactory::CreateLogic(m_object, DAMAGE));
	m_object->AddLogic(LogicFactory::CreateLogic(m_object, LIGHTNING));

	m_sprite->SetTexture(m_GSM->GetGLManager()->GetTexture("Mark"));
	m_OBM->AddObject(m_object);

	m_Active = false;
	m_AttackActive = false;

	// Set Sound
	std::string tmp("lightning");
	tmp += std::to_string(m_OwnerID);

	m_OBM->GetGameSound()->AddAudio(tmp.c_str(), "lightning");
	m_sound = m_OBM->GetGameSound()->GetAudio(tmp.c_str());
	m_sound->SetVolume(m_GSM->GetGameData()->volume);
	soundTime = 0.f;
	soundToggle = true;
}

/******************************************************************************/
/*!
\brief - Update TurretTarget info
\param dt - delta time
*/
/******************************************************************************/
void TurretTarget::Update(float dt)
{
	if (m_GSM->GetGameData()->immortal == false)
	{
		if (m_AttackActive == true)
		{
			m_trs->SetRotation(m_trs->GetRotation() + m_rotSpeed);
			m_time += dt;
			if (m_time > m_runningTime)
			{
				m_AttackActive = false;
				m_time = 0;
				m_rotSpeed = 0;

			}
		}

		else if (m_Active == true)
		{
			m_sprite->SetColor(vec4(1, 1, 1, m_time / 2));
			m_time += dt;
			m_trs->SetRotation(m_trs->GetRotation() + (m_time * 6));
			m_object->GetLogic<Damage>(DAMAGE)->ActivateDamage(false);

			if (m_time > m_waitingTime)
			{
				m_sprite->SetColor(vec4(1, 1, 1, m_time / 2));
				m_rotSpeed = m_time * 6;
				m_time = 0;
				m_object->GetLogic<Lightning>(LIGHTNING)->SetActiveToggle(true);
				m_object->GetLogic<Damage>(DAMAGE)->ActivateDamage(true);
				m_Active = false;
				m_AttackActive = true;

				if (m_GSM->GetGameData()->player_Active == true)
				{
					m_sound->SetPosition(m_GSM->GetGameData()->cameraPos);
					m_sound->Play();
				}
			}
		}
		else
		{
			m_sprite->SetColor(vec4(0, 0, 0, 0));
			m_time = 0;
			SetActiveToggle(false);
			m_AttackActive = false;
			m_object->GetLogic<Lightning>(LIGHTNING)->SetActiveToggle(false);
			m_object->GetLogic<Damage>(DAMAGE)->ActivateDamage(false);
		}
	}
}

/******************************************************************************/
/*!
\brief - Shutdown TurretTarget info
*/
/******************************************************************************/
void TurretTarget::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload TurretTarget info
*/
/******************************************************************************/
void TurretTarget::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - set the active as true or false
*/
/******************************************************************************/
void TurretTarget::SetActiveToggle(bool _gettor)
{
	m_Active = _gettor;
}

/******************************************************************************/
/*!
\brief - return active
*/
/******************************************************************************/
bool TurretTarget::GetActiveToggle(void)
{
	return m_Active;
}

/******************************************************************************/
/*!
\brief - set position
*/
/******************************************************************************/
void TurretTarget::SetPosition(vec3 _gettor)
{
	m_trs->SetPosition(_gettor);
}

/******************************************************************************/
/*!
\brief - get position
*/
/******************************************************************************/
vec3 TurretTarget::GetPosition(void)
{
	return m_trs->GetPosition();
}

/******************************************************************************/
/*!
\brief - set the active as true or false
*/
/******************************************************************************/
void TurretTarget::SetActiveAttackToggle(bool _gettor)
{
	m_AttackActive = _gettor;
}

/******************************************************************************/
/*!
\brief - return active
*/
/******************************************************************************/
bool TurretTarget::GetActiveAttackToggle(void)
{
	return m_AttackActive;
}