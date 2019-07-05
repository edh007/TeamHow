/******************************************************************************/
/*!
\file   Node.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2017/01/07(yy/mm/dd)

\description
Contains Node's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include <unordered_map>
#include "../../../Utilities/Math/MathUtils.h"

typedef Vector3<int> Index;

class World;
class Object;
class Sprite;
class ObjectManager;

// Class node for a star algorithm 
class Node {

public :
	friend World;

	typedef std::vector<Node*> LinkList;
	typedef std::unordered_map<Node*, Node*> LinkMap;

	Node(ObjectManager* OBM = 0);
	~Node(void) {};

	void SetIndex(const Index& index);
	Index& GetIndex(void);

	void SetPosition(const vec3& position);
	vec3& GetPosition(void);

	void SetToggle(bool toggle);
	bool GetToggle(void) const;

	// Node operators
	bool operator==(const Node& rhs) {
		return m_index == rhs.m_index;
	}

	bool operator!=(const Node& rhs) {
		return m_index != rhs.m_index;
	}

	bool IsNear(Node* node) const {
		if (node != this)
		if ((abs(node->GetIndex().x - m_index.x) <= 1)
			&& (abs(node->GetIndex().y - m_index.y) <= 1))
			return true;
		
		return false;
	}

	int fromStart, toEnd, cost;
	float fromStartf, toEndf;
	LinkList m_neighbors;

private :
	
	Node* m_prev;
	Index m_index;
	bool m_toggle;
	vec3 m_position;
	
	Object* m_owner;
	ObjectManager* m_OBM;

};

bool node_compare(Node* lhs, Node* rhs);

#endif // _NODE_H_