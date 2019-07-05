/******************************************************************************/
/*!
\file   RigidBody.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains RigidBody's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include <unordered_map>
#include "../../../Component/Component.h"
#include "../../../Utilities/Math/MathUtils.h"
#include "../../../Component/ComponentBuilder.h"

class World;
class Object;
class Transform;
typedef std::unordered_map<int, bool> CollisionMap;

//! Rigidbody' shape
enum Shape { BALL, BOX };

//! Tranform builder class
class RigidBodyBuilder : public ComponentBuilder
{
public:
	RigidBodyBuilder() {};
	virtual ~RigidBodyBuilder() {};
	virtual Component* BuildComponent(Object* Owner, ComponentType key) const;

};

//! For Rectangle sprites
class Vertices{

public:

	//! Vertices constructor, destructor, operator
	Vertices(){ vertice[0] = vertice[1] = vertice[2] = vertice[3] = vec3(); }
	~Vertices(){};
	vec3& operator[](const int index){ return vertice[index]; }

private:
	// Four vectices (RECT)
	vec3 vertice[4];
};

//! For Rectangle sprites
class Edges{

public:

	//! Vertices constructor, destructor, operator
	Edges(){ edges[0] = edges[1] = edges[2] = edges[3] = vec3(); }
	~Edges(){};
	vec3& operator[](const int index){ return edges[index]; }

private:
	// Four vectices (RECT)
	vec3 edges[4];
};

//! class RigidBody
class RigidBody : public Component
{
public:

	friend class World;

	RigidBody(Object* Owner = 0, ComponentType key = CT_RIGIDBODY);
	virtual ~RigidBody() {};

	//Manage Body' scale 
	void SetScale(const vec3& scale);
	vec3 GetScale(void) const;

	//Manager body's physics info
	void SetSpeed(float speed);
	float GetSpeed(void) const;

	void SetDirectionVector(const vec3& velocity);
	vec3 GetDirectionVector(void) const;

	void SetVelocity(const vec3& velocity);
	vec3 GetVelocity(void) const;
	void ClearVelocity(void);

	void SetAcceleration(float acceleration);
	float GetAcceleration(void) const;

	// Body's shape type
	void SetShape(Shape type);
	Shape GetShape(void) const;

	void SetMass(float mass);
	float GetMass(void) const;

	//Manage Body's status
	void ActivateMove(bool move);
	bool GetMoveToggle(void) const;

	void ActivateCollider(bool active);
	bool GetColliderToggle(void) const;

	void ActivateResponse(bool response);
	bool GetResponseToggle(void) const;

	void  SetFriction(float friction);
	float GetFriction(void) const;

	// Manage Collision partner
	bool IsCollided(void) const;
	bool IsCollidedWith(int sprite_id);
	
	bool GetScaleToggle(void) const;
	void SetScaleToggle(bool toggle);

	// Get vertices and edges, transform info
	Vertices GetVertices(void);
	Edges GetEdges(void);
	Transform* GetTransform(void);

	//Manage Body's direction to move
	float GetDirectionAngle(void) const;

	CollisionMap& GetCollisionMap(void);

private:

	//Manage Body's direction to move
	void SetDirectionAngle(float m_direction);

	//! Motion float info
	float m_mass;
	float m_direction;
	float m_acceleration;
	float m_friction;
	float m_speed;

	//! Motion vector Info
	vec3 m_scale;
	vec3 m_dirVector;

	//! Collision info
	bool m_response;
	bool m_collider;
	bool m_move;
	bool m_isCollided;
	bool m_sameScl;
	Object* m_with;
	Edges m_edges;
	Vertices m_verts;

	CollisionMap m_collidedList;

	Shape m_shape;			//! Body's shape(Ball or box)
};

#endif // _RIGIDBODY_H_