/******************************************************************************/
/*!
\file   CutScene.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/06/11(yy/mm/dd)

\description
Contains CutScene logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "CutScene.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - CutSceneBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* CutSceneBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new CutScene(Owner, key);
}

/******************************************************************************/
/*!
\brief - CutScene constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
CutScene::CutScene(Object* Owner, LogicType key)
: GameLogic(Owner, key), m_order(0), toggle(false), m_color(vec4(1, 1, 1, 0))
{}

/******************************************************************************/
/*!
\brief - Load CutScene info
\param data - json parser
*/
/******************************************************************************/
void CutScene::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize CutScene info
*/
/******************************************************************************/
void CutScene::Init(void)
{
	// Intro Cutscene
	if (m_GSM->GetCurrentState() == ST_INTRO) {
		m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Intro_1"));
	}

	// Ending Cutscene
	// else if (m_GSM->GetCurrentState() == ST_ENDING)
	else {
		m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("End_1"));
	}
	
}

/******************************************************************************/
/*!
\brief - Update CutScene info
\param dt - delta time
*/
/******************************************************************************/
void CutScene::Update(float dt)
{
	static float speed = .25f;

	// Intro Cutscene
	if (m_GSM->GetCurrentState() == ST_INTRO) {
        bool xInput = XboxInput::Instance()->IsConnected();
		if ((xInput && XboxInput::Instance()->GetAnyButtonTrigger()) ||
			InputManager::GetInstance().AnyKeyPressed())
		{

			if (m_order == 0) {
				m_order = 1;
				m_color.w = 0.f;
				toggle = false;
				m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Intro_2"));
			}

			else if (m_order == 1)
				m_GSM->SetNextStage(ST_TUTORIALS_1);
		}

		// Alpha value changing
		if (!toggle)
		{
			m_color.w += dt * speed;

			// Lock w value chaging
			if (m_color.w > 1.f) {
				m_color.w = 1.f;
				toggle = true;
			}
		}

		else
		{
			m_color -= dt * speed;
			if (m_color.w < 0.f)
			{
				m_order++;
				switch (m_order)
				{
				case 1:
					m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Intro_2"));
					break;
				}

				toggle = false;
				m_color.w = 0.f;
			}
		}
	}

	// Ending Cutscene
	// else if (m_GSM->GetCurrentState() == ST_ENDING)
	else {
        bool xInput = XboxInput::Instance()->IsConnected();
		if ((xInput && XboxInput::Instance()->GetAnyButtonTrigger()) ||
            InputManager::GetInstance().AnyKeyPressed()
			|| m_order == 1) {
			m_GSM->GetGameData()->gameEnded = true;
			m_GSM->SetNextStage(ST_CREDIT);
		}
		// Alpha value changing
		if (!toggle)
		{
			m_color += dt * speed;

			// Lock w value chaging
			if (m_color.w > 1.f) {
				m_color.w = 1.f;
				toggle = true;
			}
		}

		else
		{
			m_color.w -= dt * speed;
			if (m_color.w < 0.f)
			{
				m_order++;
				toggle = false;
				m_color.w = 0.f;
			}
		}

	}

	m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(m_color);
}

/******************************************************************************/
/*!
\brief - Shutdown CutScene info
*/
/******************************************************************************/
void CutScene::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload CutScene info
*/
/******************************************************************************/
void CutScene::Unload(void)
{

}
