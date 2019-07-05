/******************************************************************************/
/*!
\file   World.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains World's class member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "World.h"
#include <algorithm>
#include "../Node/Node.h"
#include "../Transform/Transform.h"
#include "../RigidBody/RigidBody.h"
#include "../../../ObjectManager/Object/Object.h"
#include "../../../StateManager/GameStateManager/GameStateManager.h"

/******************************************************************************/
/*!
\brief - World's costructor
*/
/******************************************************************************/
World::World(GameStateManager* GSM)
:mtd(vec3()), collided_edge(vec3()), m_Nodesize(0),
m_GSM(GSM), m_tailNode(nullptr), m_headNode(nullptr)
{
	new_speed[0] = new_speed[1] = 0.f;
}

/******************************************************************************/
/*!
\brief - World's destructor
*/
/******************************************************************************/
World::~World(void)
{}

/******************************************************************************/
/*!
\brief - World's init function
*/
/******************************************************************************/
void World::Init(void)
{
	//Nothing to init for now...
}

/******************************************************************************/
/*!
\brief - World's update function
*/
/******************************************************************************/
void World::Update(float dt)
{
	m_Nodesize = m_nodeList.size();

	// Works each bodies' physics
	for (auto it1 = m_bodyList.begin(); it1 != m_bodyList.end(); ++it1)
	{
		// Work basic motion
		BodyPipeline((*it1), dt);

		// If 2st sprite's colliders to be worked, check colliders
		if ((*it1)->GetColliderToggle())
		{
			// Set new begin
			auto new_begin = std::next(it1, 1);
			for (auto it2 = new_begin; it2 != m_bodyList.end(); ++it2)
			{
				// If both objs are different and have own body, 
				// check colliding and do response
				if (it1 != it2 && (*it2)->GetColliderToggle())
				{
					// Check the colliders and two bodies' collision status
					bool collisionIntersect = 
						CollisionIntersect((*it1), (*it2));
					if (collisionIntersect)
					{
						// Collision response
						if ((*it1)->GetResponseToggle() &&
							(*it2)->GetResponseToggle())
							CollisionResponse((*it1), (*it2));

						// Two bodies' been collided 
						CollisionRelation((*it1), (*it2), true);
					}

					// Two bodies' not been collided 
					else
						CollisionRelation((*it1), (*it2), false);
				}
			}
		}
	}
}

/******************************************************************************/
/*!
\brief - World's shutdown function
*/
/******************************************************************************/
void World::Shutdown(void)
{
	// Clear all sprites from the list to work
	m_bodyList.clear();
	ClearNodes();
}

/******************************************************************************/
/*!
\brief - World's Body Pipeline
\param spt - sprite to work
*/
/******************************************************************************/
void World::BodyPipeline(RigidBody* body, float dt)
{
	// Get pointer to transform
	Transform* transform = body->GetTransform();

	// Set body's scale
	if (body->GetScaleToggle())
		body->SetScale(transform->GetScale());

	if (body->GetMoveToggle())
	{
		// Get new dt
		float new_dt = dt * body->GetOwner()->GetdtOffset();

		// Get speed in advance
		float new_spd = body->GetSpeed();
		if (new_spd < 0.f)
			new_spd = 0.f;
		else
			body->SetSpeed(new_spd + (body->GetAcceleration() - body->GetFriction()) * new_dt);

		//Set directed angle 
		vec3 norm_velocity = body->GetDirectionVector();
		body->SetDirectionAngle(Math::RADIAN_DEGREE * atan2(norm_velocity.y, norm_velocity.x));

		//Update body's speed and velocity
		vec3 new_force = vec3(new_spd * cosf(Math::DegToRad(body->GetDirectionAngle())),
			new_spd * sinf(Math::DegToRad(body->GetDirectionAngle())), 0)
			*  (2.f / body->GetMass());

		//Update position by velocity and direction
		transform->SetPosition(vec3(
			transform->GetPosition().x + new_force.x * new_dt,
			transform->GetPosition().y + new_force.y * new_dt,
			transform->GetPosition().z));
	}
}

