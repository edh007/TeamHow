/******************************************************************************/
/*!
\file   GameOver.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2016/12/13(yy/mm/dd)

\description
Contains GameOver logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "GameOver.h"
#include "../../../BaseData/BaseEnigne.h"
#include "../Environment/Door.h"
#include "../Player/Player.h"

/******************************************************************************/
/*!
\brief - GameOverBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* GameOverBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new GameOver(Owner, key);
}

/******************************************************************************/
/*!
\brief - GameOver constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
GameOver::GameOver(Object* Owner, LogicType key)
	: GameLogic(Owner, key), showTime(3.f), waitTime(0.f), chopper(nullptr),
	m_victory(nullptr)
{}

/******************************************************************************/
/*!
\brief - Load GameOver info
\param data - json parser
*/
/******************************************************************************/
void GameOver::Load(const Json::Value& data)
{
	if (data.isMember("ShowTime") &&
		data["ShowTime"].isNumeric())
        clearShowTime = data["ShowTime"].asFloat();

	if (data.isMember("Stage") &&
		data["Stage"].isString())
	{
		if (!strcmp(data["Stage"].asCString(), "LV1"))
			next = ST_LV1;
		else if (!strcmp(data["Stage"].asCString(), "LV2"))
			next = ST_LV2;
		else if (!strcmp(data["Stage"].asCString(), "LV3"))
			next = ST_LV3;
		else if (!strcmp(data["Stage"].asCString(), "LV4"))
			next = ST_LV4;
		else if (!strcmp(data["Stage"].asCString(), "LV5"))
			next = ST_LV5;
		else if (!strcmp(data["Stage"].asCString(), "Menu"))
			next = ST_MENU;
		else if (!strcmp(data["Stage"].asCString(), "Tutorials_1"))
			next = ST_TUTORIALS_1;
		else if (!strcmp(data["Stage"].asCString(), "Tutorials_2"))
			next = ST_TUTORIALS_2;
		else if (!strcmp(data["Stage"].asCString(), "Tutorials_3"))
			next = ST_TUTORIALS_3;
		else if (!strcmp(data["Stage"].asCString(), "Tutorials_4"))
			next = ST_TUTORIALS_4;
		else if (!strcmp(data["Stage"].asCString(), "Tutorials_5"))
			next = ST_TUTORIALS_5;
		else if (!strcmp(data["Stage"].asCString(), "Tutorials_6"))
			next = ST_TUTORIALS_6;
		else
			next = ST_ENDING;
	}
}

/******************************************************************************/
/*!
\brief - Initialize GameOver info
*/
/******************************************************************************/
void GameOver::Init(void)
{
	m_OBM->GetObjects(AT_DOOR, door);

	if (door.size())
		door_id = door[0]->GetID();
	else
		door_id = 0;

	if (player.size())
		player_id = player[0]->GetID();
	else
		player_id = 0;

	m_OBM->GetGameSound()->AddAudio("victory", "victory");
	m_victory = m_OBM->GetAudio("victory");
	m_victory->SetVolume(m_GSM->GetGameData()->volume);
	//m_victory->SetVolume(1.f);
    
	std::string tmp("STAGE : ");
    tmp += std::to_string(m_GSM->GetCurrentState() + 1);

	m_Owner->GetComponent<Text>(CT_TEXT)->SetFontSize(50);
	m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(1.f,1.f,1.f));
	m_Owner->GetComponent<Text>(CT_TEXT)->SetText(tmp.c_str());
    m_Owner->GetComponent<Text>(CT_TEXT)->SetColor(vec4(1, 1, 1, 1));

	m_GSM->GetGameData()->gamenextCondition = false;
	m_GSM->GetGameData()->gameoverCondition = false;
    m_GSM->GetGameData()->gamegradeCondition = false;
    m_GSM->GetGameData()->gameclearCondition = false;
	m_GSM->GetGameData()->grade_Fade = false;
	m_GSM->GetGameData()->gradeTime = 0.f;
	
	chopper = new Object(AT_CHOPPER, m_OBM);
	chopper->AddComponent(ComponentFactory::CreateComponent(chopper, CT_SPRITE));
	chopper->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Chopper"));
	chopper->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(250, 100));
	chopper->AddLogic(LogicFactory::CreateLogic(chopper, CHOPPER));

	m_OBM->AddObject(chopper);
}

