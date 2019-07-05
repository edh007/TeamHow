/******************************************************************************/
/*!
\file   OuterWall.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/03/28(yy/mm/dd)

\description
Contains OuterWall logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "OuterWall.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - OuterWallBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* OuterWallBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new OuterWall(Owner, key);
}

/******************************************************************************/
/*!
\brief - OuterWall constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
OuterWall::OuterWall(Object* Owner, LogicType key)
: GameLogic(Owner, key)
{}

/******************************************************************************/
/*!
\brief - Load OuterWall info
\param data - json parser
*/
/******************************************************************************/
void OuterWall::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize OuterWall info
*/
/******************************************************************************/
void OuterWall::Init(void)
{
	for (int i=0; i<4; i++)
	{
		walls[i] = new Object(AT_NONE, m_OBM);
		walls[i]->AddComponent(ComponentFactory::CreateComponent(walls[i], CT_TRANSFORM));
		walls[i]->AddComponent(ComponentFactory::CreateComponent(walls[i], CT_SPRITE));
		walls[i]->AddComponent(ComponentFactory::CreateComponent(walls[i], CT_RIGIDBODY));

		m_trs = walls[i]->GetComponent<Transform>(CT_TRANSFORM);
		m_spr = walls[i]->GetComponent<Sprite>(CT_SPRITE);
		m_rid = walls[i]->GetComponent<RigidBody>(CT_RIGIDBODY);

		m_spr->SetTexture(m_OBM->GetTexture("Wall"));
		m_spr->SetColor(vec4(1.f, 1.f, 1.f, 1.f));

		m_rid->ActivateMove(false);

		switch (i)
		{
			// LEFT
		case 0:
			m_trs->SetScale(vec3(16, 768, 0));
			m_trs->SetPosition(vec3(-520,0,0));
			break;
			// RIGHT
		case 1:
			m_trs->SetScale(vec3(16, 768, 0));
			m_trs->SetPosition(vec3(520,0,0));
			break;
			// TOP
		case 2:
			m_trs->SetScale(vec3(1024, 16, 0));
			m_trs->SetPosition(vec3(0,392,0));
			break;
			// DOWN
		case 3:
			m_trs->SetScale(vec3(1024, 16, 0));
			m_trs->SetPosition(vec3(0,-392,0));
			break;
		}

		m_OBM->AddObject(walls[i]);
	}
}

/******************************************************************************/
/*!
\brief - Update OuterWall info
\param dt - delta time
*/
/******************************************************************************/
void OuterWall::Update(float /*dt*/)
{

}

/******************************************************************************/
/*!
\brief - Shutdown OuterWall info
*/
/******************************************************************************/
void OuterWall::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload OuterWall info
*/
/******************************************************************************/
void OuterWall::Unload(void)
{

}