/******************************************************************************/
/*!
\brief - Do line projection and check if it is or not
\param axis - pointer to standard aixes
\param index - axis' index
\return bool
*/
/******************************************************************************/
bool World::AxisSeparatePolygons(vec3* axis, int& index, RigidBody* body1, RigidBody* body2)
{
	float min_a, max_a;
	float min_b, max_b;

	// Get intervals
	CalculateInterval(axis[index], body1, min_a, max_a);
	CalculateInterval(axis[index], body2, min_b, max_b);

	if (min_a > max_b || min_b > max_a)
		return true;

	// find the interval overlap
	float d0 = max_a - min_b;
	float d1 = max_b - min_a;
	float depth = d0 < d1 ? d0 : d1;

	// conver the separation axis into a push vector (re-normaliz
	// the axis and multiply by interval overlap)
	float axis_length_sqaured = axis[index].DotProduct(axis[index]);

	axis[index] *= depth / axis_length_sqaured;

	// Increase the index
	index++;
	return false;
}

/******************************************************************************/
/*!
\brief - Get mtd and collided segment of body
\param pushVector - pointer to axis vectors
\param iNumVectors - the number of total indexes
\return temp_mtd
*/
/******************************************************************************/
vec3 World::FindMTD(vec3* pushVector, int iNumVectors)
{
	// Init temp mtd 
	// and index of collided side
	vec3 temp_mtd = pushVector[0];
	int min_i = -1;
	float min_d2 = pushVector[0].DotProduct(pushVector[0]);

	// Get collided line
	for (int i = 1; i < iNumVectors; ++i)
	{
		float d2 = pushVector[i].DotProduct(pushVector[i]);
		if (d2 < min_d2)
		{
			// Get mtd and collided line's index
			min_i = i;
			min_d2 = d2;
			temp_mtd = pushVector[i];
		}
	}

	// If index has been found,
	// set it collided edge
	if (min_i != -1)
		collided_edge = pushVector[min_i];

	return temp_mtd;
}

/******************************************************************************/
/*!
\brief - Get interval between the segment and axis
\param axis - standard axis
\param body - sprite's body
\param min - minimumn float
\param max - maximum float
*/
/******************************************************************************/
void World::CalculateInterval(vec3& axis, RigidBody* body, float& min, float&max)
{
	// Get body's vertices
	Vertices verts = body->GetVertices();

	// Init 1st min and max
	min = max = axis.DotProduct(verts[0]);

	// Get min and max
	for (int i = 1; i < 4; ++i)
	{
		float d = axis.DotProduct(verts[i]);
		if (d < min) min = d;
		else if (d > max) max = d;
	}
}

/******************************************************************************/
/*!
\brief - Do Collision Intersect
\param body1
\param body2
\return bool
*/
/******************************************************************************/
bool World::CollisionIntersect(RigidBody* body1, RigidBody* body2)
{
	// Collision between 2 balls
	if (body1->GetShape() == Shape::BALL &&
		body2->GetShape() == Shape::BALL)
		return IntersectBallToBall(body1, body2);

	// Collision between 2 boxes
	else if (body1->GetShape() == Shape::BOX &&
		body2->GetShape() == Shape::BOX)
		return IntersectBoxToBox(body1, body2);

	// Collision between ball and box
	else
	{
		if (body1->GetShape() == Shape::BOX &&
			body2->GetShape() == Shape::BALL)
			return IntersectBoxToBall(body1, body2);

		else
			return IntersectBoxToBall(body2, body1);
	}
}

