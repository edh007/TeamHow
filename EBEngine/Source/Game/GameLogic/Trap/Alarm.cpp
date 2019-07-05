/******************************************************************************/
/*!
\file   Alarm.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/08(yy/mm/dd)

\description
Contains Alarm logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Alarm.h"
#include "../../../BaseData/BaseEnigne.h"
#include "BasicTrap.h"

/******************************************************************************/
/*!
\brief - AlarmBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* AlarmBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Alarm(Owner, key);
}

/******************************************************************************/
/*!
\brief - Alarm constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Alarm::Alarm(Object* Owner, LogicType key)
: GameLogic(Owner, key)
{}

/******************************************************************************/
/*!
\brief - Load Alarm info
\param data - json parser
*/
/******************************************************************************/
void Alarm::Load(const Json::Value& data)
{
    // Set Range
    if (data.isMember("Speed") &&
        data["Speed"].isNumeric())
        searchSpd = data["Speed"].asFloat();
}

/******************************************************************************/
/*!
\brief - Initialize Alarm info
*/
/******************************************************************************/
void Alarm::Init(void)
{
    m_object = new Object(AT_NONE, m_OBM);

    m_object->AddComponent(ComponentFactory::CreateComponent(m_object, CT_TRANSFORM));
    m_object->AddComponent(ComponentFactory::CreateComponent(m_object, CT_SPRITE));
    m_object->AddComponent(ComponentFactory::CreateComponent(m_object, CT_RIGIDBODY));

	m_object->AddLogic(LogicFactory::CreateLogic(m_object, SLOW));
    m_trs = m_object->GetComponent<Transform>(CT_TRANSFORM);
    m_sprite = m_object->GetComponent<Sprite>(CT_SPRITE);
    m_body = m_object->GetComponent<RigidBody>(CT_RIGIDBODY);

    m_trs->SetScale(vec3(25, 25, 0));
    vec3 m_pos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
    m_trs->SetPosition(vec3(m_pos.x, m_pos.y, -1));

    m_sprite->SetTexture(m_GSM->GetGLManager()->GetTexture("AreaCircle"));
    m_sprite->SetColor(vec4(0.f, 1.f, 0.f, 1.f));

    m_body->ActivateResponse(false);
    m_body->SetShape(BALL);
    m_body->SetScale(vec3(25, 25, 0));

    m_OBM->AddObject(m_object);

    m_Active = false;

	// Set Sound
	std::string tmp("radar");
	tmp += std::to_string(m_OwnerID);

	m_OBM->GetGameSound()->AddAudio(tmp.c_str(), "radar");
	m_sound = m_OBM->GetGameSound()->GetAudio(tmp.c_str());
	m_sound->SetVolume(m_GSM->GetGameData()->volume);
	m_sound->SetPosition(m_pos);
	soundTime = 0.f;
	soundToggle = false;
	m_GSM->GetGameData()->radarToggle = false;
}

/******************************************************************************/
/*!
\brief - Update Alarm info
\param dt - delta time
*/
/******************************************************************************/
void Alarm::Update(float dt)
{
	
    TrapCondition tc = m_Owner->GetLogic<BasicTrap>(TRAP)->trapCondition;
	dt = dt * m_Owner->GetdtOffset();
    switch (tc)
    {
    case ACTIVATING:
        if (m_OBM->HasObject(m_GSM->GetGameData()->player_id))
        {
            vec3 m_pos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
            vec3 player_pos = m_GSM->GetGameData()->player_pos;
            vec3 m_scale = m_trs->GetScale();

            m_trs->SetScale(m_scale + (dt * searchSpd));
            m_body->SetScale(m_scale + (dt * searchSpd));
            
            std::vector<Object*> wall;
            wall.clear();
            m_OBM->GetObjects(AT_WALL, wall);

            bool between = true;

            for (auto it_wall : wall)
            {
                if (between)
                    between = m_OBM->GetGameWorld()->CollisionIntersect
                    (it_wall->GetComponent<RigidBody>(CT_RIGIDBODY), player_pos, m_pos);
                else
                    break;
            }

            if (m_body->IsCollidedWith(m_GSM->GetGameData()->player_id) && between)
            {
                //Move Enemies to the player's position
				m_GSM->GetGameData()->radarToggle = true;
				m_GSM->GetGameData()->footstack = 6.f;
				
            }

			if (m_GSM->GetGameData()->player_Active == true && m_sound->IsPlaying() == false)
				m_sound->Play();
        }
        break;
    case OPERATION:
        break;
    case CUTOFF:
		m_GSM->GetGameData()->radarToggle = false;
        m_trs->SetScale(vec3(25, 25, 0));
        m_body->SetScale(vec3(25, 25, 0));
        break;
    case WAITING:
        break;
    }
}

/******************************************************************************/
/*!
\brief - Shutdown Alarm info
*/
/******************************************************************************/
void Alarm::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload Alarm info
*/
/******************************************************************************/
void Alarm::Unload(void)
{

}
