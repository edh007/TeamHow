/******************************************************************************/
/*!
\file   RigidBody.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains RigidBody's class member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "RigidBody.h"
#include "../Transform/Transform.h"
#include "../../../ObjectManager/Object/Object.h"
#include "../../../Component/ComponentFactory/ComponentFactory.h"

/******************************************************************************/
/*!
\brief - RigidBodyBuilder constructor
\param Owner - Owner of this Component
\param key - ComponentType
\return new RigidBody
*/
/******************************************************************************/
Component* RigidBodyBuilder::BuildComponent(Object* Owner, ComponentType key) const {
	return new RigidBody(Owner, key);
};

/******************************************************************************/
/*!
\brief - RigidBody Constructor
*/
/******************************************************************************/
RigidBody::RigidBody(Object* Owner, ComponentType key)
: Component(Owner, key),
m_shape(BOX), m_mass(1.f), m_with(0), m_sameScl(true),
m_dirVector(vec3()), m_verts(Vertices()), m_edges(Edges()),
m_move(true), m_collider(true), m_isCollided(false), m_response(true),
m_direction(0), m_scale(0), m_acceleration(0), m_friction(0), m_speed(0.f)
{
	// Preset transform
	if (!m_Owner->HasComponent(CT_TRANSFORM))
		m_Owner->AddComponent(ComponentFactory::CreateComponent(m_Owner, CT_TRANSFORM));

	// Set body scale
	m_scale = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetScale();
}

/******************************************************************************/
/*!
\brief - Activate to move
\param move 
*/
/******************************************************************************/
void RigidBody::ActivateMove(bool move)
{
	m_move = move;
}

/******************************************************************************/
/*!
\brief - Get Move Toggle
\return m_move
*/
/******************************************************************************/
bool RigidBody::GetMoveToggle(void) const
{
	return m_move;
}

/******************************************************************************/
/*!
\brief - Set body's collision toggle
\param active
*/
/******************************************************************************/
void RigidBody::ActivateCollider(bool active)
{
	m_collider = active;
}

/******************************************************************************/
/*!
\brief - Get Collider Toggle
\return m_collider
*/
/******************************************************************************/
bool RigidBody::GetColliderToggle(void) const
{
	return m_collider;
}

/******************************************************************************/
/*!
\brief - Set body's acceleration
\param acceleration
*/
/******************************************************************************/
void RigidBody::SetAcceleration(float acceleration)
{
	m_acceleration = acceleration;
}

/******************************************************************************/
/*!
\brief - Get Acceleration
\return m_acceleration
*/
/******************************************************************************/
float RigidBody::GetAcceleration(void) const
{
	return m_acceleration;
}

/******************************************************************************/
/*!
\brief - Set body's speed
\param speed
*/
/******************************************************************************/
void RigidBody::SetSpeed(float speed)
{
	m_speed = speed;
}

/******************************************************************************/
/*!
\brief - Get speed
\return m_speed
*/
/******************************************************************************/
float RigidBody::GetSpeed(void) const
{
	return m_speed;
}

/******************************************************************************/
/*!
\brief - Set body's Direction Vector
\param vector
*/
/******************************************************************************/
void RigidBody::SetDirectionVector(const vec3 & vector)
{
	m_dirVector = vector;
	m_dirVector = m_dirVector.Normalize();
	m_direction = Math::RadToDeg(atan2(m_dirVector.y, m_dirVector.x));
}

/******************************************************************************/
/*!
\brief - Get Direction Vector
\return m_dirVector
*/
/******************************************************************************/
vec3 RigidBody::GetDirectionVector(void) const
{
	return m_dirVector;
}

/******************************************************************************/
/*!
\brief - Set body's velocity
\param velocity
*/
/******************************************************************************/
void RigidBody::SetVelocity(const vec3& velocity)
{
	m_speed = velocity.Length();
	m_dirVector = velocity;
	m_dirVector = m_dirVector.Normalize();
	m_direction = Math::RadToDeg(atan2(m_dirVector.y, m_dirVector.x));
}

/******************************************************************************/
/*!
\brief - Get Velocity
\return m_speed * m_dirVecto
*/
/******************************************************************************/
vec3 RigidBody::GetVelocity(void) const
{
	return m_speed * m_dirVector;
}

/******************************************************************************/
/*!
\brief - Clear all velocity and speed from body
*/
/******************************************************************************/
void RigidBody::ClearVelocity(void)
{
	m_speed = 0.f;
	m_acceleration = 0.f;
}

/******************************************************************************/
/*!
\brief - Set body's scale (! Not sprite's scale !)
\param scale
*/
/******************************************************************************/
void RigidBody::SetScale(const vec3& scale)
{
	m_scale = scale;
}

/******************************************************************************/
/*!
\brief - Get body's scale (! Not sprite's scale !)
\return m_velocity
*/
/******************************************************************************/
vec3 RigidBody::GetScale(void) const
{
	return m_scale;
}

/******************************************************************************/
/*!
\brief - Set direction
\param direction
*/
/******************************************************************************/
void RigidBody::SetDirectionAngle(float direction)
{
	m_direction = direction;
	if (m_direction > 360) m_direction -= 360.f;
	else if (m_direction < 0) m_direction = 360.f + m_direction;
}

/******************************************************************************/
/*!
\brief - Get Direction Angle
\return m_direction
*/
/******************************************************************************/
float RigidBody::GetDirectionAngle(void) const
{
	return m_direction;
}

/******************************************************************************/
/*!
\brief - Check if body got either collided or not
\return m_isCollided
*/
/******************************************************************************/
bool RigidBody::IsCollided(void) const
{
	for (auto it = m_collidedList.begin();
		it != m_collidedList.end(); ++it)
		if (it->second) return true;

	return false;
}