/******************************************************************************/
/*!
\brief - Do Collision Intersect between line and shape
\param body - body
\param start - starting point of line
\param end - ending point of line
\return bool
*/
/******************************************************************************/
bool World::CollisionIntersect(RigidBody * body, const vec3 & start, const vec3 & end)
{
	// If rigid body is rect shape
	if (body->GetShape() == BOX) {
		for (int i = 0; i < 4; ++i)
		{
			int j = i + 1;		// Current index and next index 
			if (i == 3) j = 0;	// When the index is 3, next index is 0

								// Check each vertice and segment
			if (Math::Intersect_Bool(
				body->GetVertices()[i], body->GetVertices()[j],
				start, end))
				return false;	// Cannot found that there is a player
		}

		return true;
	}

	// Todo: polish this code!!
	// Unless(circle)
	else {
		float r = body->GetTransform()->GetScale().x;		// Radius
		float m = (end.y - start.y) / (end.x - start.x);	// Slope
		float k = start.y - m * start.x;					// Constant
		float a = body->GetTransform()->GetPosition().x, b = body->GetTransform()->GetPosition().y;
		float A = m + 1, B = -2 *(a + m*k - m*b), C = pow(k-b, 2) + a*a - (r*r);
		float D = pow(B, 2) - 4*A*C;

		if (D > 0.f) return true;
		else {
			float minX = -(B+sqrt(D))*.5f *A, maxX = (sqrt(D) - B)*.5f *A;
			if (maxX >= start.x && minX <= end.x)
				return true;

			else return false;
		}
	}
}

/******************************************************************************/
/*!
\brief - Do Collision Intersect between 2 boxes
\param box1 - get 1st body's verts
\param box2 - get 2nd body's verts
\return bool
*/
/******************************************************************************/
bool World::IntersectBoxToBox(RigidBody* box1, RigidBody* box2)
{
	Transform* tsf1 = box1->GetTransform();
	Transform* tsf2 = box2->GetTransform();

	// Get bodies' edges
	Edges body1_edges = box1->GetEdges();
	Edges body2_edges = box2->GetEdges();

	// init helper variables
	vec3 vec_axis[8];
	int iNumAxis = 0;

	// Check overlapped for the 1st sprite
	for (int i = 0; i < 4; ++i)
	{
		vec_axis[iNumAxis] = vec3(-body1_edges[i].y, body1_edges[i].x);

		if (AxisSeparatePolygons(vec_axis, iNumAxis, box1, box2))
			return false;

	}

	// Check overlapped for the 2nd sprite
	for (int i = 0; i < 4; ++i)
	{
		vec_axis[iNumAxis] = vec3(-body2_edges[i].y, body2_edges[i].x);

		if (AxisSeparatePolygons(vec_axis, iNumAxis, box1, box2))
			return false;
	}

	//Find munumum transition distance
	mtd = FindMTD(vec_axis, iNumAxis);

	vec3 d = tsf1->GetPosition() - tsf2->GetPosition();

	// Reverse the mtd's sign
	if (d.DotProduct(mtd) < 0.f)
		mtd = -mtd;

	return true;
}

/******************************************************************************/
/*!
\brief - Do Collision Intersect between 2 balls
\param ball1 - get 1st body's radius(scale)
\param ball2 - get 2nd body's radius(scale)
\return bool
*/
/******************************************************************************/
bool World::IntersectBallToBall(RigidBody* ball1, RigidBody* ball2)
{
	Transform* tsf1 = ball1->GetTransform();
	Transform* tsf2 = ball2->GetTransform();

	// Get the distance of 2 circles' position and radius
	float distance = Math::Distance_pt(tsf1->GetPosition(), tsf2->GetPosition());
	float sum_radius = (ball1->GetScale().x + ball2->GetScale().x) / 2.f;

	// Check if they are overlapped or not
	if (distance < sum_radius)
		return true;
	
	return false;
}

