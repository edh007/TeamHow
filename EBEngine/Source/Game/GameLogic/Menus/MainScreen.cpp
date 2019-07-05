/******************************************************************************/
/*!
\file   MainScreen.cpp
\author Jeong Juyong
\par    email: jeykop14@gmail.com
\date   2016/10/31(yy/mm/dd)

\description
Contains MainScreen logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "MainScreen.h"
#include "../../../BaseData/BaseEnigne.h"
#include "../Menus/MenuSelect.h"

/******************************************************************************/
/*!
\brief - MainScreenBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* MainScreenBuilder::BuildLogic(Object* Owner, LogicType key) const
{
	return new MainScreen(Owner, key);
}

/******************************************************************************/
/*!
\brief - MainScreen constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
MainScreen::MainScreen(Object* Owner, LogicType key)
	: GameLogic(Owner, key), toggle(true), selectSfx(nullptr),
	menu_id(-1), m_mouse(0), mouseScl(vec3()), fistSpeed(600.f), fistToggle(false)
{}

/******************************************************************************/
/*!
\brief - Load MainScreen info
\param data - json parser
*/
/******************************************************************************/
void MainScreen::Load(const Json::Value& /*data*/)
{}

/******************************************************************************/
/*!
\brief - Initialize MainScreen info
*/
/******************************************************************************/
void MainScreen::Init(void)
{
	// Default init...
	m_OBM->GetGameSound()->AddAudio("punch", "punch");
	m_fist = m_OBM->GetGameSound()->GetAudio("punch");
	m_fist->SetVolume(m_GSM->GetGameData()->volume);

	m_OBM->GetGameSound()->AddAudio("select", "select");
	selectSfx = m_OBM->GetGameSound()->GetAudio("select");
	selectSfx->SetVolume(m_GSM->GetGameData()->volume);

	m_GSM->GetGameData()->gameEnded = false;
	m_GSM->GetGameData()->confirm = false;
	SetMenuAssets();
	SetMouse();

	if (m_GSM->GetCurrentState() == ST_MENU)
		m_GSM->GetGameData()->resumeBGM = m_OBM->GetGameSound()->GetAudio("BGM");

	background->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 1, 1, 1));
}

