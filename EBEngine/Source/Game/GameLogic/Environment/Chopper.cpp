/******************************************************************************/
/*!
\file   Chopper.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/05/24(yy/mm/dd)

\description
Contains Chopper logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Chopper.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - ChopperBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* ChopperBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Chopper(Owner, key);
}

/******************************************************************************/
/*!
\brief - Chopper constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Chopper::Chopper(Object* Owner, LogicType key)
: GameLogic(Owner, key), m_propeller(nullptr), m_activate(false), m_chopperGone(false),
m_audio(nullptr)
{}

/******************************************************************************/
/*!
\brief - Load Chopper info
\param data - json parser
*/
/******************************************************************************/
void Chopper::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize Chopper info
*/
/******************************************************************************/
void Chopper::Init(void)
{
	m_propeller = new Object(AT_CHOPPER, m_OBM);
	m_propeller->AddComponent(ComponentFactory::CreateComponent(m_propeller, CT_SPRITE));
	m_propeller->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Propeller"));
	m_propeller->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(0, 0, 0, 0));
	m_propeller->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(250, 250));
	
	m_OBM->AddObject(m_propeller);
	m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(500,500));

	m_OBM->GetGameSound()->AddAudio("chopper", "chopper");
	m_audio = m_OBM->GetAudio("chopper");
	m_audio->SetVolume(m_GSM->GetGameData()->volume);
}

/******************************************************************************/
/*!
\brief - Update Chopper info
\param dt - delta time
*/
/******************************************************************************/
void Chopper::Update(float dt)
{
	if (m_GSM->GetGameData()->player_chopper) {
		if ((!m_audio->IsPlaying()) && (m_GSM->GetGameData()->gamegradeCondition == false))
			m_audio->Play();

		static float bodySpeed = 250.f, pellerSpeed = 500.f, enter = 100.f;
		static vec3 fadeOut(0, 1);

		m_propeller->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 1, 1, 1));
		vec3 m_position = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
		vec3 player_pos = m_GSM->GetGameData()->player_pos;

		m_audio->SetPosition(player_pos);

		// Reaching to the player...
		if (Math::Distance_pt(m_position, player_pos) > enter
			&& m_GSM->GetGameData()->gameclearCondition) {
			vec3 velocity = (player_pos - m_position).Normalize();

			vec3 newPos = m_position + (velocity) * dt * bodySpeed;
			newPos.z = 10.f;
			float head = Math::Degree_pt(player_pos, m_position);
			m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetRotation(head);
			m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(newPos);
		}

		else if (Math::Distance_pt(m_position, player_pos) < enter) {
			vec3 newPos = m_position - (fadeOut * bodySpeed * dt);
			newPos.z = 10.f;
			float head = Math::Degree_pt(player_pos, m_position);
			m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetRotation(head);
			m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(newPos);
			m_GSM->GetGameData()->player->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4());
		}

		// Propeller's working and following the chopper body.
		float degree = m_propeller->GetComponent<Transform>(CT_TRANSFORM)->GetRotation();
		static vec3 zOffset(0, 0, .1f);
		m_propeller->GetComponent<Transform>(CT_TRANSFORM)->SetRotation(degree + dt * pellerSpeed);
		m_propeller->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(m_position + zOffset);
	}
}

/******************************************************************************/
/*!
\brief - Shutdown Chopper info
*/
/******************************************************************************/
void Chopper::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload Chopper info
*/
/******************************************************************************/
void Chopper::Unload(void)
{

}
