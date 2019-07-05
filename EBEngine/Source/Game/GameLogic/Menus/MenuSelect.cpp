/******************************************************************************/
/*!
\file   MenuSelect.cpp
\author Jeong Juyong
\par    email: jeykop14@gmail.com
\date   2016/10/31(yy/mm/dd)

\description
Contains MenuSelect logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "MenuSelect.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - MenuSelectBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* MenuSelectBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new MenuSelect(Owner, key);
}

/******************************************************************************/
/*!
\brief - MenuSelect constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
MenuSelect::MenuSelect(Object* Owner, LogicType key)
: GameLogic(Owner, key), selectSfx(nullptr)
{}

/******************************************************************************/
/*!
\brief - Load MenuSelect info
\param data - json parser
*/
/******************************************************************************/
void MenuSelect::Load(const Json::Value& data)
{
	if (data.isMember("Content") &&
		data["Content"].isString())
	{
		saveData = data["Content"].asCString();
		m_select = S_NONE;

		if (m_GSM->GetCurrentState() == ST_MENU) {
			if (!strcmp("QUIT GAME", data["Content"].asCString()))
				m_select = M_QUIT;
			else if (!strcmp("PLAY", data["Content"].asCString()))
				m_select = M_PLAY;
			else if (!strcmp("OPTIONS", data["Content"].asCString()))
					m_select = M_SETTING;
			else if (!strcmp("CREDITS", data["Content"].asCString()))
				m_select = M_CREDIT;
		}
		
		else if (m_GSM->GetCurrentState() == ST_SETTING
			|| m_GSM->GetCurrentState() == ST_CREDIT
			|| m_GSM->GetCurrentState() == ST_HTP) {
			if (!strcmp("BACK", data["Content"].asCString()))
				m_select = M_BACK;
			
			else if (!strcmp("ON", data["Content"].asCString()))
				m_select = S_ON;
			else if (!strcmp("OFF", data["Content"].asCString()))
				m_select = S_OFF;
			
			//else if (!strcmp("Save", data["Content"].asCString()))
			//	m_select = S_SAVE;
			//else if (!strcmp("Load", data["Content"].asCString()))
			//	m_select = S_LOAD;
			
			else if (!strcmp("<", data["Content"].asCString()))
				m_select = V_LEFT;
			else if (!strcmp(">", data["Content"].asCString()))
				m_select = V_RIGHT;

			//else if (!strcmp("1280X1024", data["Content"].asCString()))
			//	m_select = R_1280X1024;
			//else if (!strcmp("1920X1080", data["Content"].asCString()))
			//	m_select = R_1920X1080;
			//else if (!strcmp("1024X768", data["Content"].asCString()))
			//	m_select = R_1024X768;
		}
		
		else if (m_GSM->GetCurrentState() == ST_PAUSE) {
			if (!strcmp("RESUME GAME", data["Content"].asCString()))
				m_select = M_BACK;

			else if (!strcmp("RESTART GAME", data["Content"].asCString()))
				m_select = P_RESTART;

			else if (!strcmp("QUIT GAME", data["Content"].asCString()))
				m_select = M_QUIT;

			else if (!strcmp("HOW TO PLAY", data["Content"].asCString()))
				m_select = P_HOWTOPLAY;

			else if (!strcmp("GO TO MENU", data["Content"].asCString()))
				m_select = P_GOTOMENU;

			else if (!strcmp("OPTIONS", data["Content"].asCString()))
				m_select = P_SETTING;
			
		}

		else if (!strcmp("YES", data["Content"].asCString()))
			m_select = C_YES;

		else if (!strcmp("NO", data["Content"].asCString()))
			m_select = C_NO;
	}
}

