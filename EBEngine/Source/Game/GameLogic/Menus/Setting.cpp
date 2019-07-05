/******************************************************************************/
/*!
\file   Setting.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/04/11(yy/mm/dd)

\description
Contains Setting logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Setting.h"
#include "../../../BaseData/BaseEnigne.h"
#include "../Menus/MenuSelect.h"

/******************************************************************************/
/*!
\brief - SettingBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* SettingBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Setting(Owner, key);
}

/******************************************************************************/
/*!
\brief - Setting constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Setting::Setting(Object* Owner, LogicType key)
: GameLogic(Owner, key), m_volumeText(nullptr), m_mouse(nullptr), background(nullptr), title(nullptr),
tmpMouseId(0), selectSFX(nullptr)
{}

/******************************************************************************/
/*!
\brief - Load Setting info
\param data - json parser
*/
/******************************************************************************/
void Setting::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize Setting info
*/
/******************************************************************************/
void Setting::Init(void)
{
	m_OBM->GetGameSound()->AddAudio("select", "select");
	selectSFX = m_OBM->GetGameSound()->GetAudio("select");
	selectSFX->SetVolume(m_GSM->GetGameData()->volume);

	std::vector<Object*> list;
	m_OBM->GetObjects(AT_MENU, list);
	for (auto it : list)
		if (it->HasComponent(CT_TEXT))
			m_volumeText = list[0];

	SetMouse();
	SetMenuAssets();
}

/******************************************************************************/
/*!
\brief - Update Setting info
\param dt - delta time
*/
/******************************************************************************/
void Setting::Update(float dt)
{
	if (InputManager::GetInstance().KeyTriggered(KEY_ESC)
		|| InputManager::GetInstance().KeyTriggered(KEY_BACK)
        || (XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->START)))
		m_GSM->Resume();

	// Updates every assets in this stage
	UpdateMenuAssets(dt);
	UpdateKeys();
	UpdateMouse();

	m_volumeText->GetComponent<Text>(CT_TEXT)->SetText("%d%%", 
		int(m_GSM->GetGameData()->volume * 100));
    
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
\brief - Shutdown Setting info
*/
/******************************************************************************/
void Setting::Shutdown(void)
{
	m_GSM->GetGameData()->mouseID = tmpMouseId;
}

/******************************************************************************/
/*!
\brief - Unload Setting info
*/
/******************************************************************************/
void Setting::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Check keyboard inputs
*/
/******************************************************************************/
void Setting::UpdateKeys(void)
{
	//std::cout << menu_id << std::endl;

	//bool pressed = false;
	if (!m_GSM->GetGameData()->onMenuMouse)
	{
		// Set the Xbox Input Toggle
		bool xInput = XboxInput::Instance()->IsConnected();

		if (InputManager::GetInstance().KeyTriggered(KEY_LEFT) ||
            (xInput && xInptDly && XboxInput::Instance()->leftStickX < -0.5f) ||
            (xInput && XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->DPAD_LEFT)))
		{
            if (xInptDly == true)
                xInptDly = false;

			selectSFX->Play();
			--menu_id;
			//if (m_GSM->GetGameData()->confirm) {
			//	if (menu_id < 11)
			//		menu_id = 12;
			//}

			//else
			//{
				if (menu_id == 8)
					menu_id = 4;

				else if (menu_id < 4)
					menu_id = 12;
			//}

			m_GSM->GetGameData()->menuKeyPressed = true;
			m_GSM->GetGameData()->menuSelection = menu_id;
		}

		else if (InputManager::GetInstance().KeyTriggered(KEY_RIGHT) || 
            (xInput && xInptDly && XboxInput::Instance()->leftStickX > 0.5f) ||
            (xInput && XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->DPAD_RIGHT)))
		{
            if (xInptDly == true)
                xInptDly = false;

			selectSFX->Play();
			++menu_id;
			//if (m_GSM->GetGameData()->confirm)
			//{
			//	if (menu_id > 12)
			//		menu_id = 11;
			//}

			//else
			//{
				if (menu_id == 5)
					menu_id = 9;

				else if (menu_id > 12 || menu_id < 4)
					menu_id = 4;
			//}

			m_GSM->GetGameData()->menuKeyPressed = true;
			m_GSM->GetGameData()->menuSelection = menu_id;
		}
	}
}

/******************************************************************************/
/*!
\brief - Init mouse assets
*/
/******************************************************************************/
void Setting::SetMouse(void)
{
	m_mouse = new Object(AT_MOUSE, m_OBM);
	m_mouse->AddComponent(ComponentFactory::CreateComponent(m_mouse, CT_TRANSFORM));
	mouseScl = vec3(25, 25);
	m_mouse->GetComponent<Transform>(CT_TRANSFORM)->SetScale(mouseScl);

	m_mouse->AddComponent(ComponentFactory::CreateComponent(m_mouse, CT_RIGIDBODY));
	m_mouse->GetComponent<RigidBody>(CT_RIGIDBODY)->ActivateResponse(false);
	m_mouse->GetComponent<RigidBody>(CT_RIGIDBODY)->SetShape(BALL);

	//m_mouse->AddComponent(ComponentFactory::CreateComponent(m_mouse, CT_SPRITE));
	//m_mouse->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("circle"));
	//m_mouse->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1,1,1,1));

	m_OBM->AddObject(m_mouse);
	tmpMouseId = m_GSM->GetGameData()->mouseID;
	m_GSM->GetGameData()->mouseID = m_mouse->GetID();
}

/******************************************************************************/
/*!
\brief - Check mouse inputs
*/
/******************************************************************************/
void Setting::UpdateMouse(void)
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
void Setting::SetMenuAssets(void)
{
	title = new Object(AT_HUD, m_OBM);
	background = new Object(AT_HUD, m_OBM);

	title->AddComponent(ComponentFactory::CreateComponent(title, CT_TEXT));
	title->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(-165.f, 175.f, 10.f));
	title->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(1.f, 1.f));
	title->GetComponent<Text>(CT_TEXT)->SetText("Settings");
	title->GetComponent<Text>(CT_TEXT)->SetFontSize(100);
	title->GetComponent<Text>(CT_TEXT)->SetColor(vec4(1, 1, 1, 1.f));

	vec3 res(
		static_cast<float>(m_GSM->GetResolution().width),
		static_cast<float>(m_GSM->GetResolution().height));

	background->AddComponent(ComponentFactory::CreateComponent(background, CT_SPRITE));
	background->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(0, 0.f, -50.f));
	background->GetComponent<Transform>(CT_TRANSFORM)->SetScale(res);
	background->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Menu_Background"));
	background->GetComponent<Sprite>(CT_SPRITE)->SetRippleToggle(true);

	m_OBM->AddObject(title);
	m_OBM->AddObject(background);

	// Set everything default
	//m_GSM->GetGameData()->unlockTM = false;
	//m_GSM->GetGameData()->unlockSearch = false;
	//m_GSM->GetGameData()->player_death = 0;

	bgColor = vec4(1, 0, 0, 1);
}

/******************************************************************************/
/*!
\brief - Update menu stage
*/
/******************************************************************************/
void Setting::UpdateMenuAssets(float dt)
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
