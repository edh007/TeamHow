/******************************************************************************/
/*!
\file   Arrow.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/03/06(yy/mm/dd)

\description
Contains Arrow logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Arrow.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - ArrowBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* ArrowBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Arrow(Owner, key);
}

/******************************************************************************/
/*!
\brief - Arrow constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Arrow::Arrow(Object* Owner, LogicType key)
: GameLogic(Owner, key)
{}

/******************************************************************************/
/*!
\brief - Load Arrow info
\param data - json parser
*/
/******************************************************************************/
void Arrow::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize Arrow info
*/
/******************************************************************************/
void Arrow::Init(void)
{
	m_Object = new Object(AT_NONE, m_OBM);
	m_Object->AddComponent(ComponentFactory::CreateComponent(m_Object, CT_TRANSFORM));
	m_Object->AddComponent(ComponentFactory::CreateComponent(m_Object, CT_SPRITE));
	m_Sprite = m_Object->GetComponent<Sprite>(CT_SPRITE);
	m_Trs = m_Object->GetComponent<Transform>(CT_TRANSFORM);

	m_Sprite->SetTexture(m_OBM->GetTexture("Arrow"));
	vec3 tmp = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
	m_Trs->SetPosition(vec3(tmp.x, tmp.y + 50, tmp.z));
	m_Trs->SetScale(vec3(50,50,0));
	
	m_OBM->AddObject(m_Object);
	toggle = true;
}

/******************************************************************************/
/*!
\brief - Update Arrow info
\param dt - delta time
*/
/******************************************************************************/
void Arrow::Update(float dt)
{
	if (toggle == true)
	{
		m_time += dt;
		// TODO:
		//std::cout << m_time << std::endl;
		vec3 tmp = m_Trs->GetPosition();
		if (m_time < 2.f)
			m_Trs->SetPosition(vec3(tmp.x, tmp.y + 0.2f, 15.f));
		else if (m_time < 4.f)
			m_Trs->SetPosition(vec3(tmp.x, tmp.y - 0.2f, 15.f));
		else
		{
			vec3 t = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
			m_Trs->SetPosition(vec3(t.x, t.y + 50, 1.f));
			m_time = 0.f;
		}
	}
	else
		m_Trs->SetPosition(vec3(2000.f, 0.f, 0.f));
}

/******************************************************************************/
/*!
\brief - Shutdown Arrow info
*/
/******************************************************************************/
void Arrow::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload Arrow info
*/
/******************************************************************************/
void Arrow::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - get toggle of arrow
\return toggle - return value
*/
/******************************************************************************/
bool Arrow::GetToggle(void)
{
	return toggle;
}

/******************************************************************************/
/*!
\brief - set toggle of arrow
\param tog - set value
*/
/******************************************************************************/
void Arrow::SetToggle(bool tog)
{
	toggle = tog;
}