/******************************************************************************/
/*!
\brief - Initialize MenuSelect info
*/
/******************************************************************************/
void MenuSelect::Init(void)
{
	tc[3] = (false, false, false);

    m_pos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
    m_scale = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetScale();

    menu_text = new Object(m_Owner->GetArcheType(), m_OBM);
	menu_text->AddComponent(ComponentFactory::CreateComponent(menu_text, CT_TRANSFORM));
	menu_text->AddComponent(ComponentFactory::CreateComponent(menu_text, CT_TEXT));
	menu_text->GetComponent<Text>(CT_TEXT)->SetText(saveData.c_str());
	
	int lower = 0, rest = 0;
	for (char it : saveData)
		if (it >= 97 && it <= 122)
			lower++;
	rest = saveData.length() - lower;
	
	float fontSize = float(menu_text->GetComponent<Text>(CT_TEXT)->GetFontData().m_fontSize);
	float deno = (float(rest) * 1.f + float(lower) * .6f);
	float textLength = fontSize * deno;
	
	m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3((textLength* .75f), (m_scale.y * .75f), m_scale.z));
	m_scale = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetScale();
	menu_text->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(m_pos.x - (m_scale.x / 2.f - deno), m_pos.y, m_pos.z+1.f));
	menu_text->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(1.f, 1.f, 0.f));
	m_OBM->AddObject(menu_text);

	m_color = Random::GetInstance().GetRandomVec3(0.f, 1.f);
	m_color.w = 1.f;

	m_OBM->GetGameSound()->AddAudio("select", "select");
	selectSfx = m_OBM->GetGameSound()->GetAudio("select");
	selectSfx->SetVolume(m_GSM->GetGameData()->volume);

	MakeConfirm();
}

/******************************************************************************/
/*!
\brief - Update MenuSelect info
\param dt - delta time
*/
/******************************************************************************/
void MenuSelect::Update(float dt)
{
	if ((InputManager::GetInstance().KeyTriggered(KEY_ESC) 
		|| XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->START))
		&& m_GSM->GetCurrentState() == ST_MENU
		&& m_select == M_QUIT) {
		DoConfirm();
	}

	GetMouse(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown MenuSelect info
*/
/******************************************************************************/
void MenuSelect::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload MenuSelect info
*/
/******************************************************************************/
void MenuSelect::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Unload MenuSelect info
*/
/******************************************************************************/
void MenuSelect::SetTexts(std::string texts)
{
	saveData = texts;
}

/******************************************************************************/
/*!
\brief - Unload MenuSelect info
*/
/******************************************************************************/
void MenuSelect::DoConfirm(void)
{
	if (!m_GSM->GetGameData()->confirm)
	{
		std::vector <Object*> confirms;
		m_OBM->GetObjects(AT_CONFIRM, confirms);
		for (auto it : confirms) {
			if (it->HasComponent(CT_SPRITE))
				it->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 1, 1, .5f));

			else if (it->HasComponent(CT_TEXT))
				it->GetComponent<Text>(CT_TEXT)->SetColor(vec4(1, 1, 1, 1));
		}
		m_GSM->GetGameData()->confirm = true;
	}

	else
	{
		std::vector <Object*> confirms;
		m_OBM->GetObjects(AT_CONFIRM, confirms);
		for (auto it : confirms) {
			if (it->HasComponent(CT_SPRITE))
				it->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4());

			else if (it->HasComponent(CT_TEXT))
				it->GetComponent<Text>(CT_TEXT)->SetColor(vec4());
		}
		m_GSM->GetGameData()->confirm = false;
	}
}

