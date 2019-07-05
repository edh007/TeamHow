/******************************************************************************/
/*!
\file   HUD.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/09/26(yy/mm/dd)

\description
Contains HUD logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "HUD.h"
#include "../../../BaseData/BaseEnigne.h"
#include "../Player/Player.h"
#include "../Player/Punch.h"
#include "../Enemy/Enemy.h"

/******************************************************************************/
/*!
\brief - HUDBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* HUDBuilder::BuildLogic(Object* Owner, LogicType key) const
{
	return new HUD(Owner, key);
}

/******************************************************************************/
/*!
\brief - HUD constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
HUD::HUD(Object* Owner, LogicType key)
	: GameLogic(Owner, key),  m_tmToggle(false), getEnemies(false),
	m_needle(nullptr), m_clock(nullptr), m_footstep(nullptr), m_eye(nullptr), m_skillText(nullptr),
	m_cooldown(false), m_Effect(true), invisible(vec4()), visible(vec4(1,1,1,1)),
	m_needlePos(vec4()), m_cameraPos(vec4()), m_alarm(false), m_warning(true),
	m_rotation(0.f), offset(5.f), m_radius(0.f), m_radian(0.f), cd_offset(2.f),
	m_q(nullptr), m_space(nullptr), m_lm(nullptr), m_shift(nullptr), instOffset(vec3(0,0,1)),
	m_colorToggle(true), m_point(nullptr), m_pointClr(vec4()), pointToggle(false)
{}

/******************************************************************************/
/*!
\brief - Load NodeSettor info
\param data - json parser
*/
/******************************************************************************/
void HUD::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize NodeSettor info
*/
/******************************************************************************/
void HUD::Init(void)
{
	m_GSM->GetGameData()->tmToggle = false;
	m_GSM->GetGameData()->searchToggle = false;

	dt_Stack[0] = 0.f; 
	dt_Stack[1] = 0.f;

	// Make ui
	// Make clock
	m_bigScl = vec3(150.f, 150.f);
	m_smScl = vec3(100.f, 100.f);

	m_clock = new Object(AT_HUD, m_OBM);
	m_clock->AddComponent(ComponentFactory::CreateComponent(m_clock, CT_SPRITE));
	m_clock->GetComponent<Transform>(CT_TRANSFORM)->SetScale(m_bigScl);
	m_clock->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_GSM->GetGLManager()->GetTexture("UI_Circle"));

	m_needle = new Object(AT_HUD, m_OBM);
	m_needle->AddComponent(ComponentFactory::CreateComponent(m_needle, CT_SPRITE));
	m_needle->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(10.f, 50.f, 0));
	m_radius = m_clock->GetComponent<Transform>(CT_TRANSFORM)->GetScale().y *.15f;

	m_needle->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(
		m_clock->GetComponent<Transform>(CT_TRANSFORM)->GetPosition() +
		vec3(0.f, m_radius));

	m_needle->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_GSM->GetGLManager()->GetTexture("UI_Needle"));

	// Make an footstep
	m_footstep = new Object(AT_HUD, m_OBM);
	m_footstep->AddComponent(ComponentFactory::CreateComponent(m_footstep, CT_SPRITE));
	m_footstep->GetComponent<Transform>(CT_TRANSFORM)->SetScale(m_smScl);
	m_footstep->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_GSM->GetGLManager()->GetTexture("UI_Footstep"));

	// Make an eye
	m_eye = new Object(AT_HUD, m_OBM);
	m_eye->AddComponent(ComponentFactory::CreateComponent(m_eye, CT_SPRITE));
	m_eye->GetComponent<Transform>(CT_TRANSFORM)->SetScale(m_smScl);
	m_eye->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_GSM->GetGLManager()->GetTexture("UI_Eye"));

	// Make time text
	m_time = new Object(AT_HUD, m_OBM);
	m_time->AddComponent(ComponentFactory::CreateComponent(m_time, CT_TEXT));
	m_time->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(1.f, 1.f));

	// Make kill enemy text
	m_enemy = new Object(AT_HUD, m_OBM);
	m_enemy->AddComponent(ComponentFactory::CreateComponent(m_enemy, CT_TEXT));
	m_enemy->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(1.f, 1.f));

	// Make player death text
	m_death = new Object(AT_HUD, m_OBM);
	m_death->AddComponent(ComponentFactory::CreateComponent(m_death, CT_TEXT));
	m_death->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(1.f, 1.f));

	// Make UI_Qbutton
	m_q = new Object(AT_HUD, m_OBM);
	m_q->AddComponent(ComponentFactory::CreateComponent(m_q, CT_SPRITE));
	m_q->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(25.f, 25.f));
	m_q->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("UI_Qbutton"));

	// Make UI_Spacebutton
	m_space = new Object(AT_HUD, m_OBM);
	m_space->AddComponent(ComponentFactory::CreateComponent(m_space, CT_SPRITE));
	m_space->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(62.5f, 25.f));
	m_space->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("UI_Spacebutton"));

	// Make UI_Spacebutton
	m_shift = new Object(AT_HUD, m_OBM);
	m_shift->AddComponent(ComponentFactory::CreateComponent(m_shift, CT_SPRITE));
	m_shift->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(62.5f, 30.f));
	m_shift->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("UI_Shiftbutton"));

	// Make text to show the skill title
	m_skillText = new Object(AT_HUD, m_OBM);
	m_skillText->AddComponent(ComponentFactory::CreateComponent(m_skillText, CT_TEXT));
	m_skillText->GetComponent<Text>(CT_TEXT)->SetFontSize(75);
	m_skillText->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(1.f, 1.f));

	// Make text to show point
	m_point = new Object(AT_HUD, m_OBM);
	m_point->AddComponent(ComponentFactory::CreateComponent(m_point, CT_TEXT));
	m_point->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(1.f, 1.f));

	// Add these uis
	m_OBM->AddObject(m_eye);
	m_OBM->AddObject(m_clock);
	m_OBM->AddObject(m_needle);
	m_OBM->AddObject(m_footstep);
	m_OBM->AddObject(m_time);
	m_OBM->AddObject(m_enemy);
	m_OBM->AddObject(m_space);
	m_OBM->AddObject(m_q);
	m_OBM->AddObject(m_death);
	m_OBM->AddObject(m_shift);
	m_OBM->AddObject(m_skillText);
	m_OBM->AddObject(m_point);

	// Set offset value
	// TODO: Reposition by resolution
	m_clPos = vec3(-425, 275);
	m_eyePos = vec3(-315, 230);
	m_timePos = vec3(-475, 125);
	m_deathPos = vec3(-475, 150);
	m_enemyPos = vec3(-475, 175);
	m_pointPos = vec3(-475, 100);

	m_qPos = vec3(-265, 225, 10);
	m_spacePos = vec3(-425, 200, 10);

	m_shiftClr = m_spaceClr = m_qClr = vec4();
	m_needleClr = m_clClr = vec4(1,1,1,1);
}

