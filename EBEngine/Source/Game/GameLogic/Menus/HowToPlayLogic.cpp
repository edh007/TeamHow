/******************************************************************************/
/*!
\file   HowToPlayLogic.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/06/10(yy/mm/dd)

\description
Contains HowToPlayLogic logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "HowToPlayLogic.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - HowToPlayLogicBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* HowToPlayLogicBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new HowToPlayLogic(Owner, key);
}

/******************************************************************************/
/*!
\brief - HowToPlayLogic constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
HowToPlayLogic::HowToPlayLogic(Object* Owner, LogicType key)
: GameLogic(Owner, key), 
m_mouse(nullptr), m_pic1(nullptr), background(nullptr), tmpMouseId(0),
menu_id(-1), selectSFX(nullptr), m_pic2(nullptr), m_inst(nullptr)
{}

/******************************************************************************/
/*!
\brief - Load HowToPlayLogic info
\param data - json parser
*/
/******************************************************************************/
void HowToPlayLogic::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize HowToPlayLogic info
*/
/******************************************************************************/
void HowToPlayLogic::Init(void)
{
	m_OBM->GetGameSound()->AddAudio("select", "select");
	selectSFX = m_OBM->GetGameSound()->GetAudio("select");
	selectSFX->SetVolume(m_GSM->GetGameData()->volume);

	SetMouse();
	SetMenuAssets();
}

/******************************************************************************/
/*!
\brief - Update HowToPlayLogic info
\param dt - delta time
*/
/******************************************************************************/
void HowToPlayLogic::Update(float dt)
{
	if (InputManager::GetInstance().KeyTriggered(KEY_ESC)
		|| InputManager::GetInstance().KeyTriggered(KEY_BACK)
		|| (XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->START)))
		m_GSM->Resume();

	UpdateKeys(dt);
	UpdateMouse();
	UpdateMenuAssets(dt);

	if (xInptDly == false)
	{
		dly += dt;
		if (dly > 0.2f)
		{
			xInptDly = true;
			dly = 0.f;
		}
	}
}

/******************************************************************************/
/*!
\brief - Shutdown HowToPlayLogic info
*/
/******************************************************************************/
void HowToPlayLogic::Shutdown(void)
{
	m_GSM->GetGameData()->mouseID = tmpMouseId;
}

/******************************************************************************/
/*!
\brief - Unload HowToPlayLogic info
*/
/******************************************************************************/
void HowToPlayLogic::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Init mouse assets
*/
/******************************************************************************/
void HowToPlayLogic::SetMouse(void)
{
	m_mouse = new Object(AT_MOUSE, m_OBM);
	m_mouse->AddComponent(ComponentFactory::CreateComponent(m_mouse, CT_TRANSFORM));
	mouseScl = vec3(25, 25);
	m_mouse->GetComponent<Transform>(CT_TRANSFORM)->SetScale(mouseScl);

	m_mouse->AddComponent(ComponentFactory::CreateComponent(m_mouse, CT_RIGIDBODY));
	m_mouse->GetComponent<RigidBody>(CT_RIGIDBODY)->ActivateResponse(false);
	m_mouse->GetComponent<RigidBody>(CT_RIGIDBODY)->SetShape(BALL);

	m_OBM->AddObject(m_mouse);
	tmpMouseId = m_GSM->GetGameData()->mouseID;
	m_GSM->GetGameData()->mouseID = m_mouse->GetID();
}

/******************************************************************************/
/*!
\brief - Check mouse inputs
*/
/******************************************************************************/
void HowToPlayLogic::UpdateMouse(void)
{
	vec3 mousePos = InputManager::GetInstance().GetOrthoPosition();
	mousePos.z = 10.f;
	mousePos.x += mouseScl.x;
	mousePos.y -= mouseScl.y;
	m_mouse->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(
		mousePos);
}

