/******************************************************************************/
/*!
\file   BasicControl.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016-09-11(yy/mm/dd)

\description
Contains BasicControl class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "BasicControl.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - BasicControlBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* BasicControlBuilder::BuildLogic(Object* Owner, LogicType key) const
{
	return new BasicControl(Owner, key);
}

/******************************************************************************/
/*!
\brief - BasicControl constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
BasicControl::BasicControl(Object* owner, LogicType key)
	: GameLogic(owner, key)
{

}

/******************************************************************************/
/*!
\brief - Load BasicControl info
\param data - json parser
*/
/******************************************************************************/
void BasicControl::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize BasicControl info
*/
/******************************************************************************/
void BasicControl::Init(void)
{
	m_GSM->GetGameData()->immortal = false;
	
	if (m_GSM->GetCurrentState() != ST_SPLASH
		&& m_GSM->GetCurrentState() != ST_PAUSE
		&& m_GSM->GetCurrentState() != ST_CREDIT
		&& m_GSM->GetCurrentState() != ST_SETTING
		&& m_GSM->GetCurrentState() != ST_MENU

		// TODO
		// ADD BGM TO THESE STAGES
		&& m_GSM->GetCurrentState() != ST_INTRO
		&& m_GSM->GetCurrentState() != ST_ENDING)
		m_GSM->GetGameData()->resumeBGM = m_OBM->GetGameSound()->GetAudio("BGM");
}

/******************************************************************************/
/*!
\brief - Update BasicControl info
\param dt - delta time
*/
/******************************************************************************/
void BasicControl::Update(float /*dt*/)
{
	/***************** Cheat code *****************/
	// immortal player
	if (InputManager::GetInstance().KeyTriggered(KEY_X))
		m_GSM->GetGameData()->immortal = !m_GSM->GetGameData()->immortal;

	// no footstep noise
	if (InputManager::GetInstance().KeyTriggered(KEY_C))
		m_GSM->GetGameData()->silent = !m_GSM->GetGameData()->silent;

	// Unlock this when the game is published
	// This code will be removed
	if (InputManager::GetInstance().KeyTriggered(KEY_V)) {
		m_GSM->GetGameData()->unlockSearch = true;
		m_GSM->GetGameData()->unlockTM = true;
	}

	// Increase the point
	if (InputManager::GetInstance().KeyTriggered(KEY_Z))
		m_GSM->GetGameData()->player_point += 100;
	
	/***************** Cheat code *****************/

	BasicStateControl();

	for (auto it : m_OBM->GetGameSound()->GetAudioMap())
		it.second->SetVolume(
			m_GSM->GetGameData()->volume);
}

/******************************************************************************/
/*!
\brief - Shutdown BasicControl info
*/
/******************************************************************************/
void BasicControl::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload BasicControl info
*/
/******************************************************************************/
void BasicControl::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Basic State Control function
*/
/******************************************************************************/
void BasicControl::BasicStateControl(void)
{
	if (m_GSM->GetCurrentState() != ST_MENU
		&& m_GSM->GetCurrentState() != ST_SPLASH
		&& m_GSM->GetCurrentState() != ST_CREDIT
		&& m_GSM->GetCurrentState() != ST_SETTING)
	{
		if (InputManager::GetInstance().KeyTriggered(KEY_ESC)
			/*|| InputManager::GetInstance().KeyTriggered(KEY_BACK)*/
            || (XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->START)))
		{
			if (m_GSM->GetCurrentState() != ST_PAUSE)
				m_GSM->Pause(ST_PAUSE);
			else
				m_GSM->Resume();
		}
	}
	
	if (m_GSM->GetCurrentState() != ST_PAUSE
		&& m_GSM->GetCurrentState() != ST_CREDIT
		&& m_GSM->GetCurrentState() != ST_SETTING
		&& m_GSM->GetCurrentState() != ST_HTP)
	{

		if (InputManager::GetInstance().KeyTriggered(KEY_1))
			m_GSM->SetNextStage(ST_TUTORIALS_1);

		else if (InputManager::GetInstance().KeyTriggered(KEY_2))
			m_GSM->SetNextStage(ST_TUTORIALS_2);

		else if (InputManager::GetInstance().KeyTriggered(KEY_3))
			m_GSM->SetNextStage(ST_TUTORIALS_3);

		else if (InputManager::GetInstance().KeyTriggered(KEY_4))
			m_GSM->SetNextStage(ST_TUTORIALS_4);

		else if (InputManager::GetInstance().KeyTriggered(KEY_5))
			m_GSM->SetNextStage(ST_TUTORIALS_5);

		else if (InputManager::GetInstance().KeyTriggered(KEY_6))
			m_GSM->SetNextStage(ST_TUTORIALS_6);

		else if (InputManager::GetInstance().KeyTriggered(KEY_7))
			m_GSM->SetNextStage(ST_LV1);

		else if (InputManager::GetInstance().KeyTriggered(KEY_8))
			m_GSM->SetNextStage(ST_LV2);

		else if (InputManager::GetInstance().KeyTriggered(KEY_9))
			m_GSM->SetNextStage(ST_LV3);

		else if (InputManager::GetInstance().KeyTriggered(KEY_0))
			m_GSM->SetNextStage(ST_LV4);
		
		else if (InputManager::GetInstance().KeyTriggered(KEY_UNDERSCORE))
			m_GSM->SetNextStage(ST_LV5);

		else if (InputManager::GetInstance().KeyTriggered(KEY_EQUALS))
			m_GSM->SetNextStage(ST_MENU);
	}
}