/******************************************************************************/
/*!
\brief - Do Collision Intersect between box and ball
\param box - get 1st body's verts
\param ball - get 2nd body's radius(scale)
\return bool
*/
/******************************************************************************/
bool World::IntersectBoxToBall(RigidBody* box, RigidBody* ball)
{
	Transform* box_tsf = box->GetTransform();
	Transform* ball_tsf = ball->GetTransform();

	// Call this radius
	float radius = ball->GetScale().x / 2.f;

	vec3 relPos = ball_tsf->GetPosition() - box_tsf->GetPosition();
	float relDIs = sqrt(relPos.x * relPos.x + relPos.y * relPos.y);
	float relDeg = Math::DegToRad(box_tsf->GetRotation()) - atan2(relPos.y, relPos.x);

	vec3 new_xy = vec3(cosf(relDeg), sinf(relDeg)) * relDIs;
	vec3 halfSize = box->GetScale() / 2.f;

	if (new_xy.x >= -halfSize.x && new_xy.x <= halfSize.x &&
		new_xy.y >= -halfSize.y && new_xy.y <= halfSize.y)
		return true;

	// Init closest;
	vec3 closest;

	// Find the closest point in the X axis
	if (new_xy.x  < -halfSize.x)
		closest.x = -halfSize.x;
	else if (new_xy.x > halfSize.x)
		closest.x = halfSize.x;
	else
		closest.x = new_xy.x;

	// Find the closest point in the Y axis
	if (new_xy.y < -halfSize.y)
		closest.y = -halfSize.y;
	else if (new_xy.y > halfSize.y)
		closest.y = halfSize.y;
	else
		closest.y = new_xy.y;

	vec3 dt = new_xy - closest;
	float distance_sq = dt.DotProduct(dt);
	
	// Get mtd
	if (distance_sq <= radius * radius)
	{
		float dist = sqrt(distance_sq);
		if (dist < 0.0000001f) return false;

		mtd = dt * (radius - dist) / dist;

		if (relPos.DotProduct(mtd) < 0.f)
			mtd = -mtd;

		return true;
	}

	return false;

}

/******************************************************************************/
/*!
\brief - Do Collision Response
\param box1 - get 1st body's verts
\param box2 - get 2nd body's verts
*/
/******************************************************************************/
void World::CollisionResponse(RigidBody* box1, RigidBody* box2)
{	
	// Collision between 2 balls
	if (box1->GetShape() == Shape::BALL &&
		box2->GetShape() == Shape::BALL)
		ResponseBallToBall(box1, box2);

	// Collision between 2 boxes
	else if (box1->GetShape() == Shape::BOX &&
		box2->GetShape() == Shape::BOX)
		ResponseBoxToBox(box1, box2);

	// Collision between ball and box
	else
	{
		if (box1->GetShape() == Shape::BOX &&
			box2->GetShape() == Shape::BALL)
			ResponseBoxToBall(box1, box2);

		else
			ResponseBoxToBall(box2, box1);
	}

	// Refresh global minimum transition distance
	mtd = 0.f;
}

