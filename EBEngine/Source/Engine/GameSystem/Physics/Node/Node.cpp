/******************************************************************************/
/*!
\file   Node.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2017/07/07(yy/mm/dd)

\description
Contains Node's class member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Node.h"
#include <algorithm>
#include "../../Graphic/Sprite/Sprite.h"
#include "../../Physics/Transform/Transform.h"
#include "../../../ObjectManager/Object/Object.h"
#include "../../../ObjectManager/ObjectManager.h"
#include "../../../Component/ComponentFactory/ComponentFactory.h"

/******************************************************************************/
/*!
\brief - Compares node's moving cost
\param lhs 
\param rhs 
*/
/******************************************************************************/
bool node_compare(Node* lhs, Node* rhs) {
	return lhs->cost < rhs->cost;
}

/******************************************************************************/
/*!
\brief - Node Constructor
\param OBM - OBM to manage the node
*/
/******************************************************************************/
Node::Node(ObjectManager* OBM)
	: m_OBM(OBM), m_toggle(true), m_position(vec3()), 
	m_prev(nullptr), m_index(Index())
{
	m_owner = new Object(AT_NODE, m_OBM);
	m_owner->AddComponent(ComponentFactory::CreateComponent(m_owner, CT_SPRITE));
	m_owner->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("circle"));
	m_owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1,1,1,0.5f));
	m_owner->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec2(50, 50));
	//m_owner->AddComponent(ComponentFactory::CreateComponent(m_owner, CT_TEXT));
	//m_owner->GetComponent<Text>(CT_TEXT)->SetColor(vec4(0,0,0,1));
	//m_owner->GetComponent<Text>(CT_TEXT)->SetFontSize(15.f);
	m_OBM->AddObject(m_owner);
}

/******************************************************************************/
/*!
\brief - Set node's index
\param index
*/
/******************************************************************************/
void Node::SetIndex(const Index & index)
{
	m_index = index;/*
	m_owner->GetComponent<Text>(CT_TEXT)->SetText("[%d, %d]", m_index.x, m_index.y);*/
}

/******************************************************************************/
/*!
\brief - Get node's index
\preturn m_index
*/
/******************************************************************************/
Index& Node::GetIndex(void) 
{
	return m_index;
}

/******************************************************************************/
/*!
\brief - Set node's rwal position
\param  position;
*/
/******************************************************************************/
void Node::SetPosition(const vec3 & position)
{
	m_position = position;
	m_position.z = -9.f;
	m_owner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(m_position);
}

/******************************************************************************/
/*!
\brief - Get node's rwal position
\return  m_position;
*/
/******************************************************************************/
vec3 & Node::GetPosition(void)
{
	return m_position;
}

/******************************************************************************/
/*!
\brief - Set node's open toggle
\param  m_toggle;
*/
/******************************************************************************/
void Node::SetToggle(bool toggle)
{
	if (toggle)
		m_owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 1, 1, 0.5f));

	else
		m_owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 0, 0, 0.5f));

	m_toggle = toggle;
}

/******************************************************************************/
/*!
\brief - Get node's open toggle
\return  m_toggle;
*/
/******************************************************************************/
bool Node::GetToggle(void) const
{
	return m_toggle;
}
