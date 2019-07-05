/******************************************************************************/
/*!
\file   World.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains World's class member

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _WORLD_H_
#define _WORLD_G_

#include <vector>
#include "../../../Utilities/Math/MathUtils.h"

class Node;
class Object;
class Transform;
class RigidBody;
class ObjectManager;
class GameStateManager;

//! Type definition for list
typedef Vector3<int> Index;
typedef std::vector<Node*> NodeList;
typedef std::vector<RigidBody*> BodyList;

//! class Physics World
class World
{

public:

	//! constructor and destructor
	World(GameStateManager* GSM);
	~World();
	
	//! World's base function
	void Init(void);
	void Update(float dt);
	void Shutdown(void);

	void AddRigidBody(Object* obj);
	void RemoveBody(const int id);

	bool CollisionIntersect(RigidBody* box1, RigidBody* box2);
	bool CollisionIntersect(RigidBody* body, const vec3& start, const vec3& end);
	void AddNode(ObjectManager* OBM, const Index& index, const vec3& position = vec3());

	// Node functions
	Node* GetClosestNode(const vec3& position);
	Node* GetNode(const Index& index);
	Node* GetNode(const vec3& position);
	void GetRoute(Node * node1, Node * node2);
	void RefreshNodes(void);
	NodeList& GetPFList(void);
	NodeList& GetNodeList(void);
	int GetNodeSize(void) const;

private:

	//! Calculate bodies' motion
	void BodyPipeline(RigidBody* body, float dt);

	//! Collision intersection checking functions
	bool IntersectBallToBall(RigidBody* ball1, RigidBody* ball2);
	bool IntersectBoxToBall(RigidBody* box,	RigidBody* ball);
	bool IntersectBoxToBox(RigidBody* box1,	RigidBody* box2);

	//! Collision response functions
	void CollisionResponse(RigidBody* box1, RigidBody* box2);
	void ResponseBallToBall(RigidBody* ball1, RigidBody* ball2);
	void ResponseBoxToBall(RigidBody* box, RigidBody* ball);
	void ResponseBoxToBox(RigidBody* box1, RigidBody* box2);

	//! box2box helper functions
	void CalculateInterval(vec3& axis, RigidBody* body, float& min, float&max);
	bool AxisSeparatePolygons(vec3* axis, int& index, RigidBody* body1, RigidBody* body2);
	vec3 FindMTD(vec3* pushVector, int iNumVectors);

	//! Collision relation setting function 
	void CollisionRelation(RigidBody* body1, RigidBody* body2, bool rel);

	// Clear nodes in the world
	void ClearNodes(void);

	// Get node that haslowest cost
	int Distance_Nodes1(Node* node1, Node* node2);
	int Distance_Nodes2(Node* node1, Node* node2);
	int m_Nodesize;
	GameStateManager* m_GSM;

	//! Helper variables
	vec3 collided_edge;	//! bodies edge storage
	float new_speed[2];	//! new speed for 2 sprites
	vec3 mtd;			//! minimum  transition distance

	BodyList m_bodyList;
	NodeList m_nodeList;
	NodeList m_pfList;

	Node* m_tailNode, *m_headNode;
	
};

#endif // _WORLD_H_