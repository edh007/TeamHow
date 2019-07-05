/******************************************************************************/
/*!
\file   Tutorial.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/03/06(yy/mm/dd)

\description
Contains Tutorial logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Tutorial.h"
#include "../../../BaseData/BaseEnigne.h"
#include "../Menus/MenuSelect.h"

/******************************************************************************/
/*!
\brief - TutorialBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* TutorialBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Tutorial(Owner, key);
}

/******************************************************************************/
/*!
\brief - Tutorial constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Tutorial::Tutorial(Object* Owner, LogicType key)
: GameLogic(Owner, key)
{}

/******************************************************************************/
/*!
\brief - Load Tutorial info
\param data - json parser
*/
/******************************************************************************/
void Tutorial::Load(const Json::Value& data)
{
// Set these info only for this case
	if (data.isMember("Message") &&
		data["Message"].isArray() &&
		data["Message"][0].isArray() &&
		data["Message"][0][0].isString() &&
		data["Message"][0][1].isArray())
	{
		for (unsigned i = 0; i < data["Message"].size(); ++i)
		{
			Messages *temp = new Messages();
			temp->m_texts = data["Message"][i][0].asCString();
			temp->m_pos.x = data["Message"][i][1][0].asFloat();
			temp->m_pos.y = data["Message"][i][1][1].asFloat();

			if (data["Message"][i][2].isString())
			{
				temp->textureName = data["Message"][i][2].asCString();
				temp->imageToggle = true;
				temp->seenOnceToggle = true;
			}
			else
			{
				temp->textureName = "";
				temp->imageToggle = false;
				temp->seenOnceToggle = false;
			}

            if(data["Message"][i][3].isBool() == true)
                temp->seenOnceToggle = data["Message"][i][1][2].asBool();

			messageList.push_back(temp);
		}
	}
}

/******************************************************************************/
/*!
\brief - Initialize Tutorial info
*/
/******************************************************************************/
void Tutorial::Init(void)
{
	m_Object = new Object(AT_NONE, m_OBM);
	m_Object->AddComponent(ComponentFactory::CreateComponent(m_Object, CT_TRANSFORM));
	m_Object->AddComponent(ComponentFactory::CreateComponent(m_Object, CT_TEXT));

    m_Text = m_Object->GetComponent<Text>(CT_TEXT);
	m_Trs = m_Object->GetComponent<Transform>(CT_TRANSFORM);

	m_Trs->SetPosition(vec3(1000, 1000, 0));
	m_Trs->SetScale(vec3(1, 1, 0));

    m_Text->SetColor(vec4(1.f, 1.f, 1.f, 1.f));
	m_OBM->AddObject(m_Object);

	m_Image = new Object(AT_NONE, m_OBM);
	m_Image->AddComponent(ComponentFactory::CreateComponent(m_Image, CT_TRANSFORM));
	m_Image->AddComponent(ComponentFactory::CreateComponent(m_Image, CT_SPRITE));
	m_ImageSprite = m_Image->GetComponent<Sprite>(CT_SPRITE);
	m_ImageTrs = m_Image->GetComponent<Transform>(CT_TRANSFORM);

	m_ImageTrs->SetPosition(vec3(1000, 1000, 0));
	m_ImageTrs->SetScale(vec3(250, 443, 0));

	m_ImageSprite->SetTexture(m_OBM->GetTexture("Black"));
	m_ImageSprite->SetColor(vec4(1.f, 1.0f, 1.f, 0.8f));
	m_OBM->AddObject(m_Image);

	dtStack = 0.f;

    m_Skip = new Object(AT_NONE, m_OBM);
    m_Skip->AddComponent(ComponentFactory::CreateComponent(m_Skip, CT_TRANSFORM));
    m_Skip->AddComponent(ComponentFactory::CreateComponent(m_Skip, CT_TEXT));

    m_SkipText = m_Skip->GetComponent<Text>(CT_TEXT);
    m_SkipTrs = m_Skip->GetComponent<Transform>(CT_TRANSFORM);

    m_SkipTrs->SetPosition(vec3(1000, 1000, 0));
    m_SkipTrs->SetScale(vec3(1, 1, 0));

    m_SkipText->SetFontSize(30);
    m_SkipText->SetColor(vec4(1.f, 1.f, 1.f, 1.f));
    m_OBM->AddObject(m_Skip);


	m_ObjectLT = new Object(AT_NONE, m_OBM);
	m_ObjectLT->AddComponent(ComponentFactory::CreateComponent(m_ObjectLT, CT_TRANSFORM));
	m_ObjectLT->AddComponent(ComponentFactory::CreateComponent(m_ObjectLT, CT_TEXT));

	m_TextLT = m_ObjectLT->GetComponent<Text>(CT_TEXT);
	m_TrsLT = m_ObjectLT->GetComponent<Transform>(CT_TRANSFORM);

	m_TrsLT->SetPosition(vec3(1000, 1000, 0));
	m_TrsLT->SetScale(vec3(1, 1, 0));

	m_TextLT->SetFontSize(100);
	m_TextLT->SetColor(vec4(1.f, 1.f, 1.f, 1.f));
	m_OBM->AddObject(m_ObjectLT);


	m_ImageArrow = new Object(AT_NONE, m_OBM);
	m_ImageArrow->AddComponent(ComponentFactory::CreateComponent(m_ImageArrow, CT_TRANSFORM));
	m_ImageArrow->AddComponent(ComponentFactory::CreateComponent(m_ImageArrow, CT_SPRITE));
	m_ImageArSprite = m_ImageArrow->GetComponent<Sprite>(CT_SPRITE);
	m_ImageArTrs = m_ImageArrow->GetComponent<Transform>(CT_TRANSFORM);

	m_ImageArTrs->SetPosition(vec3(1000, 1000, 0));
	m_ImageArTrs->SetScale(vec3(230, 134, 0));

	m_ImageArSprite->SetTexture(m_OBM->GetTexture("UI_Arrow"));
	m_ImageArSprite->SetColor(vec4(1.f, 1.0f, 1.f, 0.8f));
	m_OBM->AddObject(m_ImageArrow);
	dtArrow = 0.f;
	arrow = false;
	seenOnce = false;
	sprPunch = false;
}

