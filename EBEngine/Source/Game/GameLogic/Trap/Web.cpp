/******************************************************************************/
/*!
\file   Web.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/10/11(yy/mm/dd)

\description
Contains Web logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Web.h"
#include "../../../BaseData/BaseEnigne.h"
#include "../Enemy/Damage.h"

/******************************************************************************/
/*!
\brief - WebBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* WebBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Web(Owner, key);
}

/******************************************************************************/
/*!
\brief - Web constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Web::Web(Object* Owner, LogicType key)
: GameLogic(Owner, key), m_dnmt(0.f), m_vanish(false),
m_undone(true), m_size(150.f), m_scale(vec3()),
m_scaleSpeed(500.f)//, dt_Stack(0.f)
{}

/******************************************************************************/
/*!
\brief - Load Web info
\param data - json parser
*/
/******************************************************************************/
void Web::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize Web info
*/
/******************************************************************************/
void Web::Init(void)
{
	// Init body
	m_body = m_Owner->GetComponent<RigidBody>(CT_RIGIDBODY);
}

/******************************************************************************/
/*!
\brief - Update Web info
\param dt - delta time
*/
/******************************************************************************/
void Web::Update(float dt)
{
	m_color = m_Owner->GetComponent<Sprite>(CT_SPRITE)->GetColor();

	if (m_undone)
	{
		if (m_root)
		{
			// Increase the size of the web
			float calculated_dtspeed = dt *  m_dnmt;
			m_scale.x += calculated_dtspeed;
			m_scale.y += calculated_dtspeed;
			m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetScale(m_scale);

			// Until user set
			if (m_scale.x > m_size)
			{
				m_scale = vec3(m_size, m_size);
				m_root = false;
				m_Owner->GetComponent<RigidBody>(CT_RIGIDBODY)->SetScale(m_scale);
			}
		}

		else
		{
			// No more moves or size incresing
			m_Owner->GetComponent<RigidBody>(CT_RIGIDBODY)->ClearVelocity();
			m_scale = vec3(m_size, m_size);

			// No more check this out
			m_undone = false;
		}

		// Check size and moving web
		m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetScale(m_scale);
	}

	//dt_Stack += dt;

	// Start web to be vanished
	if (m_vanish)
	{
		m_color.w -= dt;
		
		if (m_color.w < 0.f)
			RemoveOwner(true);
	}

	// Lef web to be vanished
	else if (m_body->GetSpeed() <= 0.f)
			m_vanish = true;
	 
	m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(m_color);
}

/******************************************************************************/
/*!
\brief - Shutdown Web info
*/
/******************************************************************************/
void Web::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload Web info
*/
/******************************************************************************/
void Web::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Set root
\param from_spider
*/
/******************************************************************************/
void Web::SetRoot(bool from_spider)
{
	m_root = from_spider;
}

/******************************************************************************/
/*!
\brief -Set Denominator
\param dnmt
*/
/******************************************************************************/
void Web::SetDenominator(float dnmt)
{
	m_dnmt = dnmt;
}