/******************************************************************************/
/*!
\brief - Do Collision Response between two balls
\param ball1 - set new body info
\param ball2 - set new body info
*/
/******************************************************************************/
void World::ResponseBallToBall(RigidBody* ball1, RigidBody* ball2)
{			
	Transform* tsf1 = ball1->GetTransform();
	Transform* tsf2 = ball2->GetTransform();

	// Subtract to balls position
	vec3 dt = tsf1->GetPosition() - tsf2->GetPosition();
	float d = dt.Length();

	// Get minumum transition distance
	mtd = dt * ((ball1->GetScale().x / 2.f + ball2->GetScale().x / 2.f) - d) / d;

	// Get reflection velocity
	float ball1_ci = ball1->GetDirectionVector().DotProduct(dt);
	float ball2_ci = ball2->GetDirectionVector().DotProduct(dt);

	// If 2nd ball is movable, refresh the 2nd ball's body info too
	if (ball1->GetMoveToggle() && ball2->GetMoveToggle())
	{
		// Move to the uncollided last position
		tsf1->SetPosition(tsf1->GetPosition() + .5f * mtd);
		tsf2->SetPosition(tsf2->GetPosition() - .5f * mtd);

		// Set new velocity
		ball1->SetDirectionVector(ball1->GetDirectionVector() +
			(ball2_ci - ball1_ci) * dt );

		ball2->SetDirectionVector(ball2->GetDirectionVector() +
			(ball1_ci - ball2_ci) * dt );

		// Save new speeds of two boxes
		new_speed[0] = ball1->GetSpeed() *
			(ball1->GetMass() /
			(ball2->GetMass() + ball1->GetMass()));

		new_speed[1] = ball2->GetSpeed() *
			(ball2->GetMass() /
			(ball2->GetMass() + ball1->GetMass()));

		// Reset the speed
		ball1->SetSpeed(new_speed[0] + new_speed[1] / ball2->GetMass());
		ball2->SetSpeed(new_speed[1] + new_speed[0] / ball1->GetMass());
	}

	else if (ball1->GetMoveToggle() && !ball2->GetMoveToggle())
	{
		// Move to the uncollided last position
		tsf1->SetPosition(tsf1->GetPosition() + mtd);

		// Set new velocity
		ball1->SetDirectionVector((ball1->GetDirectionVector() +
			(ball2_ci - ball1_ci) * dt / d));

		// Save new speeds of two boxes
		new_speed[0] = ball1->GetSpeed() *
			(ball1->GetMass() /
			(ball2->GetMass() + ball1->GetMass()));

		// Set new speed
		ball1->SetSpeed(new_speed[0] / ball2->GetMass());
	}

	else if (!ball1->GetMoveToggle() && ball2->GetMoveToggle())
	{
		// Move to the uncollided last position
		tsf2->SetPosition(tsf2->GetPosition() - mtd);

		// Set new velocity
		ball2->SetDirectionVector((ball1->GetDirectionVector() +
			(ball1_ci - ball2_ci) * dt / d));

		// Save new speeds of two boxes
		new_speed[1] = ball2->GetSpeed() *
			(ball2->GetMass() /
			(ball2->GetMass() + ball1->GetMass()));

		// Set new speed
		ball2->SetSpeed(new_speed[1] / ball1->GetMass());
	}
}

/******************************************************************************/
/*!
\brief - Do Collision Response between two boxes
\param box1 - set new body info
\param box2 - set new body info
*/
/******************************************************************************/
void World::ResponseBoxToBox(RigidBody* box1, RigidBody* box2)
{			
	Transform* tsf1 = box1->GetTransform();
	Transform* tsf2 = box2->GetTransform();

	// If 2nd box is movable, refresh both 2 bodies info
	if (box1->GetMoveToggle() && box2->GetMoveToggle())
	{
			// Move both onjects to be proper position
			// after the colliding
			tsf2->SetPosition(tsf2->GetPosition() - .5f * mtd);
			tsf1->SetPosition(tsf1->GetPosition() + .5f * mtd);

			// Calculate new velocity
			box1->SetDirectionVector(
				box1->GetDirectionVector().Reflection(
					collided_edge));

			// if 1st body's force is stronger than 2nd.
			// 2nd sprite's velocity to be set same as the 1st
			if (box1->GetMass() > box2->GetMass())
				box2->SetDirectionVector(box1->GetDirectionVector());

			// else if (the 2nd stronger, than set opposite velocity)
			// Set opposite velocity
			else
				box2->SetDirectionVector(-box1->GetDirectionVector());

			// Reset the speed
			// Save new speeds of two boxes
			new_speed[0] = box1->GetSpeed() *
				(box1->GetMass() /
				(box2->GetMass() + box1->GetMass()));

			new_speed[1] = box2->GetSpeed() *
				(box2->GetMass() /
				(box2->GetMass() + box1->GetMass()));

			// Reset the speeds
			box1->SetSpeed(new_speed[0] + new_speed[1] / box2->GetMass());
			box2->SetSpeed(new_speed[1] + new_speed[0] / box1->GetMass());
	}

	// 1st sprite is unmovable,
	else if (!box1->GetMoveToggle() && box2->GetMoveToggle())
	{
		// Here refresh only 1sr sprite
		tsf2->SetPosition(tsf2->GetPosition() - mtd);

		// Calculate new reflected velocity
		box2->SetDirectionVector(
			box2->GetDirectionVector().Reflection(
				collided_edge));

		// Reset the speed
		new_speed[1] = box2->GetSpeed() *
			(box2->GetMass() /
			(box2->GetMass() + box1->GetMass()));

		// Reset the speeds
		box2->SetSpeed(new_speed[1]);
	}

	// 2nd sprite is unmovable,
	else if (box1->GetMoveToggle() && !box2->GetMoveToggle())
	{
		// Here refresh only 1sr sprite
		tsf1->SetPosition(tsf1->GetPosition() + mtd);

		// Calculate new reflected velocity
		box1->SetDirectionVector(
			box1->GetDirectionVector().Reflection(
				collided_edge));

		// Reset the speed
		new_speed[0] = box1->GetSpeed() *
			(box1->GetMass() /
			(box2->GetMass() + box1->GetMass()));

		// Reset the speeds
		box1->SetSpeed(new_speed[0]);
	}
}

