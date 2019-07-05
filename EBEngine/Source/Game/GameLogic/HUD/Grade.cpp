/******************************************************************************/
/*!
\file   Grade.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/07(yy/mm/dd)

\description
Contains Grade logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Grade.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - GradeBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* GradeBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Grade(Owner, key);
}

/******************************************************************************/
/*!
\brief - Grade constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Grade::Grade(Object* Owner, LogicType key)
: GameLogic(Owner, key)
{}

/******************************************************************************/
/*!
\brief - Load Grade info
\param data - json parser
*/
/******************************************************************************/
void Grade::Load(const Json::Value& data)
{
    if (data.isMember("Kill") &&
        data["Kill"].isNumeric())
        gradeKill = data["Kill"].asInt();

    if (data.isMember("Time") &&
        data["Time"].isNumeric())
        gradeTime = data["Time"].asFloat();

    if (data.isMember("Death") &&
        data["Death"].isNumeric())
        gradeDeath = data["Death"].asInt();
}

/******************************************************************************/
/*!
\brief - Initialize Grade info
*/
/******************************************************************************/
void Grade::Init(void)
{
    m_object = new Object(AT_NONE, m_OBM);

    m_object->AddComponent(ComponentFactory::CreateComponent(m_object, CT_TRANSFORM));
    m_object->AddComponent(ComponentFactory::CreateComponent(m_object, CT_SPRITE));

    m_sprite = m_object->GetComponent<Sprite>(CT_SPRITE);
    m_trs = m_object->GetComponent<Transform>(CT_TRANSFORM);

    m_trs->SetScale(vec3(1024, 768, 0));
    m_trs->SetPosition(vec3(2000, 1000, 91));

    m_sprite->SetTexture(m_GSM->GetGLManager()->GetTexture("GradeFrame"));
    m_sprite->SetColor(vec4(0.f, 0.f, 0.f, 0.f));

    m_OBM->AddObject(m_object);

    for (int i = GradeText::t_Kill; i < GradeText::t_End; ++i)
    {
        m_objectTxt[i] = new Object(AT_NONE, m_OBM);

        m_objectTxt[i]->AddComponent(ComponentFactory::CreateComponent(m_objectTxt[i], CT_TRANSFORM));
        m_objectTxt[i]->AddComponent(ComponentFactory::CreateComponent(m_objectTxt[i], CT_TEXT));

        m_trsTxt[i] = m_objectTxt[i]->GetComponent<Transform>(CT_TRANSFORM);
        m_text[i] = m_objectTxt[i]->GetComponent<Text>(CT_TEXT);

        m_text[i]->SetFontSize(35);
        m_trsTxt[i]->SetPosition(vec3(1000, 1000, 95));
        m_trsTxt[i]->SetScale(vec3(1.f, 1.f, 1.f));

        m_OBM->AddObject(m_objectTxt[i]);
    }
    
    m_text[GradeText::t_Kill]->SetText("Kill");
    m_text[GradeText::t_Time]->SetText("Time");
    m_text[GradeText::t_Death]->SetText("Death");
    m_text[GradeText::t_Report]->SetText("Report");
    m_text[GradeText::t_Total]->SetText("Total");
    m_text[GradeText::t_Score]->SetText("Score");
    m_text[GradeText::t_Instruction]->SetText("Press Any Key to go to the Next Stage");
    m_text[GradeText::t_Instruction]->SetFontSize(25);

    waitTime = 0.f;
}

