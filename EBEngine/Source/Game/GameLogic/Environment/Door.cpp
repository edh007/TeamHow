/******************************************************************************/
/*!
\file   Door.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2016/11/08(yy/mm/dd)

\description
Contains Door logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Door.h"
#include "../../../BaseData/BaseEnigne.h"
#include "../Items/Target.h"
#include "../HUD/Arrow.h"
#include "../Particle/ParticleManager.h"

/******************************************************************************/
/*!
\brief - DoorBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* DoorBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Door(Owner, key);
}

/******************************************************************************/
/*!
\brief - Door constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Door::Door(Object* Owner, LogicType key)
: GameLogic(Owner, key), EndCondition(false), showingTablet(false)
{}

/******************************************************************************/
/*!
\brief - Load Door info
\param data - json parser
*/
/******************************************************************************/
void Door::Load(const Json::Value& data)
{
	if (!strcmp((data)["Piece"].asCString(), "C1"))
	{ 
		showingTablet = true;
		saveTexture = "Piece_1";
	}
	else if (!strcmp((data)["Piece"].asCString(), "C2"))
	{
		showingTablet = true;
		saveTexture = "Piece_C2";
	}
	else if (!strcmp((data)["Piece"].asCString(), "C3"))
	{
		showingTablet = true;
		saveTexture = "Piece_C3";
	}
	else if (!strcmp((data)["Piece"].asCString(), "C4"))
	{
		showingTablet = true;
		saveTexture = "Piece_C4";
	}
	else if (!strcmp((data)["Piece"].asCString(), "C5"))
	{
		showingTablet = true;
		saveTexture = "Piece_C5";
	}
	else if (!strcmp((data)["Piece"].asCString(), "C6"))
	{
		showingTablet = true;
		saveTexture = "Piece_C6";
	}
	else if (!strcmp((data)["Piece"].asCString(), "C7"))
	{
		showingTablet = true;
		saveTexture = "Piece_C7";
	}
}

/******************************************************************************/
/*!
\brief - Initialize Door info
*/
/******************************************************************************/
void Door::Init(void)
{
	m_OBM->GetObjects(AT_PLAYER, player);

	if (player.size())
		player_id = player[0]->GetID();
	else
		player_id = 0;

	m_OBM->GetObjects(AT_TARGET, talisman);

	if (talisman.size())
		talisman_id = talisman[0]->GetID();
	else
		talisman_id = 0;

	m_Owner->GetLogic<Arrow>(ARROW)->SetToggle(false);

	if (showingTablet == true)
	{
		m_object = new Object(AT_NONE, m_OBM);

		m_object->AddComponent(ComponentFactory::CreateComponent(m_object, CT_TRANSFORM));
		m_object->AddComponent(ComponentFactory::CreateComponent(m_object, CT_SPRITE));

		m_trs = m_object->GetComponent<Transform>(CT_TRANSFORM);
		m_sprite = m_object->GetComponent<Sprite>(CT_SPRITE);

		m_trs->SetPosition(vec3(2000.f, 0.f, 0.f));
		m_trs->SetScale(vec3(900, 636, 0));
		m_sprite->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.f));

		m_sprite->SetTexture(m_GSM->GetGLManager()->GetTexture(saveTexture.c_str()));
		m_OBM->AddObject(m_object);
		dtStack = 0.f;

        m_Skip = new Object(AT_NONE, m_OBM);
        m_Skip->AddComponent(ComponentFactory::CreateComponent(m_Skip, CT_TRANSFORM));
        m_Skip->AddComponent(ComponentFactory::CreateComponent(m_Skip, CT_TEXT));

        m_SkipText = m_Skip->GetComponent<Text>(CT_TEXT);
        m_SkipTrs = m_Skip->GetComponent<Transform>(CT_TRANSFORM);

        m_SkipTrs->SetPosition(vec3(1000, 1000, 0));
        m_SkipTrs->SetScale(vec3(1, 1, 0));

        m_SkipText->SetFontSize(30);
        m_SkipText->SetColor(vec4(1.f, 1.f, 1.f, 1.f));
        m_OBM->AddObject(m_Skip);
	}
}

/******************************************************************************/
/*!
\brief - Update Door info
\param dt - delta time
*/
/******************************************************************************/
void Door::Update(float dt)
{
	if (m_OBM->HasObject(talisman_id))
	{
		if (showingTablet == true && m_GSM->GetGameData()->createTablet == true)
		{
            bool xInput = XboxInput::Instance()->IsConnected();
            vec3 temp = m_GSM->GetGameData()->cameraPos;

            m_SkipText->SetText("Press BackSpace/Left Click/BACK to SKIP!");
            m_SkipTrs->SetPosition(vec3(temp.x - 250.f, temp.y - 330.f, 17.f));

			m_sprite->SetColor(vec4(1.0f, 1.0f, 1.0f, 1.f));
			m_trs->SetPosition(vec3(temp.x, temp.y, 16.f));
			dtStack += dt;
            if (dtStack > 3.f || InputManager::GetInstance().KeyTriggered(KEY_BACK)
				|| InputManager::GetInstance().KeyTriggered(MOUSE_LEFT) ||
                (xInput && XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->BACK)))
			{
                m_SkipText->SetText("");
                m_SkipTrs->SetPosition(vec3(1000.f, 1000.f, 0.f));

				m_trs->SetPosition(vec3(2000.f, 0.f, 0.f));
				m_sprite->SetColor(vec4(1.0f, 1.0f, 1.0f, 1.f));
				showingTablet = false;
				dtStack = 0.f;
			}
		}
		if (talisman[0]->GetLogic<Target>(TARGET)->CheckItem() && EndCondition == false)
		{
			m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->Restore();
			m_Owner->GetLogic<Arrow>(ARROW)->SetToggle(true);
			if (m_OBM->HasObject(player_id))
			{
				if (player[0]->GetComponent<RigidBody>(CT_RIGIDBODY)->IsCollidedWith(m_Owner->GetID()))
				{
					EndCondition = true;
					m_Owner->GetLogic<Arrow>(ARROW)->SetToggle(false);
					m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->SetActive(false);
				}
			}
		}
	}
}

/******************************************************************************/
/*!
\brief - Shutdown Door info
*/
/******************************************************************************/
void Door::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload Door info
*/
/******************************************************************************/
void Door::Unload(void)
{

}
