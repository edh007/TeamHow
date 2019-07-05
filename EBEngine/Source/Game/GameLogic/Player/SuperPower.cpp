/******************************************************************************/
/*!
\file   SuperPower.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/11/28(yy/mm/dd)

\description
Contains SuperPower logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "SuperPower.h"
#include "../HUD/HUD.h"
#include "../Enemy/Enemy.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - SuperPowerBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* SuperPowerBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new SuperPower(Owner, key);
}

/******************************************************************************/
/*!
\brief - SuperPower constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
SuperPower::SuperPower(Object* Owner, LogicType key)
	: GameLogic(Owner, key), m_fist(0), m_init(true)
{}

/******************************************************************************/
/*!
\brief - Load SuperPower info
\param data - json parser
*/
/******************************************************************************/
void SuperPower::Load(const Json::Value& /*data*/)
{}

/******************************************************************************/
/*!
\brief - Initialize SuperPower info
*/
/******************************************************************************/
void SuperPower::Init(void)
{
	if (!m_fist)
	{
		m_fist = new Object(AT_PUNCH, m_OBM);
		m_fist->AddComponent(ComponentFactory::CreateComponent(m_fist, CT_SPRITE));
		m_fist->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_GSM->GetGLManager()->GetTexture("circle"));
		m_fist->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1,1,1,0.f));
		m_fist->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(75, 75));
		m_fist->AddComponent(ComponentFactory::CreateComponent(m_fist, CT_RIGIDBODY));
		m_fist->AddLogic(LogicFactory::CreateLogic(m_fist, PUNCH));
		
		RigidBody* fist = m_fist->GetComponent<RigidBody>(CT_RIGIDBODY);
		fist->ActivateResponse(false);
		fist->SetShape(BALL);
		m_OBM->AddObject(m_fist);
		m_GSM->GetGameData()->fist = m_fist;
	}
}

/******************************************************************************/
/*!
\brief - Update SuperPower info
\param dt - delta time
*/
/******************************************************************************/
void SuperPower::Update(float /*dt*/)
{
	std::vector<Object*> hud;
	m_OBM->GetObjects(BASIC_HUD, hud);

	// Make sure if there is 
	// hud object
	if (hud.size())
	{
		// Set the Xbox Input Toggle
		bool xInput = XboxInput::Instance()->IsConnected();
		// Search power
		if (m_GSM->GetGameData()->unlockSearch) {
			if ((InputManager::GetInstance().KeyTriggered(KEY_Q) ||
                (xInput && XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->XBOX_X)))
				&& !m_GSM->GetGameData()->dtPower)
				m_search = !m_search;
			Search();
		}


		// Super punch
		Punch();
	}
}

/******************************************************************************/
/*!
\brief - Shutdown SuperPower info
*/
/******************************************************************************/
void SuperPower::Shutdown(void)
{
	m_OBM->RemoveObject(m_fist->GetID());
}

/******************************************************************************/
/*!
\brief - Unload SuperPower info
*/
/******************************************************************************/
void SuperPower::Unload(void)
{

}

/******************************************************************************/
/*!
\brief -Update fist of player
*/
/******************************************************************************/
void SuperPower::Punch(void)
{
	// Punch settor
	m_position = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
	m_scale = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetScale();
	m_position = Math::Rotation(m_position + vec3(m_scale.x)* .4f,
		m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetRotation(), m_position);
	m_position.z = 1.5f;
	m_fist->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(m_position);
}

