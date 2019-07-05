/******************************************************************************/
/*!
\file   Lightning.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/04/05(yy/mm/dd)

\description
Contains Lightning logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Lightning.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - LightningBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* LightningBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Lightning(Owner, key);
}

/******************************************************************************/
/*!
\brief - Lightning constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Lightning::Lightning(Object* Owner, LogicType key)
: GameLogic(Owner, key)
{}

/******************************************************************************/
/*!
\brief - Load Lightning info
\param data - json parser
*/
/******************************************************************************/
void Lightning::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize Lightning info
*/
/******************************************************************************/
void Lightning::Init(void)
{
	m_object = new Object(AT_NONE, m_OBM);

	m_object->AddComponent(ComponentFactory::CreateComponent(m_object, CT_TRANSFORM));
	m_object->AddComponent(ComponentFactory::CreateComponent(m_object, CT_SPRITE));

	m_trs = m_object->GetComponent<Transform>(CT_TRANSFORM);
	m_sprite = m_object->GetComponent<Sprite>(CT_SPRITE);

	m_trs->SetScale(vec3(200, 1050, 0));
	m_trs->SetPosition(vec3(1000, 1000, 15));

	m_sprite->SetTexture(m_GSM->GetGLManager()->GetTexture("Lightning"));
	m_sprite->SetAnimation(true);
	m_sprite->SetFrame(5);
	m_sprite->SetFrameSpd(10);
	
	m_OBM->AddObject(m_object);

	m_Active = false;

}

/******************************************************************************/
/*!
\brief - Update Lightning info
\param dt - delta time
*/
/******************************************************************************/
void Lightning::Update(float /*dt*/)
{
	if (m_Active == true)
	{
		m_sprite->SetColor(vec4(1, 1, 1, 1));
		vec3 pos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
		//vec3 scl = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetScale();
		m_trs->SetPosition(vec3(pos.x, pos.y + (500), 15.f));

		
	}
	else
	{
		m_sprite->SetColor(vec4(0,0,0,0));
	}
}

/******************************************************************************/
/*!
\brief - Shutdown Lightning info
*/
/******************************************************************************/
void Lightning::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload Lightning info
*/
/******************************************************************************/
void Lightning::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - set the active as true or false
*/
/******************************************************************************/
void Lightning::SetActiveToggle(bool _gettor)
{
	m_Active = _gettor;
}

/******************************************************************************/
/*!
\brief - return active
*/
/******************************************************************************/
bool Lightning::GetActiveToggle(void)
{
	return m_Active;
}

/******************************************************************************/
/*!
\brief - set position
*/
/******************************************************************************/
void Lightning::SetPosition(vec3 _gettor)
{
	m_trs->SetPosition(_gettor);
}

/******************************************************************************/
/*!
\brief - get position
*/
/******************************************************************************/
vec3 Lightning::GetPosition(void)
{
	return m_trs->GetPosition();
}