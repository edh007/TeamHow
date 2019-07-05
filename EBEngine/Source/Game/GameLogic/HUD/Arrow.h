/******************************************************************************/
/*!
\file   Arrow.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/03/06(yy/mm/dd)

\description
Contains Arrow logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _ARROW_H_
#define _ARROW_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class ArrowBuilder : public LogicBuilder
{

public:
	ArrowBuilder() {};
	virtual ~ArrowBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Sprite;
class Transform;

class Arrow : public GameLogic
{
public:

	Arrow(Object* Owner, LogicType key);
	virtual ~Arrow(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	bool GetToggle(void);
	void SetToggle(bool tog);

private:
	Object* m_Object;
	Sprite* m_Sprite;
	Transform* m_Trs;
	bool active;
	float m_time;
	bool toggle;
};

#endif // _ARROW_H_