/******************************************************************************/
/*!
\brief - Do Collision Response between ball and box
\param box - set new body info
\param ball - set new body info
*/
/******************************************************************************/
void World::ResponseBoxToBall(RigidBody* box, RigidBody* ball)
{		
	Transform* box_tsf = box->GetTransform();
	Transform* ball_tsf = ball->GetTransform();

	vec3 n = mtd.Normalize();
	
	// Save new velocities
	vec3 new_vel[2];
	new_vel[0] = box->GetDirectionVector() - n ;
	new_vel[1] = ball->GetDirectionVector() + n ;

	// Save new speed
	new_speed[0] = box->GetSpeed() *
		(box->GetMass() /
		(ball->GetMass() + box->GetMass()));

	new_speed[1] = ball->GetSpeed() *
		(ball->GetMass() /
		(ball->GetMass() + box->GetMass()));

	// If both 2 sprites are movable...
	if (box->GetMoveToggle() && ball->GetMoveToggle())
	{
		// Set sprites' position with mtd
		box_tsf->SetPosition(box_tsf->GetPosition() - mtd * .5f);
		ball_tsf->SetPosition(ball_tsf->GetPosition() + mtd * .5f);

		// Set new velocity
		box->SetDirectionVector(new_vel[0]);
		ball->SetDirectionVector(new_vel[1]);

		// Set new speed
		box->SetSpeed(new_speed[0] + new_speed[1] / ball->GetMass());
		ball->SetSpeed(new_speed[1] + new_speed[0] / box->GetMass());
	}

	// If only box sprite is movable...
	else if (!ball->GetMoveToggle() && box->GetMoveToggle())
	{
		// Set sprites' position with mtd
		box_tsf->SetPosition(box_tsf->GetPosition() - mtd);

		// Set new velocity
		box->SetDirectionVector(new_vel[0]);

		// Set new speed
		box->SetSpeed(new_speed[0] + new_speed[1] / ball->GetMass());
	}

	// If only ball sprite is movable...
	else if (!box->GetMoveToggle() && ball->GetMoveToggle())
	{
		// Set sprites' position with mtd
		ball_tsf->SetPosition(ball_tsf->GetPosition() + mtd);

		// Set new velocity
		ball->SetDirectionVector(new_vel[1]);

		// Set new speed
		ball->SetSpeed(new_speed[1] + new_speed[0] / box->GetMass());
	}
}

/******************************************************************************/
/*!
\brief - Do Collision Relation
\param body1 - get 1st sprite
\param body2 - get 2nd sprite
\param coliided - Set 2 bodies collision status
*/
/******************************************************************************/
void World::CollisionRelation(RigidBody* body1, RigidBody* body2, bool rel)
{
	//Set each sprite's collision status
	body1->GetCollisionMap()[body2->GetOwner()->GetID()] = rel;
	body2->GetCollisionMap()[body1->GetOwner()->GetID()] = rel;
}