/******************************************************************************/
/*!
\brief - Init menu stage assets
*/
/******************************************************************************/
void HowToPlayLogic::SetMenuAssets(void)
{
	m_pic1 = new Object(AT_HUD, m_OBM);
	m_pic2 = new Object(AT_HUD, m_OBM);
	m_inst = new Object(AT_HUD, m_OBM);
	background = new Object(AT_HUD, m_OBM);

	m_pic1->AddComponent(ComponentFactory::CreateComponent(m_pic1, CT_SPRITE));
	m_pic1->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3());
	m_pic1->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(700.f, 700.f));
	m_pic1->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("HowToPlay_1"));

	m_pic2->AddComponent(ComponentFactory::CreateComponent(m_pic2, CT_SPRITE));
	m_pic2->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(1000.f));
	m_pic2->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(700.f, 700.f));
	m_pic2->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("HowToPlay_2"));

	m_inst->AddComponent(ComponentFactory::CreateComponent(m_inst, CT_TEXT));
	m_inst->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(-500.f, -370.f, 10.f));
	m_inst->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(1.f, 1.f));
	m_inst->GetComponent<Text>(CT_TEXT)->SetText("Control left and right arrow keys.");
	m_inst->GetComponent<Text>(CT_TEXT)->SetColor(vec4(1, 1, 1, 1.f));

	vec3 res(
		static_cast<float>(m_GSM->GetResolution().width),
		static_cast<float>(m_GSM->GetResolution().height));

	background->AddComponent(ComponentFactory::CreateComponent(background, CT_SPRITE));
	background->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(0, 0.f, -50.f));
	background->GetComponent<Transform>(CT_TRANSFORM)->SetScale(res);
	background->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Menu_Background"));
	background->GetComponent<Sprite>(CT_SPRITE)->SetRippleToggle(true);

	m_OBM->AddObject(m_inst);
	m_OBM->AddObject(m_pic1);
	m_OBM->AddObject(m_pic2);
	m_OBM->AddObject(background);

	bgColor = vec4(1, 0, 0, 1);
}

/******************************************************************************/
/*!
\brief - Update menu stage
*/
/******************************************************************************/
void HowToPlayLogic::UpdateMenuAssets(float dt)
{
	// Random title color
	if (colorToggle) {
		bgColor.x += dt;
		bgColor.z -= dt;
		if (bgColor.x > 1.f
			&& bgColor.z < 0.f) {
			colorToggle = !colorToggle;
			bgColor = vec4(1, 0, 0, 1);
		}
	}

	else {
		bgColor.x -= dt;
		bgColor.z += dt;
		if (bgColor.x < 0.f
			&& bgColor.z > 1.f) {
			colorToggle = !colorToggle;
			bgColor = vec4(0, 0, 1, 1);
		}
	}
}

/******************************************************************************/
/*!
\brief - Check keyboard inputs
*/
/******************************************************************************/
void HowToPlayLogic::UpdateKeys(float dt)
{
	static int status = 0;
	static vec3 speed = vec3(1000.f);
	vec3 newSp = speed * dt;

	// Set the Xbox Input Toggle
	bool xInput = XboxInput::Instance()->IsConnected();

	// Next instruction
	if (InputManager::GetInstance().KeyTriggered(KEY_LEFT)
		|| (xInput && xInptDly && XboxInput::Instance()->leftStickX < -0.5f)
		|| (xInput && XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->DPAD_LEFT)))
			status = 1;

	// First instruction
	else if (InputManager::GetInstance().KeyTriggered(KEY_RIGHT)
		|| (xInput && xInptDly && XboxInput::Instance()->leftStickX > 0.5f)
		|| (xInput && XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->DPAD_RIGHT)))
			status = 2;

	// Move to the last instruction
	if (status == 1) {
		vec3 pos = m_pic2->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();

		if (pos.x > 0.f) {

			m_pic1->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(
				m_pic1->GetComponent<Transform>(CT_TRANSFORM)->GetPosition() - newSp);

			m_pic2->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(
				m_pic2->GetComponent<Transform>(CT_TRANSFORM)->GetPosition() - newSp);
		}

		if (pos.x <= 0.f) {
			status = 0;
			m_pic2->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3());
		}
	}

	else if (status == 2){
		vec3 pos = m_pic1->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();

		if (pos.x < 0.f) {

			m_pic1->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(
				m_pic1->GetComponent<Transform>(CT_TRANSFORM)->GetPosition() + newSp);

			m_pic2->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(
				m_pic2->GetComponent<Transform>(CT_TRANSFORM)->GetPosition() + newSp);
		}

		if (pos.x >= 0.f) {
			status = 0;
			m_pic1->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3());
		}
	}

	//bool pressed = false;
	if (!m_GSM->GetGameData()->onMenuMouse)
	{
		if (InputManager::GetInstance().KeyTriggered(KEY_LEFT)
			|| (xInput && xInptDly && XboxInput::Instance()->leftStickX < -0.5f)
			|| (xInput && XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->DPAD_LEFT))
			|| InputManager::GetInstance().KeyTriggered(KEY_RIGHT)
			|| (xInput && xInptDly && XboxInput::Instance()->leftStickX > 0.5f)
			|| (xInput && XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->DPAD_RIGHT)))
		{
			if (xInptDly == true)
				xInptDly = false;

			selectSFX->Play();
			menu_id = 4;
			m_GSM->GetGameData()->menuKeyPressed = true;
			m_GSM->GetGameData()->menuSelection = menu_id;
		}
	}
}