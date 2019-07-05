/******************************************************************************/
/*!
\file   Splash.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/11/15(yy/mm/dd)

\description
Contains Splash logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Splash.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - SplashBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* SplashBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Splash(Owner, key);
}

/******************************************************************************/
/*!
\brief - Splash constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Splash::Splash(Object* Owner, LogicType key)
: GameLogic(Owner, key),  m_order(0), toggle(false), m_color(vec4(1,1,1,0)), m_res(vec3())
{}

/******************************************************************************/
/*!
\brief - Load Splash info
\param data - json parser
*/
/******************************************************************************/
void Splash::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize Splash info
*/
/******************************************************************************/
void Splash::Init(void)
{
	m_GSM->GetGameData()->volume = .5f;
	m_GSM->GetGameData()->silent = false;

	m_res = m_GSM->GetGameData()->resolution = vec2(
		static_cast<float>(m_GSM->GetResolution().width), 
		static_cast<float>(m_GSM->GetResolution().height));
	m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetScale(m_GSM->GetGameData()->resolution);
	m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(m_color);
}

/******************************************************************************/
/*!
\brief - Update Splash info
\param dt - delta time
*/
/******************************************************************************/
void Splash::Update(float dt)
{
	static float speed = .6f;

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
		m_color -= dt * speed;
		if (m_color.w < 0.f)
		{
			m_order++;
			switch (m_order)
			{
			case 1:
				m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(m_res.x * .75f, m_res.y * .5f));
				m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("FMOD"));
				break;
			case 2:
				m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(m_res.x* .5f, m_res.x* .5f));
				m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("TeamLogo"));
				break;
			case 3:
				m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(m_res.x, m_res.y));
				m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("XboxSplash"));
				break;
			}

			toggle = false;
			m_color.w = 0.f;
		}
	}

	m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(m_color);

	// If splash screen's over or
	// got any input pressed,
	// move to the main screen
	// Digipen logo should be shown enough
    bool xInput = XboxInput::Instance()->IsConnected();
	if ((xInput && XboxInput::Instance()->GetAnyButtonTrigger()) ||
        InputManager::GetInstance().AnyKeyPressed() || m_order == 4)
		m_GSM->SetNextStage(ST_MENU);
}

/******************************************************************************/
/*!
\brief - Shutdown Splash info
*/
/******************************************************************************/
void Splash::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload Splash info
*/
/******************************************************************************/
void Splash::Unload(void)
{

}