/******************************************************************************/
/*!
\brief - Add bbdy to the list
\param body 
*/
/******************************************************************************/
void World::AddRigidBody(Object* obj)
{
	RigidBody* body = obj->GetComponent<RigidBody>(CT_RIGIDBODY);

	// Delete if there is same rigid body
	for (auto it = m_bodyList.begin(); it != m_bodyList.end(); ++it)
		if (body->GetOwner()->GetID() == (*it)->GetOwner()->GetID())
		{
			m_bodyList.erase(it);
			break;
		}

	//Init bodies' collision relationship info
	for (auto it = m_bodyList.begin(); it != m_bodyList.end(); ++it)
	{
		// Add exist bodies' relationship with this new body to this body's list 
		body->GetCollisionMap().insert(
			CollisionMap::value_type((*it)->GetOwner()->GetID(), false));

		// Add new body's relationship with exist bodies' to their list 
		(*it)->GetCollisionMap().insert(
			CollisionMap::value_type(body->GetOwner()->GetID(), false));
	}

	// And add to the list
	m_bodyList.push_back(body);
}

/******************************************************************************/
/*!
\brief - Add bbdy to the list
\param id - Sprite's id number
*/
/******************************************************************************/
void World::RemoveBody(const int id)
{
	for (auto it = m_bodyList.begin(); it != m_bodyList.end(); ++it)
	{
		if (id == (*it)->GetOwner()->GetID())
		{
			m_bodyList.erase(it);
			break;
		}
	}
}

/******************************************************************************/
/*!
\brief - Clear all nodes in the world
\param index - node's index
\param position - node's real position in the world
*/
/******************************************************************************/
void World::AddNode(ObjectManager* OBM, const Index & index, const vec3 & position)
{
	bool found = false;

	// If there is no same index in the list,
	// set found to true
	for (auto it : m_nodeList)
		if (it->GetIndex() == index) {
			found = true;
			std::cout << "There is a node that has same index!!";
		}

	// If there is no found,
	// add new to the static list
	if (!found) {

		Node* node = new Node(OBM);
		node->SetIndex(index);
		node->SetPosition(position);
		
		m_nodeList.push_back(node);
	}

	// Rearrange the nodes' link
	for (auto it : m_nodeList) {
		it->m_neighbors.clear();
		for (auto candidates : m_nodeList)
			if ((*it).IsNear(candidates))
				(*it).m_neighbors.push_back(candidates);
	}
}

/******************************************************************************/
/*!
\brief - Clear all nodes in the world
*/
/******************************************************************************/
void World::ClearNodes(void)
{
	for (auto it : m_nodeList)
	{
		delete it;
		it = 0;
	}

	m_nodeList.clear();
}

/******************************************************************************/
/*!
\brief - Get the distance between 2 nodes including across case
\param node1 - starting point
\param node2 - destination point
*/
/******************************************************************************/
int World::Distance_Nodes1(Node * node1, Node * node2)
{
	int diff_x = abs(node1->m_index.x - node2->m_index.x), 
		diff_y = abs(node1->m_index.y - node2->m_index.y);
	
	if (diff_x == 1 && diff_y == 1)
		return 14;

	return 10;
}

/******************************************************************************/
/*!
\brief - Get the distance between 2 nodes without across case
\param node1 - starting point
\param node2 - destination point
*/
/******************************************************************************/
int World::Distance_Nodes2(Node * node1, Node * node2)
{
	Index diff = node1->m_index - node2->m_index;
	return (abs(diff.x) + abs(diff.y)) * 10;
}

/******************************************************************************/
/*!
\brief - Get the shortest node when starting to get the path fiding 
\param node1 - starting point
\param node2 - destination point
*/
/******************************************************************************/
Node* World::GetClosestNode(const vec3 & position)
{
	// Get first node as shortest node
	Node* s_node = (*m_nodeList.begin());
	// Get first distance as shortest distance
	float s_distance = Math::Distance_pt(s_node->GetPosition(), position);

	for (auto it : m_nodeList)
	{
		// Calculate distance input position and node's position 
		float t_distance = Math::Distance_pt(it->GetPosition(), position);

		// If the t_distance is shorter than exsiting distance,
		// update s_distance and s_node
		if (t_distance < s_distance) {
			s_distance = t_distance;
			s_node = it;
		}
	}

	// Return the shortest node
	return s_node;
}