/******************************************************************************/
/*!
\brief -Search ability of player
*/
/******************************************************************************/
void SuperPower::Search(void)
{
	// Collect the enemies that can be seen
	// and set their visibilty from player
	//***********************************************************************************//
	m_enemies.clear();
	for (auto it = m_OBM->GetObjectMap().begin(); it != m_OBM->GetObjectMap().end(); ++it)
		if ((*it).second && ((*it).second->HasLogic(ENEMY) || (*it).second->HasLogic(DOOR) ||
			(*it).second->HasLogic(TARGET) || (*it).second->HasLogic(TURRET)))
			m_enemies.push_back((*it).second);

	for (auto it = m_enemies.begin(); it != m_enemies.end(); ++it)
	{
		vec3 creaturePosition = (*it)->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();

		if (m_GSM->GetGameData()->fogToggle == false)
			(*it)->GetComponent<Sprite>(CT_SPRITE)->SetDrawingCheck(true);
		else if (Math::Distance_pt(creaturePosition, m_GSM->GetGameData()->cameraPos) 
			< m_GSM->GetGameData()->realViewSight)
			(*it)->GetComponent<Sprite>(CT_SPRITE)->SetDrawingCheck(true);
		else
			(*it)->GetComponent<Sprite>(CT_SPRITE)->SetDrawingCheck(false);
	}
	//***********************************************************************************//

	// 2. searching setting
	// When searching ability is on
	if (m_search) {
		m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetSobelAmount(400.f);
		// Set this once
		if (m_init)
		{
			// Except the fog, fov, tutorial and hud stuff
			for (auto obj : m_OBM->GetObjectMap()) {
				if (obj.second->GetArcheType() != AT_HUD
					&& obj.second->GetArcheType() != AT_FOV
					&& obj.second->GetArcheType() != AT_FOG
					&& obj.second->GetArcheType() != AT_NODE
					&& obj.second->GetArcheType() != AT_NONE
					&& obj.second->GetArcheType() != AT_TUTORIAL
					&& obj.second->GetArcheType() != AT_FADE) {
				
					// Nake walls invisible
					if (obj.second->GetArcheType() == AT_WALL)
						obj.second->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4());

					// Make the others blur
					else if (obj.second->HasComponent(CT_SPRITE)) {
						obj.second->GetComponent<Sprite>(CT_SPRITE)->SetBlurToggle(true);
						obj.second->GetComponent<Sprite>(CT_SPRITE)->SetBlurAmount(200.f);
					}
				}
			}
			m_init = false;
		}

		// Mark only enemies visible
		// This is for fog
		for (auto it : m_enemies)
		{
			// If it is target or door...
			if (Math::Distance_pt(m_GSM->GetGameData()->player_pos,
				(*it).GetComponent<Transform>(CT_TRANSFORM)->GetPosition())
				< m_GSM->GetGameData()->player_searchDist
				&& ((it->HasLogic(TRAP) || (it->HasLogic(TARGET) || (it->HasLogic(DOOR))))))
			{
				vec3 temp = it->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
				temp.z = 10.f;
				it->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(temp);
				it->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 1, 1, 1.f));
				it->GetComponent<Sprite>(CT_SPRITE)->SetSobelToggle(true);
				it->GetComponent<Sprite>(CT_SPRITE)->SetSobelAmount(50.f);
				it->GetComponent<Sprite>(CT_SPRITE)->SetDrawingCheck(true);
			}
			else {
				vec3 temp = it->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
				temp.z = 1.f;
				it->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(temp);
				it->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 1, 1, 1.f));
				it->GetComponent<Sprite>(CT_SPRITE)->SetSobelToggle(false);
			}

			// If it is just enemy...
			if (Math::Distance_pt(m_GSM->GetGameData()->player_pos,
				(*it).GetComponent<Transform>(CT_TRANSFORM)->GetPosition())
				< m_GSM->GetGameData()->player_searchDist
				&&(it->HasLogic(ENEMY)))
			{
				// Check alive enemies
				if (it->GetLogic<Enemy>(ENEMY)->GetAliveToggle()) {
					vec3 temp = it->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
					temp.z = 10.f;
					it->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(temp);
					it->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 1, 1, 1.f));
					it->GetComponent<Sprite>(CT_SPRITE)->SetSobelToggle(true);
					it->GetComponent<Sprite>(CT_SPRITE)->SetSobelAmount(50.f);
				}

				// Check dead enemies
				else {
					vec3 temp = it->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
					temp.z = 1.f;
					it->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(temp);
					it->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(.25f, .25f, .25f, 1.f));
					it->GetComponent<Sprite>(CT_SPRITE)->SetSobelToggle(false);
				}

				// Anyway draw the enemy
				it->GetComponent<Sprite>(CT_SPRITE)->SetDrawingCheck(true);
			}
		}
	}

	// When turn search toggle off
	else {
		// Refresh info
		if (!m_init)
		{
			// If it is just enemy...
			for (auto it : m_enemies)
			{
				if (it->HasLogic(ENEMY)) {
					vec3 temp = it->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
					temp.z = 1.f;
					it->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(temp);
					it->GetComponent<Sprite>(CT_SPRITE)->SetSobelToggle(false);
					if (!it->GetLogic<Enemy>(ENEMY)->GetAliveToggle())
						it->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(.25f, .25f, .25f, 1.f));
				}
				else if (it->HasLogic(TARGET) || it->HasLogic(DOOR) || it->HasLogic(TRAP)) {
					vec3 temp = it->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
					temp.z = 1.f;
					it->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(temp);
					it->GetComponent<Sprite>(CT_SPRITE)->SetSobelToggle(false);
				}

			}

			// Return the color of objects
			for (auto obj : m_OBM->GetObjectMap()) {
			
				if (obj.second->GetArcheType() == AT_WALL)
					obj.second->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1,1,1,1));

				if (obj.second->HasComponent(CT_SPRITE))
					obj.second->GetComponent<Sprite>(CT_SPRITE)->SetBlurToggle(false);
			}
			m_init = true;
		}
	}

	m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetSobelToggle(m_search);
	m_GSM->GetGameData()->searchToggle = m_search;
}