/******************************************************************************/
/*!
\brief - Update Grade info
\param dt - delta time
*/
/******************************************************************************/
void Grade::Update(float dt)
{
    if (m_GSM->GetGameData()->gamegradeCondition == true)
    {
		m_OBM->GetGameSound()->GetAudio("BGM")->Stop();
        waitTime += dt;
        if (waitTime > 3.f)
        {
            bool xInput = XboxInput::Instance()->IsConnected();
            m_trsTxt[GradeText::t_Instruction]->SetPosition(vec3(
                m_GSM->GetGameData()->cameraPos.x - 500.f, m_GSM->GetGameData()->cameraPos.y - 350.f, 46));
            if (InputManager::GetInstance().AnyKeyTriggered() == true ||
                (xInput && XboxInput::Instance()->GetAnyButtonTrigger()))
            {
                m_GSM->GetGameData()->gamegradeCondition = false;
                m_GSM->GetGameData()->gamenextCondition = true;
                //m_sprite->SetColor(vec4(0.f, 0.f, 0.f, 0.f));
                //m_trs->SetPosition(vec3(2000, 1000, 45));
            }
        }
        else
            m_trs->SetPosition(vec3(m_GSM->GetGameData()->cameraPos.x, m_GSM->GetGameData()->cameraPos.y, 45));

        int death = m_GSM->GetGameData()->player_death;
        int kill = m_GSM->GetGameData()->killedEnemies;
        float time = m_GSM->GetGameData()->gradeTime;

		//// For Gradings
		//float timeElapsed, sneakTime, dashTime;
		//int sneakKill, dashKill, killedEnemies;

        std::string d;
        std::string k;
        std::string t;
        std::string c;
        
        int checkGrade = 0;
        // Dead less than Expect
        if (gradeDeath > death)
        {
            checkGrade++;
            d = "PRUDENT!";
        }
        else
            d = "RECKLESS...";

        // Kill less than Expect
        if (gradeKill > kill)
            k = "PEACEFUL!";
        else
            k = "BRUTAL!";

        // Time less than Expect
        if (gradeTime > time)
        {
            checkGrade++;
            t = "QUICK!";
        }
        else
            t = "SLOW..";

        // Good, average, bad
        if (checkGrade >= 2)
            c = "ASSASSINO!";
        else if (checkGrade >= 1)
            c = "AVERAGE.";
        else
            c = "POOR...";

        m_text[GradeText::s_Death]->SetText(d.c_str());
        m_text[GradeText::s_Kill]->SetText(k.c_str());
        m_text[GradeText::s_Time]->SetText(t.c_str());
        m_text[GradeText::s_Conclusion]->SetText(c.c_str());

		std::string r_d;
		std::string r_k;
		std::string r_t;

		r_d = std::to_string(death);
		r_k = std::to_string(kill);
		r_t = std::to_string(time);
		r_t.pop_back();
		r_t.pop_back();
		r_t.pop_back();
		m_text[GradeText::r_Death]->SetText(r_d.c_str());
		m_text[GradeText::r_Kill]->SetText(r_k.c_str());
		m_text[GradeText::r_Time]->SetText(r_t.c_str());

        //get 0,0,0 position
        vec3 pos = m_trs->GetPosition();
        m_sprite->SetColor(vec4(1.f, 1.f, 1.f, 1.f));

        // rearrange the position of the texts, kill, death, time
        m_trsTxt[GradeText::t_Report]->SetPosition(vec3(pos.x - 350.f, pos.y + 220.f, pos.z + 1));
        m_trsTxt[GradeText::t_Score]->SetPosition(vec3(pos.x + 130.f, pos.y + 220.f, pos.z + 1));
        
        m_trsTxt[GradeText::t_Kill]->SetPosition(vec3(pos.x - 350.f, pos.y + 120.f, pos.z + 1));
        m_trsTxt[GradeText::r_Kill]->SetPosition(vec3(pos.x - 130.f, pos.y + 120.f, pos.z + 1));
		m_trsTxt[GradeText::s_Kill]->SetPosition(vec3(pos.x + 130.f, pos.y + 120.f, pos.z + 1));
        
        m_trsTxt[GradeText::t_Death]->SetPosition(vec3(pos.x - 350.f, pos.y + 10.f, pos.z + 1));
        m_trsTxt[GradeText::r_Death]->SetPosition(vec3(pos.x - 130.f, pos.y + 10.f, pos.z + 1));
		m_trsTxt[GradeText::s_Death]->SetPosition(vec3(pos.x + 130.f, pos.y + 10.f, pos.z + 1));

        m_trsTxt[GradeText::t_Time]->SetPosition(vec3(pos.x - 350.f, pos.y - 90.f, pos.z + 1));
        m_trsTxt[GradeText::r_Time]->SetPosition(vec3(pos.x - 130.f, pos.y - 90.f, pos.z + 1));
		m_trsTxt[GradeText::s_Time]->SetPosition(vec3(pos.x + 130.f, pos.y - 90.f, pos.z + 1));

        m_trsTxt[GradeText::t_Total]->SetPosition(vec3(pos.x - 350.f, pos.y - 200.f, pos.z + 1));
        m_trsTxt[GradeText::s_Conclusion]->SetPosition(vec3(pos.x + 130.f, pos.y - 200.f, pos.z + 1));

		m_GSM->GetGameData()->player_Active = false;
		m_GSM->GetGameData()->player->GetComponent<RigidBody>(CT_RIGIDBODY)->ClearVelocity();
    }

}

/******************************************************************************/
/*!
\brief - Shutdown Grade info
*/
/******************************************************************************/
void Grade::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload Grade info
*/
/******************************************************************************/
void Grade::Unload(void)
{

}
