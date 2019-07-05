/******************************************************************************/
/*!
\file   FadeScreen.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/04/04(yy/mm/dd)

\description
Contains FadeScreen logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "FadeScreen.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - FadeScreenBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* FadeScreenBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new FadeScreen(Owner, key);
}

/******************************************************************************/
/*!
\brief - FadeScreen constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
FadeScreen::FadeScreen(Object* Owner, LogicType key)
: GameLogic(Owner, key), m_color(vec4(0,0,0,1.f)), m_speed(1.f), m_condition(FADE_ON),
m_gameOn(true), fade(nullptr)
{}

/******************************************************************************/
/*!
\brief - Load FadeScreen info
\param data - json parser
*/
/******************************************************************************/
void FadeScreen::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize FadeScreen info
*/
/******************************************************************************/
void FadeScreen::Init(void)
{
	m_res.x = static_cast<float>(m_GSM->GetResolution().width);
	m_res.y = static_cast<float>(m_GSM->GetResolution().height);

	fade = new Object(AT_FADE, m_OBM);
	fade->AddComponent(ComponentFactory::CreateComponent(fade, CT_SPRITE));
	fade->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("rect"));
	fade->GetComponent<Transform>(CT_TRANSFORM)->SetScale(m_res);
	
	vec3 tmp = fade->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
	fade->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(tmp.x, tmp.y, 20.f));

	m_OBM->AddObject(fade);
}

/******************************************************************************/
/*!
\brief - Update FadeScreen info
\param dt - delta time
*/
/******************************************************************************/
void FadeScreen::Update(float dt)
{
    if (m_condition == FADE_ON) {
        if (m_gameOn)
            m_color.w -= dt /** .1f*/;

        else
            m_color.w += dt /** m_speed*/;
    }

    if (m_color.w > 1.f) {
        m_color.w = 1.f;
        m_condition = FADE_OUT;
    }

    if (m_color.w < 0.f) {
        m_color.w = 0.f;
        m_condition = FADE_IN;
    }

    m_pos = m_GSM->GetGameData()->cameraPos;
    m_pos.z = 99.f;

    fade->GetComponent<Sprite>(CT_SPRITE)->SetColor(m_color);
    fade->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(m_pos);

    if (m_GSM->GetGameData()->gamenextCondition == true && m_GSM->GetGameData()->gamegradeCondition == false
        && m_color.w > 0.9f)
    {
        SetGameOn(false);
        m_GSM->GetGameData()->player_death = 0;
    }
    else if (m_GSM->GetGameData()->gamenextCondition == true || m_GSM->GetGameData()->gameoverCondition == true)
    {
        SetGameOn(false);
        m_OBM->GetGameSound()->GetAudio("BGM")->SetMuteToggle(false);
        m_OBM->GetGameSound()->GetAudio("chopper")->SetMuteToggle(false);
    }
    else if (m_GSM->GetGameData()->gameclearCondition == true
        && m_GSM->GetGameData()->gamenextCondition == false
        && m_GSM->GetGameData()->grade_Fade == true)
    {
        SetGameOn(false);
    }
    else if (m_GSM->GetGameData()->gameclearCondition == false && m_GSM->GetGameData()->gamegradeCondition == true)
    {
        SetGameOn(true);
    }
}

/******************************************************************************/
/*!
\brief - Shutdown FadeScreen info
*/
/******************************************************************************/
void FadeScreen::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload FadeScreen info
*/
/******************************************************************************/
void FadeScreen::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Unload FadeScreen info
\param toggle - Turn toggle on /off
*/
/******************************************************************************/
void FadeScreen::SetGameOn(bool toggle) 
{ 
	m_condition = FADE_ON;
	m_gameOn = toggle; 
}
