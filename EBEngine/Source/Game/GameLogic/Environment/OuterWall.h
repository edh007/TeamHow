/******************************************************************************/
/*!
\file   OuterWall.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/03/28(yy/mm/dd)

\description
Contains OuterWall logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _OUTERWALL_H_
#define _OUTERWALL_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class OuterWallBuilder : public LogicBuilder
{

public:
	OuterWallBuilder() {};
	virtual ~OuterWallBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class RigidBody;
class Transform;
class Sprite;

class OuterWall : public GameLogic
{
public:

	OuterWall(Object* Owner, LogicType key);
	virtual ~OuterWall(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:
	Object* walls[4];
	RigidBody* m_rid;
	Transform* m_trs;
	Sprite* m_spr;
};

#endif // _OUTERWALL_H_
