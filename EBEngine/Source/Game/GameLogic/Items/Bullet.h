/******************************************************************************/
/*!
\file   Bullet.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/11/12(yy/mm/dd)

\description
Contains Bullet logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _BULLET_H_
#define _BULLET_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class BulletBuilder : public LogicBuilder
{

public:
	BulletBuilder() {};
	virtual ~BulletBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class RigidBody;
//!Class bullet from enemy
class Bullet : public GameLogic
{
public:

	Bullet(Object* Owner, LogicType key);
	virtual ~Bullet(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	void SetId(int id);

private:

	vec3 m_res;
	int punch_id;
	RigidBody* m_body;
	int m_OwnerId;
};

#endif // _BULLET_H_
