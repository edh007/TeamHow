/******************************************************************************/
/*!
\file   Fov.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/04/06(yy/mm/dd)

\description
Contains Fov logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Fov.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - FovBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* FovBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Fov(Owner, key);
}

/******************************************************************************/
/*!
\brief - Fov constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Fov::Fov(Object* Owner, LogicType key)
: GameLogic(Owner, key)
{}

/******************************************************************************/
/*!
\brief - Load Fov info
\param data - json parser
*/
/******************************************************************************/
void Fov::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize Fov info
*/
/******************************************************************************/
void Fov::Init(void)
{
	m_object = new Object(AT_NONE, m_OBM);

	m_object->AddComponent(ComponentFactory::CreateComponent(m_object, CT_TRANSFORM));
	m_object->AddComponent(ComponentFactory::CreateComponent(m_object, CT_SPRITE));

	m_trs = m_object->GetComponent<Transform>(CT_TRANSFORM);
	m_sprite = m_object->GetComponent<Sprite>(CT_SPRITE);

	m_trs->SetScale(vec3(1440, 1080, 0));
	vec3 tmp = m_GSM->GetGameData()->cameraPos;
	m_trs->SetPosition(vec3(tmp.x, tmp.y, 8.f));

	m_sprite->SetTexture(m_GSM->GetGLManager()->GetTexture("Player_Fov"));

	m_OBM->AddObject(m_object);

	m_GSM->GetGameData()->realViewSight = 350.f;
}

/******************************************************************************/
/*!
\brief - Update Fov info
\param dt - delta time
*/
/******************************************************************************/
void Fov::Update(float /*dt*/)
{
	vec3 tmp = m_GSM->GetGameData()->cameraPos;
	m_trs->SetPosition(vec3(tmp.x, tmp.y, 8.f));
}

/******************************************************************************/
/*!
\brief - Shutdown Fov info
*/
/******************************************************************************/
void Fov::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload Fov info
*/
/******************************************************************************/
void Fov::Unload(void)
{

}