/******************************************************************************/
/*!
\brief - Update NodeSettor info
\param dt - delta time
*/
/******************************************************************************/
void HUD::Update(float dt)
{
	if (!getEnemies) {
		std::vector<Object*> enemies;
		m_OBM->GetObjects(AT_ENEMY, enemies);
		m_enemySize = enemies.size();
		getEnemies = true;
	}

	// Set camera pos and center offset
	m_cameraPos = m_OBM->GetGameScene()->GetCameraPos();
	m_GSM->GetGameData()->cameraPos = m_cameraPos;
    m_cameraPos.z = 40.f;
	
	mousePos = InputManager::GetInstance().GetOrthoPosition();

	// After tutorial
	if (m_GSM->GetGameData()->unlockSearch)
		Search();
	
	else 
		m_eye->GetComponent<Sprite>(CT_SPRITE)->SetColor(invisible);

	// After tutorial
	if (m_GSM->GetGameData()->unlockTM)
		TimeManipulation(dt);

	else {
		m_eye->GetComponent<Sprite>(CT_SPRITE)->SetColor(invisible);
		m_clock->GetComponent<Sprite>(CT_SPRITE)->SetColor(invisible);
		m_needle->GetComponent<Sprite>(CT_SPRITE)->SetColor(invisible);
	}

	if (m_enemySize
		- m_GSM->GetGameData()->killedEnemies)
		m_warning = true;

	else
		m_warning = false;

	Run();
	ShowInfo(dt);

	// Show the instruction keys
	if (Math::Distance_pt(mousePos, m_fsPos + m_cameraPos) < m_fsScl.x * .5f)
		m_shiftClr = visible;

	else
		m_shiftClr = invisible;

	m_q->GetComponent<Sprite>(CT_SPRITE)->SetColor(m_qClr);
	m_shift->GetComponent<Sprite>(CT_SPRITE)->SetColor(m_shiftClr);
	m_space->GetComponent<Sprite>(CT_SPRITE)->SetColor(m_spaceClr);

	vec3 offsetPos = m_cameraPos + instOffset;

	m_q->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(m_qPos + offsetPos);
	m_shift->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(m_shiftPos + offsetPos);
	m_space->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(m_spacePos + offsetPos);
	m_point->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(m_pointPos + offsetPos);

	SkillText(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown NodeSettor info
*/
/******************************************************************************/
void HUD::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload NodeSettor info
*/
/******************************************************************************/
void HUD::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Get Cooldown Toggle
\return m_cooldown
*/
/******************************************************************************/
bool HUD::GetCooldownToggle(void) const
{
	return m_cooldown;
}

/******************************************************************************/
/*!
\brief - Time Manipulation hud
\param dt
*/
/******************************************************************************/
void HUD::TimeManipulation(float dt)
{
	// Show the instruction keys
	m_spacePos = m_clPos - vec3(0, m_bigScl.y * .5f);
	if (Math::Distance_pt(mousePos, m_clPos + m_cameraPos) < m_bigScl.x * .5f)
		m_spaceClr = visible;

	else
		m_spaceClr = invisible;

	// If the cool down is not working
	// player can use skills
	// Set the Xbox Input Toggle
	bool xInput = XboxInput::Instance()->IsConnected();

	if ((InputManager::GetInstance().KeyTriggered(KEY_SPACE) ||
        (xInput && XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->XBOX_Y)))
		&& !m_tmToggle
		&& !m_cooldown
		&& !m_GSM->GetGameData()->dtPower)
		m_tmToggle = true;
	
	if (m_OBM->HasObject(m_GSM->GetGameData()->player_id)) {
		if (m_GSM->GetGameData()->dtPower)
			m_needleClr = m_clClr = vec4(1, 1, 1, .5f);
		else
			m_needleClr = m_clClr = visible;
		
		if (m_tmToggle) {
			// 1. time manipulation setting
			// When time manipulation is on
			// Set this once
			if (m_Effect)	{
				m_clock->GetComponent<Sprite>(CT_SPRITE)->SetRippleToggle(true);
				// Except the fog, fov, tutorial and hud stuff
				for (auto obj : m_OBM->GetObjectMap())
					if (obj.second->GetArcheType() != AT_HUD
						&& obj.second->GetArcheType() != AT_FOV
						&& obj.second->GetArcheType() != AT_FOG
						&& obj.second->GetArcheType() != AT_NODE
						&& obj.second->GetArcheType() != AT_NONE
						&& obj.second->GetArcheType() != AT_FADE
						&& obj.second->GetArcheType() != AT_PLAYER
						&& obj.second->GetArcheType() != AT_TUTORIAL
						&& obj.second->HasComponent(CT_SPRITE)) {
						obj.second->GetComponent<Sprite>(CT_SPRITE)->SetBlurToggle(true);
						obj.second->GetComponent<Sprite>(CT_SPRITE)->SetBlurAmount(200.f);
					}
				m_Effect = false;
			}

			// Update dt, rotation
			dt_Stack[0] += dt;
			m_rotation -= dt * (360.f / offset);

			// Refresh info when time is over
			// when it reashes to the end
			if (dt_Stack[0] > offset) {
				m_Effect = m_cooldown = true;
				dt_Stack[0] = m_rotation = 0.f;
				m_tmToggle = false;
				// Return the color of objects
				if (!m_GSM->GetGameData()->searchToggle)
				for (auto obj : m_OBM->GetObjectMap())
					if (obj.second->HasComponent(CT_SPRITE))
						obj.second->GetComponent<Sprite>(CT_SPRITE)->SetBlurToggle(false);
			}

			// Set color of clock and needle
			m_needleClr = m_clClr = vec4(0, 0, 1.f, 1.f);
		}

		// Unless,
		// cool down working
		else if (m_cooldown)
		{
			// Set color of clock and needle
			// and rotation
			dt_Stack[0] += dt;
			m_rotation -= dt * (360.f / cd_offset);
			m_needleClr = m_clClr = vec4(1, 0.f, 0.f, 1.f);

			if (dt_Stack[0] > cd_offset) {
				m_needleClr = m_clClr = vec4(1, 1, 1, 1);
				m_cooldown = false;
				m_rotation = dt_Stack[0] = 0.f;
				m_clock->GetComponent<Sprite>(CT_SPRITE)->SetRippleToggle(false);
			}
		}
	}

	// Set final info of two sprites
	m_clock->GetComponent<Sprite>(CT_SPRITE)->SetColor(m_clClr);
	m_needle->GetComponent<Sprite>(CT_SPRITE)->SetColor(m_needleClr);

	m_radian = Math::DegToRad(m_rotation + 90.f);
	m_needle->GetComponent<Transform>(CT_TRANSFORM)->SetRotation(m_rotation);

	vec3 finalClPos = m_cameraPos + m_clPos;
	m_needlePos = m_radius * vec3(cosf(m_radian), sinf(m_radian))
		+ vec3(cosf(m_radian), sinf(m_radian)) + finalClPos;

	m_clock->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(finalClPos);
	m_needle->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(m_needlePos);

	m_GSM->GetGameData()->tmToggle = m_tmToggle;
}

/******************************************************************************/
/*!
\brief - Footstep hud
*/
/******************************************************************************/
void HUD::Run(void)
{
	if (!m_GSM->GetGameData()->unlockSearch &&
		!m_GSM->GetGameData()->unlockTM)
	{
		m_fsPos = m_clPos;
		m_fsScl = m_bigScl;
		m_shiftPos = m_fsPos - vec3(0.f, m_fsScl.y * .5f, 0.f);
	}

	else {
		m_fsScl = m_smScl;
		m_fsPos = vec3(-315, 320);
		m_shiftPos = m_fsPos + vec3(m_fsScl.x * .5f, 0, 0.f );
	}

	bool ripple = false;
	m_fsClr = vec4(1, 1, 1, 1);

	if (m_warning) {
		if (m_GSM->GetGameData()->footstack >= 3.f
			&& m_GSM->GetGameData()->footstack < 5.f) {
			ripple = true;
			m_fsClr = vec4(1, 1, 0, 1);
		}

		else if (m_GSM->GetGameData()->footstack >= 5.f) {
			ripple = true;
			m_fsClr = vec4(1, 0, 0, 1);
		}
	}

	if (m_GSM->GetGameData()->dtPower)
		m_fsClr = vec4(1, 1, 1, .5f);

	if (m_GSM->GetGameData()->silent)
		m_fsClr = vec4(.25f, .25f, .25f, .5f);

	m_footstep->GetComponent<Sprite>(CT_SPRITE)->SetRippleToggle(ripple);

	// Set position and color of run ui
	m_footstep->GetComponent<Transform>(CT_TRANSFORM)->SetScale(m_fsScl);
	m_footstep->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(
		m_fsPos + m_cameraPos);
	m_footstep->GetComponent<Sprite>(CT_SPRITE)->SetColor(m_fsClr);
}

/******************************************************************************/
/*!
\brief - Searching hud
*/
/******************************************************************************/
void HUD::Search(void)
{
	// Show the instruction keys
	if (Math::Distance_pt(mousePos, m_eyePos + m_cameraPos) < m_smScl.x * .5f)
		m_qClr = visible;
	else
		m_qClr = invisible;

	if (!m_GSM->GetGameData()->dtPower) {
		//Get  player's search toggle
		bool toggle = m_GSM->GetGameData()->searchToggle;

		// Set color and effect
		if (toggle)
			m_eye->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 1, 0, 1));
		else
			m_eye->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 1, 1, 1));

		m_eye->GetComponent<Sprite>(CT_SPRITE)->SetRippleToggle(toggle);
	}

	else
		m_eye->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 1, 1, .5f));

	// Set position
	m_eye->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(m_eyePos + m_cameraPos);
	m_qPos = m_eyePos + vec3(m_smScl.x * .5f);
}