/******************************************************************************/
/*!
\brief - Update MainScreen info
\param dt - delta time
*/
/******************************************************************************/
void MainScreen::Update(float dt)
{
	// Updates every assets in this stage
	UpdateMenuAssets(dt);
	UpdateKeys();
	UpdateMouse(dt);

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
\brief - Shutdown MainScreen info
*/
/******************************************************************************/
void MainScreen::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload MainScreen info
*/
/******************************************************************************/
void MainScreen::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Check keyboard inputs
*/
/******************************************************************************/
void MainScreen::UpdateKeys(void)
{
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

			selectSfx->Play();
			--menu_id;
			if (m_GSM->GetGameData()->confirm) {
				
				if (menu_id < 13)
					menu_id = 14;

				else
					menu_id = 13;
			}

			else
			{
				if (m_GSM->GetCurrentState() == ST_MENU) {
					if (menu_id < 0)
						menu_id = 3;

					else if (menu_id > 3)
						menu_id = 2;
				}
			
				// Pause menu
				else {
					if (menu_id < 3 || menu_id > 8)
						menu_id = 8;
				}
			}

			m_GSM->GetGameData()->menuKeyPressed = true;
			m_GSM->GetGameData()->menuSelection = menu_id;
		}

		else if (InputManager::GetInstance().KeyTriggered(KEY_RIGHT) ||
            (xInput && xInptDly && XboxInput::Instance()->leftStickX > 0.5f) ||
			(xInput && XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->DPAD_RIGHT)))
		{
            if (xInptDly == true)
                xInptDly = false;

			selectSfx->Play();
			++menu_id;
			if (m_GSM->GetGameData()->confirm) {
				
				if (menu_id > 14)
					menu_id = 13;

				else
					menu_id = 14;
			}

			else
			{
				if (m_GSM->GetCurrentState() == ST_MENU) {
					if (menu_id > 3)
						menu_id = 0;
				}

				// Pause menu
				else {
					if (menu_id > 8 || menu_id < 3)
						menu_id = 3;
				}
			}

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
void MainScreen::SetMouse(void)
{
	m_mouse = new Object(AT_MOUSE, m_OBM);
	m_mouse->AddComponent(ComponentFactory::CreateComponent(m_mouse, CT_TRANSFORM));
	mouseScl = vec3(25, 25);
	m_mouse->GetComponent<Transform>(CT_TRANSFORM)->SetScale(mouseScl);

	m_mouse->AddComponent(ComponentFactory::CreateComponent(m_mouse, CT_RIGIDBODY));
	m_mouse->GetComponent<RigidBody>(CT_RIGIDBODY)->ActivateResponse(false);
	m_mouse->GetComponent<RigidBody>(CT_RIGIDBODY)->SetShape(BALL);

	m_OBM->AddObject(m_mouse);
	m_GSM->GetGameData()->mouseID = m_mouse->GetID();
}

/******************************************************************************/
/*!
\brief - Check mouse inputs
*/
/******************************************************************************/
void MainScreen::UpdateMouse(float dt)
{
	vec3 mousePos = InputManager::GetInstance().GetOrthoPosition();
	mousePos.z = 10.f;
	mousePos.x += mouseScl.x;
	mousePos.y -= mouseScl.y;
	m_mouse->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(
		mousePos);

	// Set the Xbox Input Toggle
	bool xInput = XboxInput::Instance()->IsConnected();

	if (InputManager::GetInstance().KeyTriggered(MOUSE_LEFT) ||
		(xInput && XboxInput::Instance()->GetButtonPressed(XboxInput::Instance()->XBOX_A))) {
		if (xInput)
			XboxInput::Instance()->SetVibration(30000, 0.5f);

		fistToggle = true;
		m_fist->Play();
	}

	if (fistToggle) {
		fistScl += dt * fistSpeed;
		if (fistScl.x > 350.f) {
			fistScl = vec3(250.f, 250.f);
			fistToggle = false;
		}
	}

	else
	{
		fistScl -= dt * fistSpeed;
		if (fistScl.x < 200.f)
			fistScl = vec3(200.f, 200.f);
	}

	fist->GetComponent<Transform>(CT_TRANSFORM)->SetScale(fistScl);

	if (m_GSM->GetCurrentState() ==ST_MENU)
		m_GSM->GetGameData()->mouseID = 21;
}

/******************************************************************************/
/*!
\brief - Init menu stage assets
*/
/******************************************************************************/
void MainScreen::SetMenuAssets(void)
{
	m_OBM->GetObjects(MENUSELECT, menuList);

	// Only in menu stage
	fist = new Object(AT_HUD, m_OBM);
	fist->AddComponent(ComponentFactory::CreateComponent(fist, CT_SPRITE));
	fist->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(0, 0.f, 5.f));
	fist->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Menu_Star"));
	m_OBM->AddObject(fist);

	title = new Object(AT_HUD, m_OBM);
	background = new Object(AT_HUD, m_OBM);

	titlePos = vec3(-300.f, 175.f, 10.f);
	
	if (m_GSM->GetCurrentState() == ST_MENU)
		titlePos.y = float(m_GSM->GetResolution().height) * .5f + 100.f;
	else
		titlePos.x = -125.f;

	title->AddComponent(ComponentFactory::CreateComponent(title, CT_TEXT));
	title->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(titlePos);
	title->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(1.f, 1.f));

	if (m_GSM->GetCurrentState() == ST_MENU)
		title->GetComponent<Text>(CT_TEXT)->SetText("Captain Korea");
	else
		title->GetComponent<Text>(CT_TEXT)->SetText("Pause");
	
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
	// only when it is menu screen,
	// not pause
	if (m_GSM->GetCurrentState() == ST_MENU) {
		m_GSM->GetGameData()->unlockTM = false;
		m_GSM->GetGameData()->unlockSearch = false;
		m_GSM->GetGameData()->player_death = 0;
	
		std::vector<Object*> list;
		m_OBM->GetObjects(AT_MENU, list);
		for (auto it : list) {
			vec3 save = it->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
			if (m_GSM->GetCurrentState() == ST_MENU)
				save.y = -(float(m_GSM->GetResolution().height) * .5f + 100.f);
			else
				save.y = -200.f;
			it->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(save);
		}
	}

	bgColor = vec4(1, 0, 0, 1);
}

/******************************************************************************/
/*!
\brief - Update menu stage
*/
/******************************************************************************/
void MainScreen::UpdateMenuAssets(float dt)
{

	// Random title color
	if (colorToggle) {
		bgColor.x += dt;
		bgColor.z -= dt;
		if (bgColor.x > 1.f
			&& bgColor.z < 0.f) {
			colorToggle = !colorToggle;
			bgColor = vec4(1,0,0,1);
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

	if (m_GSM->GetCurrentState() == ST_MENU)
	{
		titlePos.y -= 150.f * dt;
		if (175.f > titlePos.y
			|| InputManager::GetInstance().AnyKeyTriggered())
			titlePos.y = 175.f;

		std::vector<Object*> list;
		m_OBM->GetObjects(AT_MENU, list);
		for (auto it : list) {
			vec3 save = it->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
			save.y += 150.f * dt;
			if (save.y > -200.f
				|| InputManager::GetInstance().AnyKeyTriggered())
				save.y = -200.f;

			if (it->HasComponent(CT_TEXT))
				save.z = 1.F;
			else
				save.z = 0.F;
			it->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(save);
		}
	}

	title->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(titlePos);
	title->GetComponent<Text>(CT_TEXT)->SetColor(bgColor);

	vec4 inverse = vec4(1, 1, 1, 1) - bgColor;
	inverse.w = 1.f;
	fist->GetComponent<Sprite>(CT_SPRITE)->SetColor(inverse);

	vec2 vector = InputManager::GetInstance().GetOrthoPosition();
	rotate = Math::RadToDeg(atan2(vector.y, vector.x));
	fist->GetComponent<Transform>(CT_TRANSFORM)->SetRotation(rotate);
}
