/******************************************************************************/
/*!
\file   Fov.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/04/06(yy/mm/dd)

\description
Contains Fov logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _FOV_H_
#define _FOV_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class FovBuilder : public LogicBuilder
{

public:
	FovBuilder() {};
	virtual ~FovBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Sprite;
class Transform;

class Fov : public GameLogic
{
public:

	Fov(Object* Owner, LogicType key);
	virtual ~Fov(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:
	
	Sprite* m_sprite;
	Object* m_object;
	Transform* m_trs;
};

#endif // _FOV_H_