/******************************************************************************/
/*!
\brief - World's shutdown function
\param node1 - starting point
\param node2 - destination point
*/
/******************************************************************************/
Node* World::GetNode(const Index & index)
{
	for (auto it = m_nodeList.begin();
		it != m_nodeList.end(); ++it)
		if ((*it)->GetIndex() == index)
			return *it;

	return nullptr;
}

/******************************************************************************/
/*!
\brief - World's shutdown function
\param node1 - starting point
\param node2 - destination point
*/
/******************************************************************************/
Node* World::GetNode(const vec3& position)
{
	for (auto it = m_nodeList.begin();
		it != m_nodeList.end(); ++it)
		if ((*it)->GetPosition() == position)
			return *it;

	return nullptr;
}

/******************************************************************************/
/*!
\brief - World's shutdown function
\param node1 - starting point
\param node2 - destination point
*/
/******************************************************************************/
void World::GetRoute(Node * node1, Node * node2)
{
	// Clear pre nodes list...
	RefreshNodes();

	// Save where from and to go....
	m_headNode = node1;
	m_tailNode = node2;

	// The result RoadList
	Node::LinkMap openList, closedList;

	// Add current node to open list
	openList.insert(Node::LinkMap::value_type(m_headNode, m_headNode));
	m_headNode->toEnd
		= m_headNode->cost 
		= Distance_Nodes2(m_headNode, m_tailNode);

	Node* current = nullptr;
	while (openList.size()) {

		// Set the current node
		// that has lowest cost in the open list
		current = openList.begin()->second;
		for (auto it : openList) {
			if (it.second->cost < current->cost)
				current = it.second;
		}

		// If the current node is same as destination(node2),
		// stop looping
		if (current == m_tailNode) {
			while (current) {
				m_pfList.push_back(current);
				current = current->m_prev;
			}
			std::reverse(m_pfList.begin(), m_pfList.end());
			break;
		}

		// Remove current node from open list
		// and add to closed list
		openList.erase(current);
		closedList.insert(Node::LinkMap::value_type(current, current));
		int tentative_cost = 0;
		
		// Calculate info in advance
		for (auto it : current->m_neighbors) {

			// If the neighbor is in the close list
			// then ignore
			if (closedList.find(it) != closedList.end())
				continue;
			
			tentative_cost = current->fromStart + Distance_Nodes1(current, it);
			
			// Add this to the open list
			if (openList.find(it) == openList.end())
				openList.insert(Node::LinkMap::value_type(it, it));

			// Check and set up info
			else if (tentative_cost >= it->fromStart)
				continue;

			// Calculate the info...
			it->m_prev = current;
			it->fromStart = tentative_cost;
			it->toEnd = Distance_Nodes2(it, m_tailNode);
			it->cost = it->toEnd + it->fromStart;
		} // for (auto it : current->m_neighbors)
	} // while (openList.size()) {
}

/******************************************************************************/
/*!
\brief - Refresh all nodes that have been used
*/
/******************************************************************************/
void World::RefreshNodes(void)
{
	m_pfList.clear();
	for (auto it : m_nodeList) {
		it->m_prev = nullptr;
		it->fromStartf = it->toEndf = 0.f;
		it->toEnd = it->fromStart = it->cost = 0;
	}
}

/******************************************************************************/
/*!
\brief - Get path finding result list
\return m_pfList
*/
/******************************************************************************/
NodeList & World::GetPFList(void)
{
	return m_pfList;
}

/******************************************************************************/
/*!
\brief - Get node list
\return m_nodeList
*/
/******************************************************************************/
NodeList & World::GetNodeList(void)
{
	return m_nodeList;
}

/******************************************************************************/
/*!
\brief - Get nodes' size
\return m_Nodesize
*/
/******************************************************************************/
int World::GetNodeSize(void) const
{
	return m_Nodesize;
}