/******************************************************************************/
/*!
\brief - Set friction
\param friction
*/
/******************************************************************************/
void RigidBody::SetFriction(float friction)
{
	m_friction = friction;
}

/******************************************************************************/
/*!
\brief - Get friction
\return m_friction
*/
/******************************************************************************/
float RigidBody::GetFriction(void) const
{
	return m_friction;
}

/******************************************************************************/
/*!
\brief - Set body's shape
\param shape - body's shape
*/
/******************************************************************************/
void RigidBody::SetShape(Shape shape)
{
	m_shape = shape;
}

/******************************************************************************/
/*!
\brief - Get body's shape
\return m_shape - body's shape
*/
/******************************************************************************/
Shape RigidBody::GetShape(void) const
{
	return m_shape;
}

/******************************************************************************/
/*!
\brief - Check if specific sprite's been collided to 
\param partner - opponent's address
\return bool
*/
/******************************************************************************/
bool RigidBody::IsCollidedWith(int sprite_id)
{
	// If input id and bdy's mother sprite's number is same,
	// return null
	if (sprite_id == m_Owner->GetID())
		return false;

	auto found = m_collidedList.find(sprite_id);

	if (found != m_collidedList.end())
		return found->second;

	return false;
}

/******************************************************************************/
/*!
\brief - Get m_sameScl toggle
\return m_sameScl
*/
/******************************************************************************/
bool RigidBody::GetScaleToggle(void) const
{
	return m_sameScl;
}

/******************************************************************************/
/*!
\brief - Set same transform's and body's scale
\param toggle
*/
/******************************************************************************/
void RigidBody::SetScaleToggle(bool toggle)
{
	m_sameScl = toggle;
}

/******************************************************************************/
/*!
\brief - Set body's mass
\param mass - body's mass
*/
/******************************************************************************/
void RigidBody::SetMass(float mass)
{
	if (mass <= 1.f)
		m_mass = 1.f;
	
	else
		m_mass = mass;
}

/******************************************************************************/
/*!
\brief - Get body's mass
\return m_mass - body's mass
*/
/******************************************************************************/
float RigidBody::GetMass(void) const
{
	return m_mass;
}

/******************************************************************************/
/*!
\brief - Get sprite's 4 vertices

    vert[1]     vert[2]
      *----------*
      |		     |
      |	  spt    |
	  |		     |
	  *----------*
	vert[0]     vert[3]

\return m_verts
*/
/******************************************************************************/
Vertices RigidBody::GetVertices(void)
{
	Transform* pTransform = m_Owner->GetComponent<Transform>(CT_TRANSFORM);

	if (m_shape == BOX)
	{
		// This scale is body's scale, not sprite's.
		m_verts[0] = vec3(pTransform->GetPosition().x - m_scale.x / 2, pTransform->GetPosition().y - m_scale.y / 2, pTransform->GetPosition().z);
		m_verts[1] = vec3(pTransform->GetPosition().x - m_scale.x / 2, pTransform->GetPosition().y + m_scale.y / 2, pTransform->GetPosition().z);
		m_verts[2] = vec3(pTransform->GetPosition().x + m_scale.x / 2, pTransform->GetPosition().y + m_scale.y / 2, pTransform->GetPosition().z);
		m_verts[3] = vec3(pTransform->GetPosition().x + m_scale.x / 2, pTransform->GetPosition().y - m_scale.y / 2, pTransform->GetPosition().z);

		//If sprite is rotated...
		if (pTransform->GetRotation())
		{
			m_verts[0] = m_verts[0].Rotation(pTransform->GetRotation(), pTransform->GetPosition());
			m_verts[1] = m_verts[1].Rotation(pTransform->GetRotation(), pTransform->GetPosition());
			m_verts[2] = m_verts[2].Rotation(pTransform->GetRotation(), pTransform->GetPosition());
			m_verts[3] = m_verts[3].Rotation(pTransform->GetRotation(), pTransform->GetPosition());
		}
	}

	return m_verts;
}

/******************************************************************************/
/*!
\brief - Get sprite's 4 edges

				edge[1]
			* ---------- *
			|			 |
	edge[0]	|	 spt	 |	edge[2]
			|			 |
			* ---------- *
				edge[3]


\return m_edges
*/
/******************************************************************************/
Edges RigidBody::GetEdges(void)
{
	if (m_shape == BOX)
	{
		// Init vertices
		GetVertices();

		//				edge[1]
		//			* ---------- *
		//			|			 |
		//	edge[0]	|	 spt	 |	edge[2]
		//			|			 |
		//			* ---------- *
		//				edge[3]

		// Set 4 edges
		m_edges[0] = m_verts[1] - m_verts[0];
		m_edges[1] = m_verts[2] - m_verts[1];
		m_edges[2] = m_verts[3] - m_verts[2];
		m_edges[3] = m_verts[0] - m_verts[3];
	}
	return m_edges;
}

/******************************************************************************/
/*!
\brief - Get transform from owner's transform component
\return pTransform
*/
/******************************************************************************/
Transform* RigidBody::GetTransform(void)
{
	return m_Owner->GetComponent<Transform>(CT_TRANSFORM);
}

/******************************************************************************/
/*!
\brief - Set body's response toggle
\param response
*/
/******************************************************************************/
void RigidBody::ActivateResponse(bool response)
{
	m_response = response;
}

/******************************************************************************/
/*!
\brief - Get body's response toggle
\return m_response
*/
/******************************************************************************/
bool RigidBody::GetResponseToggle(void) const
{
	return m_response;
}

/******************************************************************************/
/*!
\brief - Get list of collided sprites
\return m_collidedList
*/
/******************************************************************************/
CollisionMap& RigidBody::GetCollisionMap(void)
{
	return m_collidedList;
}