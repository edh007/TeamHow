/******************************************************************************/
/*!
\file   Bullet.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/11/12(yy/mm/dd)

\description
Contains Bullet logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Bullet.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - BulletBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* BulletBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Bullet(Owner, key);
}

/******************************************************************************/
/*!
\brief - Bullet constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Bullet::Bullet(Object* Owner, LogicType key)
: GameLogic(Owner, key), m_body(0), m_OwnerId(0)
{}

/******************************************************************************/
/*!
\brief - Load Bullet info
\param data - json parser
*/
/******************************************************************************/
void Bullet::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize Bullet info
*/
/******************************************************************************/
void Bullet::Init(void)
{
	std::vector<Object*> punch;
	m_OBM->GetObjects(AT_PUNCH, punch);
	if (punch.size())
		punch_id = punch[0]->GetID();

	m_body = m_Owner->GetComponent<RigidBody>(CT_RIGIDBODY);
	m_res.x = static_cast<float>(m_GSM->GetResolution().width);
	m_res.y = static_cast<float>(m_GSM->GetResolution().height);
}

/******************************************************************************/
/*!
\brief - Update Bullet info
\param dt - delta time
*/
/******************************************************************************/
void Bullet::Update(float /*dt*/)
{
	// If bullet got collided,
	if (m_body->IsCollided())
	{
		//// Remove other enemy
		//std::vector<Object*> enemyList;
		//m_OBM->GetObjects(ENEMY, enemyList);

		//for (auto it : enemyList) {
		//	// If there was a collision between enemy and bullet
		//	if (it->GetComponent<RigidBody>(CT_RIGIDBODY)->IsCollidedWith(m_OwnerID)) {
		//		// Remove enemy 
		//		m_OBM->RemoveObject(it->GetID());
		//		break;
		//	}
		//}

		// Remove bullet here
		if (!m_body->IsCollidedWith(punch_id) &&
			!m_body->IsCollidedWith(m_OwnerId))
			RemoveOwner(true);
	}

	// Pre calculate for screen size
	vec3 view = m_OBM->GetGameScene()->GetCameraPos() * .5f + m_res;
	vec3 position = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();

	// If the bullet is outside sceren,
	// destroy this.
	if (position.x > view.x ||
		position.x < -view.x ||
		position.y < -view.y ||
		position.y > view.y)
		RemoveOwner(true);
}

/******************************************************************************/
/*!
\brief - Shutdown Bullet info
*/
/******************************************************************************/
void Bullet::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload Bullet info
*/
/******************************************************************************/
void Bullet::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Set Id
\param id
*/
/******************************************************************************/
void Bullet::SetId(int id)
{
	m_OwnerId = id;
}