/******************************************************************************/
/*!
\brief - Check mouse input
\param dt
*/
/******************************************************************************/
void MenuSelect::GetMouse(float dt)
{
	// Check mouse collision
	if (m_Owner->GetComponent<RigidBody>(CT_RIGIDBODY)->IsCollidedWith(
		m_GSM->GetGameData()->mouseID))
	{
		if (sfxBool) {
			selectSfx->Play();
			sfxBool = false;
		}

		m_GSM->GetGameData()->menuSelection = m_select;
		m_GSM->GetGameData()->onMenuMouse = true;
		m_GSM->GetGameData()->menuKeyPressed = false;
	}

	else {
		sfxBool = true;
		m_GSM->GetGameData()->onMenuMouse = false;

		if (!m_GSM->GetGameData()->menuKeyPressed)
			m_GSM->GetGameData()->menuSelection = -1;
	}

	// Check selection value
	if (m_GSM->GetGameData()->menuSelection == int(m_select)
		&& (m_Owner->GetArcheType() == AT_MENU
			|| ((m_select == C_YES || m_select == C_NO)
				&& m_GSM->GetGameData()->confirm))
		)
	{
		// Set the Xbox Input Toggle
		bool xInput = XboxInput::Instance()->IsConnected();

		ColorEffect(dt);
		if ((InputManager::GetInstance().KeyTriggered(MOUSE_LEFT)
			&& m_GSM->GetGameData()->onMenuMouse)
			|| (InputManager::GetInstance().KeyTriggered(KEY_ENTER) ||
			(xInput && XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->XBOX_A))))
			DoResponse();
	}
	else {
		m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4());
		m_color = Random::GetInstance().GetRandomVec3(0.f, 1.f);
	}
}

/******************************************************************************/
/*!
\brief - Update response by input
*/
/******************************************************************************/
void MenuSelect::DoResponse(void)
{
	// In Menu stage
	if (m_GSM->GetCurrentState() == ST_MENU)
	{
		if (!m_GSM->GetGameData()->confirm)
			switch (m_select)
			{
				// On main menu
			case M_PLAY:
				m_GSM->SetNextStage(ST_INTRO);
				break;
			case M_SETTING:
				m_GSM->Pause(ST_SETTING);
				break;
			case M_CREDIT:
				m_GSM->Pause(ST_CREDIT);
				break;
			case M_QUIT:
				DoConfirm();
				m_GSM->GetGameData()->quitApp = true;
				break;
			}

		else
			switch (m_select)
			{
				// On main menu
			case C_YES:
				m_GSM->SetQuit(true);
				break;
			case C_NO:
				DoConfirm();
				break;
			}
	}

	else if (m_GSM->GetCurrentState() == ST_PAUSE)
	{
		if (!m_GSM->GetGameData()->confirm)
			switch (m_select)
			{
			case M_BACK:
				m_GSM->Resume();
				break;
			case P_RESTART:
				DoConfirm();
				m_GSM->GetGameData()->restart = true;
				break;
			case P_HOWTOPLAY:
				m_GSM->Pause(ST_HTP);
				break;
			case P_GOTOMENU:
				DoConfirm();
				m_GSM->GetGameData()->quitApp = false;
				break;
			case P_SETTING:
				m_GSM->Pause(ST_SETTING);
				break;
			case M_QUIT:
				DoConfirm();
				m_GSM->GetGameData()->quitApp = true;
				break;
			}

		else
			switch (m_select)
			{
				// On main menu
			case C_YES:
				if (m_GSM->GetGameData()->restart) {
					m_GSM->ResumeRestart();
					m_GSM->GetGameData()->restart = false;
				}
				else if (!m_GSM->GetGameData()->quitApp)
					m_GSM->ResumeNextStage(ST_MENU);
				else
					m_GSM->SetQuit(true);
				break;
			case C_NO:
				if (m_GSM->GetGameData()->restart)
					m_GSM->GetGameData()->restart = false;
				DoConfirm();
				break;
			}
	}

	else if (m_GSM->GetCurrentState() == ST_SETTING)
	{
        
		switch (m_select)
		{
			// On main menu
		case S_ON:
			if (!m_GSM->GetFullScreen()) {
				m_GSM->SetFullScreen(true);
				//m_GSM->SetResolution(m_GSM->GetResolution());
			}
			break;
		
		case S_OFF:
			if (m_GSM->GetFullScreen()) {
				m_GSM->SetFullScreen(false);
				//m_GSM->GetGLManager()->Resize(
				//	m_GSM->GetResolution().width, 
				//	m_GSM->GetResolution().height);
			}
			break;
		//TODO
		//case S_SAVE:
		//	DoConfirm();
		//	break;
		//case S_LOAD:
		//	DoConfirm();
		//	break;
		case V_LEFT:
		{
			float volume = m_GSM->GetGameData()->volume;

			volume -= 0.1f;
			if (volume < 0.f) {
				volume = 0.f;
				// Mute the all sounds
				m_OBM->GetGameSound()->SetMasterMuteToggle(false);
			}

			m_OBM->GetGameSound()->SetMasterVolume(volume);
			m_GSM->GetGameData()->volume = volume;
			m_GSM->GetGameData()->resumeBGM->m_channel->setVolume(volume);
			break;
		}
		case V_RIGHT:
		{
			// Unmute the all sounds
			if (!m_OBM->GetGameSound()->GetMasterMuteToggle())
				m_OBM->GetGameSound()->SetMasterMuteToggle(true);

			float volume = m_GSM->GetGameData()->volume;

			volume += 0.1f;
			if (volume >= 1.f)
				volume = 1.f;
			
			m_OBM->GetGameSound()->SetMasterVolume(volume);
			m_GSM->GetGameData()->volume = volume;
			m_GSM->GetGameData()->resumeBGM->m_channel->setVolume(volume);
			break;
		}
		/*case R_1280X1024:
			if (m_GSM->GetResolution() != SCR_1280X1024) {
				if (!m_GSM->GetFullScreen()) {
					m_GSM->SetResolution(SCR_1280X1024);
				}
				else
				{
                    m_GSM->SetResolution(SCR_1280X1024);
				}
			}
			break;
		case R_1920X1080:
			if (m_GSM->GetResolution() != SCR_1920X1080) {
				if (!m_GSM->GetFullScreen()) {
					m_GSM->SetResolution(SCR_1920X1080);
				}
				else
				{
                    m_GSM->SetResolution(SCR_1920X1080);
				}
			}
			break;
		case R_1024X768:
			if (m_GSM->GetResolution() != SCR_1024X768) {
				if (!m_GSM->GetFullScreen()) {
					m_GSM->SetResolution(SCR_1024X768);
				}
				else
				{
                    m_GSM->SetResolution(SCR_1024X768);
				}
			}
			break;*/
		case M_BACK:
			m_GSM->Resume();
			break;
		}
	}
	else if (m_GSM->GetCurrentState() == ST_CREDIT)
	{
		switch (m_select) {
		case M_BACK:
            
			if (m_GSM->GetGameData()->gameEnded) {
				m_GSM->GetGameData()->gameEnded = false;
				m_GSM->SetNextStage(ST_MENU);
			}
			else
				m_GSM->Resume();
			break;
		}
	}

	else if (m_GSM->GetCurrentState() == ST_HTP)
	{
		switch (m_select) {
		case M_BACK:
				m_GSM->Resume();
			break;
		}
	}
}