/******************************************************************************/
/*!
\brief - Update GameOver info
\param dt - delta time
*/
/******************************************************************************/
void GameOver::Update(float dt)
{
    if (showingStage == true)
    {
        m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(m_GSM->GetGameData()->cameraPos.x + 250.f, m_GSM->GetGameData()->cameraPos.y + 300.f, 18.f));
        waitTime += dt;
        if (waitTime > showTime)
        {
            m_Owner->GetComponent<Text>(CT_TEXT)->SetFontSize(75);
            waitTime = 0.f;
            showingStage = false;
            m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(2000.f, 0.f, 0.f));
            m_Owner->GetComponent<Text>(CT_TEXT)->SetColor(vec4(1, 1, 1, 0));
        }
    }

    if (m_GSM->GetGameData()->gamenextCondition == true)
    {
        waitTime += dt;
        if(waitTime > showTime)
            m_GSM->SetNextStage(next);
    }
    else if(m_GSM->GetGameData()->gamegradeCondition != true)
    {
        if (m_OBM->HasObject(door_id))
        {
            if (door[0]->GetLogic<Door>(DOOR)->EndCondition == true)
            {
                if (XboxInput::Instance()->IsConnected())
                    XboxInput::Instance()->SetVibration(50000, 1.f);

                m_GSM->GetGameData()->player_Active = false;
                m_GSM->GetGameData()->player->GetComponent<RigidBody>(CT_RIGIDBODY)->ClearVelocity();

                m_GSM->GetGameData()->immortal = true;
                m_Owner->GetComponent<Text>(CT_TEXT)->SetText(" CLEAR! ");
                m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(m_GSM->GetGameData()->cameraPos.x - 150.f, m_GSM->GetGameData()->cameraPos.y, 30.f));
                m_Owner->GetComponent<Text>(CT_TEXT)->SetColor(vec4(1, 1, 1, 1));
                m_GSM->GetGameData()->gameclearCondition = true;
				m_GSM->GetGameData()->player_chopper = true;

				m_OBM->GetGameSound()->GetAudio("BGM")->Stop();

				if (!m_victory->IsPlaying()) {
					m_victory->Play();
					m_victory->SetPosition(m_GSM->GetGameData()->cameraPos);
				}

                waitTime += dt;
                if (waitTime > clearShowTime)
                {
                    waitTime = 0.f;
                    m_Owner->GetComponent<Text>(CT_TEXT)->SetColor(vec4(0, 0, 0, 0));
                    m_GSM->GetGameData()->gamegradeCondition = true;
                    m_GSM->GetGameData()->gameclearCondition = false;
					m_GSM->GetGameData()->grade_Fade = true;
					m_GSM->GetGameData()->gradeTime = m_GSM->GetStageTimer().GetElapsedTime();
                }
				else if (waitTime > clearShowTime - 2)
				{
					m_GSM->GetGameData()->grade_Fade = true;
					m_GSM->GetGameData()->player_chopper = true;
				}
            }
        }

        if (!m_OBM->HasObject(player_id))
        {
            if (XboxInput::Instance()->IsConnected())
                XboxInput::Instance()->SetVibration(50000, 1.f);

            m_GSM->GetGameData()->gameoverCondition = true;
            m_Owner->GetComponent<Text>(CT_TEXT)->SetText("Game Over");
            m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(m_GSM->GetGameData()->cameraPos.x - 150.f, m_GSM->GetGameData()->cameraPos.y, 30.f));
            m_Owner->GetComponent<Text>(CT_TEXT)->SetColor(vec4(1, 1, 1, 1));
            waitTime += dt;
			if (waitTime > showTime)
			{
				if(m_GSM->GetCurrentState() == ST_TUTORIALS_4)
					m_GSM->GetGameData()->unlockTM = false;
				else if (m_GSM->GetCurrentState() == ST_TUTORIALS_6)
					m_GSM->GetGameData()->unlockSearch = false;
				m_GSM->Restart(true);
			}
        }
    }
}

/******************************************************************************/
/*!
\brief - Shutdown GameOver info
*/
/******************************************************************************/
void GameOver::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload GameOver info
*/
/******************************************************************************/
void GameOver::Unload(void)
{

}