/******************************************************************************/
/*!
\brief - Check grade
*/
/******************************************************************************/
void HUD::ShowInfo(float /*dt*/)
{
	if (!m_GSM->GetGameData()->gamenextCondition
		&& !m_GSM->GetGameData()->gameoverCondition) {
		// Update the time
		m_GSM->GetGameData()->timeElapsed
			= m_GSM->GetStageTimer().GetElapsedTime();
	}

	m_time->GetComponent<Text>(CT_TEXT)->SetText(
		"* Time: %.3f", m_GSM->GetGameData()->timeElapsed);
	m_enemy->GetComponent<Text>(CT_TEXT)->SetText(
		"* Killed: %d", m_GSM->GetGameData()->killedEnemies);
	m_death->GetComponent<Text>(CT_TEXT)->SetText(
		"* Death: %d", m_GSM->GetGameData()->player_death);

	m_time->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(
		m_timePos + m_cameraPos);
	m_enemy->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(
		m_enemyPos + m_cameraPos);
	m_death->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(
		m_deathPos + m_cameraPos);

}

/******************************************************************************/
/*!
\brief - Show skill texts on the screen
\param dt - delta time
*/
/******************************************************************************/
void HUD::SkillText(float dt)
{
	// Make time manipulation texts to be printed out
	if (m_GSM->GetGameData()->tmToggle
		&& !m_GSM->GetGameData()->searchToggle) {
		m_skillText->GetComponent<Text>(CT_TEXT)->SetText("The One Watch");
		m_skillPos = vec3(-150, m_GSM->GetGameData()->resolution.y * .5f - 75.f);
		m_skillText->GetComponent<Text>(CT_TEXT)->SetFontSize(75);
	}
	
	// Make both texts to be printed out
	else if (m_GSM->GetGameData()->searchToggle
		&& !m_GSM->GetGameData()->tmToggle) {
		m_skillText->GetComponent<Text>(CT_TEXT)->SetText("Eyes Of People");
		m_skillPos = vec3(-150, m_GSM->GetGameData()->resolution.y * .5f - 75.f);
		m_skillText->GetComponent<Text>(CT_TEXT)->SetFontSize(75);
	}
	
	// Make both texts to be printed out
	else if (m_GSM->GetGameData()->tmToggle
		&& m_GSM->GetGameData()->searchToggle) {
		m_skillText->GetComponent<Text>(CT_TEXT)->SetText("Eyes Of People + The One Watch");
		m_skillPos = vec3(-175, m_GSM->GetGameData()->resolution.y * .5f - 75.f);
		m_skillText->GetComponent<Text>(CT_TEXT)->SetFontSize(40);
	}

	// Make invisible
	else
		m_skillText->GetComponent<Text>(CT_TEXT)->SetText("");

	m_point->GetComponent<Text>(CT_TEXT)->SetText("* Point: %d", m_GSM->GetGameData()->player_point);

	ColorEffect(skillColor, colorToggle, dt);

	if (m_GSM->GetGameData()->enoughPoint)
		ColorEffect(m_pointClr, pointToggle, dt);
	else
		m_pointClr = vec4(1,1,1,1);
	
	m_skillText->GetComponent<Text>(CT_TEXT)->SetColor(skillColor);
	m_skillText->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(
		m_skillPos + m_cameraPos);
	m_point->GetComponent<Text>(CT_TEXT)->SetColor(m_pointClr);
}

/******************************************************************************/
/*!
\brief - Do color effect from red to blue
\param color - color to change
\param dt - delta time
*/
/******************************************************************************/
void HUD::ColorEffect(vec4& color, bool& toggle, float dt)
{
	if (toggle) {
		color.x += dt;
		color.z -= dt;
		if (color.x > 1.f
			&& color.z < 0.f) {
			toggle = !toggle;
			color = vec4(1, 0, 0, 1);
		}
	}

	else {
		color.x -= dt;
		color.z += dt;
		if (color.x < 0.f
			&& color.z > 1.f) {
			toggle = !toggle;
			color = vec4(0, 0, 1, 1);
		}
	}
}