/******************************************************************************/
/*!
\brief - Update Tutorial info
\param dt - delta time
*/
/******************************************************************************/
void Tutorial::Update(float dt)
{
	vec3 temp = m_GSM->GetGameData()->cameraPos;
	
	if (!m_GSM->GetGameData()->searchToggle
		&& !m_GSM->GetGameData()->tmToggle
		&& m_GSM->GetGameData()->clicked
		&& seenOnce == false)
		sprPunch = true;
	else
		sprPunch = false;
	
	
	if (arrow == true)
	{
		//dtArrow += dt;
		//if (dtArrow > 0.1f)
		//{
			dtArrow = 0.f;
			arrow = false;
			m_ImageArTrs->SetPosition(vec3(1000, 1000, 16.f));
			m_ImageArSprite->SetColor(vec4(1.f, 1.0f, 1.f, 0.f));
		//}
	}
	for (auto it = messageList.begin(); it != messageList.end(); ++it)
	{
		if (Math::Distance_pt(temp, (*it)->m_pos) < 100.f && sprPunch == false)
		{ 
			if ((*it)->imageToggle == true)
			{
				std::string tmpStr = (*it)->textureName;
				if (tmpStr.size() != 0)
				{
					m_ImageSprite->SetTexture(m_OBM->GetTexture(tmpStr.c_str()));
					m_ImageTrs->SetPosition(vec3(temp.x - 350.f, temp.y - 150.f, 16.f));
					m_ImageSprite->SetColor(vec4(1.f, 1.0f, 1.f, 0.8f));

                    if (tmpStr == "Manipulation_8")
                    {
                        m_ImageTrs->SetPosition(vec3(temp.x, temp.y, 16.f));
                        m_ImageSprite->SetColor(vec4(1.f, 1.0f, 1.f, 0.5f));
                        m_ImageTrs->SetScale(vec3(621, 468, 0));
                    }
                    else if (tmpStr == "Manipulation_9")
                    {
                        m_ImageTrs->SetPosition(vec3(temp.x, temp.y, 16.f));
                        m_ImageSprite->SetColor(vec4(1.f, 1.0f, 1.f, 0.5f));
                        m_ImageTrs->SetScale(vec3(621, 468, 0));
                    }
					else if (tmpStr == "Manipulation_3" && (*it)->seenOnceToggle == true)
					{
						m_ImageArTrs->SetPosition(vec3(temp.x - 232.f, temp.y + 200.f, 17.f));
						m_ImageArSprite->SetColor(vec4(1.f, 1.0f, 1.f, 1.f));
						arrow = true;
					}
					else if (tmpStr == "Manipulation_4" && (*it)->seenOnceToggle == true)
					{
						m_ImageArTrs->SetPosition(vec3(temp.x - 232.f, temp.y + 200.f, 17.f));
						m_ImageArSprite->SetColor(vec4(1.f, 1.0f, 1.f, 1.f)); 
						arrow = true;
					}
					else if (tmpStr == "Manipulation_6" && (*it)->seenOnceToggle == true)
					{
						m_ImageArTrs->SetPosition(vec3(temp.x - 232.f, temp.y + 200.f, 17.f));
						m_ImageArSprite->SetColor(vec4(1.f, 1.0f, 1.f, 1.f));
						arrow = true;
					}
					else if (tmpStr == "Manipulation_7" && (*it)->seenOnceToggle == true)
					{
						m_ImageArTrs->SetPosition(vec3(temp.x - 232.f, temp.y + 200.f, 17.f));
						m_ImageArSprite->SetColor(vec4(1.f, 1.0f, 1.f, 1.f));
						arrow = true;
					}
					else
						m_ImageTrs->SetScale(vec3(250, 443, 0));

					if ((*it)->seenOnceToggle == true)
					{
                        m_SkipText->SetText("Press BackSpace/Left Click/BACK to SKIP!");
                        m_SkipTrs->SetPosition(vec3(temp.x - 250.f, temp.y - 300.f, 17.f));

						seenOnce = true;
						m_TextLT->SetText("%d", int(4.f - dtStack));
						m_TrsLT->SetPosition(vec3(temp.x + 400.f, temp.y - 350.f, 17.f));
						m_ImageTrs->SetPosition(vec3(temp.x, temp.y, 16.f));
                        m_ImageSprite->SetColor(vec4(1.f, 1.0f, 1.f, 1.0f));
						dtStack += dt;
						m_GSM->GetGameData()->player_Active = false;
						m_GSM->GetGameData()->player->GetComponent<RigidBody>(CT_RIGIDBODY)->ClearVelocity();

                        bool xInput = XboxInput::Instance()->IsConnected();
						if (dtStack > 3.f || InputManager::GetInstance().KeyTriggered(KEY_BACK)
							|| InputManager::GetInstance().KeyTriggered(MOUSE_LEFT) ||
							(xInput && XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->BACK)))
						{
                            m_SkipText->SetText("");
                            m_SkipTrs->SetPosition(vec3(1000.f, 1000.f, 0.f));

							seenOnce = false;
							dtStack = 0.f;
							(*it)->seenOnceToggle = false;
							m_TextLT->SetText("");
							m_TrsLT->SetPosition(vec3(1000, 1000, 0));
						}
					}
					else
						m_GSM->GetGameData()->player_Active = true;
				}
			}

            m_Text->SetText((*it)->m_texts.c_str());
			m_Trs->SetPosition(vec3(temp.x-450.f, temp.y - 350.f, 17.f));
			break;
		}
		else
		{
			if ((*it)->seenOnceToggle == true)
			{
				dtStack = 0.f;
				m_TextLT->SetText("");
				m_TrsLT->SetPosition(vec3(1000, 1000, 0));
				m_GSM->GetGameData()->player_Active = true;
			}
			if ((*it)->imageToggle == true)
			{
				std::string tmpStr = (*it)->textureName;
				if (tmpStr.size() != 0)
				{
					m_ImageSprite->SetTexture(m_OBM->GetTexture(tmpStr.c_str()));
					m_ImageSprite->SetColor(vec4(0.f,0.f,0.f,0.f));
				}
			}

            m_Text->SetText("");
		}

	}
}

/******************************************************************************/
/*!
\brief - Shutdown Tutorial info
*/
/******************************************************************************/
void Tutorial::Shutdown(void)
{
	for (auto it = messageList.begin(); it != messageList.end(); )
		delete (*it++);
	messageList.clear();
}

/******************************************************************************/
/*!
\brief - Unload Tutorial info
*/
/******************************************************************************/
void Tutorial::Unload(void)
{

}