/******************************************************************************/
/*!
\file   Credit.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/04/11(yy/mm/dd)

\description
Contains Credit logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Credit.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - CreditBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* CreditBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Credit(Owner, key);
}

/******************************************************************************/
/*!
\brief - Credit constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Credit::Credit(Object* Owner, LogicType key)
: GameLogic(Owner, key), 
m_mouse(nullptr), title(nullptr), m_creditList(nullptr), background(nullptr), tmpMouseId(0),
menu_id(-1), selectSFX(nullptr)
{}

/******************************************************************************/
/*!
\brief - Load Credit info
\param data - json parser
*/
/******************************************************************************/
void Credit::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize Credit info
*/
/******************************************************************************/
void Credit::Init(void)
{
	m_OBM->GetGameSound()->AddAudio("select", "select");
	selectSFX = m_OBM->GetGameSound()->GetAudio("select");
	selectSFX->SetVolume(m_GSM->GetGameData()->volume);

	SetMouse();
	SetMenuAssets();
}

/******************************************************************************/
/*!
\brief - Update Credit info
\param dt - delta time
*/
/******************************************************************************/
void Credit::Update(float dt)
{
	if (InputManager::GetInstance().KeyTriggered(KEY_ESC)
		|| InputManager::GetInstance().KeyTriggered(KEY_BACK)
        || (XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->START)))
		m_GSM->Resume();

	UpdateKeys();
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
\brief - Shutdown Credit info
*/
/******************************************************************************/
void Credit::Shutdown(void)
{
	m_GSM->GetGameData()->mouseID = tmpMouseId;
}

/******************************************************************************/
/*!
\brief - Unload Credit info
*/
/******************************************************************************/
void Credit::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Init mouse assets
*/
/******************************************************************************/
void Credit::SetMouse(void)
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
void Credit::UpdateMouse()
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
void Credit::SetMenuAssets(void)
{
	title = new Object(AT_HUD, m_OBM);
	m_creditList = new Object(AT_HUD, m_OBM);
	m_creditContents = new Object(AT_HUD, m_OBM);
	background = new Object(AT_HUD, m_OBM);

	title->AddComponent(ComponentFactory::CreateComponent(title, CT_TEXT));
	title->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(-150.f, 175.f, 10.f));
	title->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(1.f, 1.f));
	title->GetComponent<Text>(CT_TEXT)->SetText("Credits");
	title->GetComponent<Text>(CT_TEXT)->SetFontSize(100);
	title->GetComponent<Text>(CT_TEXT)->SetColor(vec4(1, 1, 1, 1.f));

	m_creditList->AddComponent(ComponentFactory::CreateComponent(m_creditList, CT_TEXT));
	m_creditList->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(-450.f, 100.f, 10.f));
	m_creditList->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(1.f, 1.f));

	m_creditContents->AddComponent(ComponentFactory::CreateComponent(m_creditContents, CT_TEXT));
	m_creditContents->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(150.f, 100.f, 10.f));
	m_creditContents->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(1.f, 1.f));

	/**************************** Credit Here *********************************/
	m_creditList->GetComponent<Text>(CT_TEXT)->SetText(
		"Copyrights \n\n"
		"All content(C) 2017 DigiPen(USA) Corporation\nall rights reserved. \n\n"
		"json, Copyright 2007 - 2010 Baptiste Lepilleur\n under MIT license \n\n"
		"freetype.Copyright 1996 - 2001, 2002\nby David Turner."
		"Robert Wilhelm, and Werner Lemberg. \n\n"
		"FMOD, copyright(C) Firelight Technologies\nPty.Ltd., 2012 - 2017 \n\n"
		"LodePNG Copyright(c) 2005 - 2013 \nby Lode Vandevenne. All rights reserved.");

	m_creditContents->GetComponent<Text>(CT_TEXT)->SetText(
		"Credits\n\n"
		"Game Title : Captain Korea \n"
		"Team Name : Team HOW \n\n"
		"Class : GAM250KR \n"
		"Instructor : David Ly \n\n"
		"President : Claude Comair \n\n"
		"Tech Lead : Juyong Jeong \n"
		"Design Lead : Dongho Lee ");
	/**************************** Credit Here *********************************/

	m_creditList->GetComponent<Text>(CT_TEXT)->SetFontSize(25);
	m_creditList->GetComponent<Text>(CT_TEXT)->SetColor(vec4(1, 1, 1, 1.f));

	m_creditContents->GetComponent<Text>(CT_TEXT)->SetFontSize(25);
	m_creditContents->GetComponent<Text>(CT_TEXT)->SetColor(vec4(1, 1, 1, 1.f));

	vec3 res(
		static_cast<float>(m_GSM->GetResolution().width),
		static_cast<float>(m_GSM->GetResolution().height));

	background->AddComponent(ComponentFactory::CreateComponent(background, CT_SPRITE));
	background->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(0, 0.f, -50.f));
	background->GetComponent<Transform>(CT_TRANSFORM)->SetScale(res);
	background->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Menu_Background"));
	background->GetComponent<Sprite>(CT_SPRITE)->SetRippleToggle(true);

	m_OBM->AddObject(title);
	m_OBM->AddObject(m_creditList);
	m_OBM->AddObject(m_creditContents);
	m_OBM->AddObject(background);

	bgColor = vec4(1, 0, 0, 1);
}

/******************************************************************************/
/*!
\brief - Update menu stage
*/
/******************************************************************************/
void Credit::UpdateMenuAssets(float dt)
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

	title->GetComponent<Text>(CT_TEXT)->SetColor(bgColor);
}

/******************************************************************************/
/*!
\brief - Check keyboard inputs
*/
/******************************************************************************/
void Credit::UpdateKeys(void)
{
	//bool pressed = false;
	if (!m_GSM->GetGameData()->onMenuMouse)
	{
		// Set the Xbox Input Toggle
		bool xInput = XboxInput::Instance()->IsConnected();

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