/******************************************************************************/
/*!
\brief - Color effect
\param dt 
*/
/******************************************************************************/
void MenuSelect::ColorEffect(float dt)
{
	if (m_select != S_NONE)
	{
		// Random title color
		if (tc[0]) {
			m_color.x += dt;
			if (m_color.x > 1.f) {
				tc[0] = !tc[0];
				m_color.x = 1.f;
			}
		}

		else {
			m_color.x -= dt;
			if (m_color.x < .25f) {
				tc[0] = !tc[0];
				m_color.x = 0.25f;
			}
		}

		if (tc[1]) {
			m_color.y += dt;
			if (m_color.y > 1.f) {
				tc[1] = !tc[1];
				m_color.y = 1.f;
			}
		}

		else {
			m_color.y -= dt;
			if (m_color.y < .25f) {
				tc[1] = !tc[1];
				m_color.y = .25f;
			}
		}

		if (tc[2]) {
			m_color.z += dt;
			if (m_color.z > .25f) {
				tc[2] = !tc[2];
				m_color.z = .25f;
			}
		}

		else {
			m_color.z -= dt;
			if (m_color.z < .25f) {
				tc[2] = !tc[2];
				m_color.z = .25f;
			}
		}
		m_color.w = 1.f;
		m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(m_color);
	}
}

/******************************************************************************/
/*!
\brief - Init confirm window
*/
/******************************************************************************/
void MenuSelect::MakeConfirm(void)
{
	if (m_select == M_QUIT)
	{
		// Makes confirm menus
		m_ask = new Object(AT_CONFIRM, m_OBM);
		m_yes = new Object(AT_CONFIRM, m_OBM);
		m_no = new Object(AT_CONFIRM, m_OBM);
		m_askText = new Object(AT_CONFIRM, m_OBM);

		// Text boxes setting
		m_ask->AddComponent(ComponentFactory::CreateComponent(m_ask, CT_SPRITE));
		m_yes->AddComponent(ComponentFactory::CreateComponent(m_yes, CT_SPRITE));
		m_no->AddComponent(ComponentFactory::CreateComponent(m_no, CT_SPRITE));

		//m_ask->AddComponent(ComponentFactory::CreateComponent(m_ask, CT_RIGIDBODY));
		m_yes->AddComponent(ComponentFactory::CreateComponent(m_yes, CT_RIGIDBODY));
		m_no->AddComponent(ComponentFactory::CreateComponent(m_no, CT_RIGIDBODY));

		//m_ask->GetComponent<RigidBody>(CT_RIGIDBODY)->ActivateResponse(false);
		//m_ask->GetComponent<RigidBody>(CT_RIGIDBODY)->ActivateResponse(false);
		m_yes->GetComponent<RigidBody>(CT_RIGIDBODY)->ActivateResponse(false);
		m_yes->GetComponent<RigidBody>(CT_RIGIDBODY)->ActivateMove(false);
		m_no->GetComponent<RigidBody>(CT_RIGIDBODY)->ActivateMove(false);
		m_no->GetComponent<RigidBody>(CT_RIGIDBODY)->ActivateMove(false);

		m_ask->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(-10, 25, 25.f));
		m_yes->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(-50.f, -75.f, 30.f));
		m_no->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(25.f, -75.f, 30.f));

		m_ask->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(400.f, 300.f));
		m_yes->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(100.f, 50.f));
		m_no->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(100.f, 50.f));

		m_ask->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Window"));
		m_yes->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("rect"));
		m_no->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("rect"));

		m_ask->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(0, 0, 0, .5f));

		m_yes->AddLogic(LogicFactory::CreateLogic(m_yes, MENUSELECT));
		m_no->AddLogic(LogicFactory::CreateLogic(m_no, MENUSELECT));

		m_yes->GetLogic<MenuSelect>(MENUSELECT)->saveData = "YES";
		m_no->GetLogic<MenuSelect>(MENUSELECT)->saveData = "NO";

		m_yes->GetLogic<MenuSelect>(MENUSELECT)->m_select = C_YES;
		m_no->GetLogic<MenuSelect>(MENUSELECT)->m_select = C_NO;

		m_OBM->AddObject(m_ask);
		m_OBM->AddObject(m_yes);
		m_OBM->AddObject(m_no);

		// Texts setting
		m_askText->AddComponent(ComponentFactory::CreateComponent(m_askText, CT_TEXT));
		m_askText->GetComponent<Text>(CT_TEXT)->SetText("Are you sure?");
		m_askText->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(1, 1));
		m_askText->GetComponent<Text>(CT_TEXT)->SetFontSize(50);
		m_askText->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(-145, 100, 50.f));

		m_OBM->AddObject(m_askText);

		std::vector <Object*> confirms;
		m_OBM->GetObjects(AT_CONFIRM, confirms);
		for (auto it : confirms) {
			if (it->HasComponent(CT_SPRITE))
				it->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4());

			else if (it->HasComponent(CT_TEXT))
				it->GetComponent<Text>(CT_TEXT)->SetColor(vec4());
		}
	}
}

