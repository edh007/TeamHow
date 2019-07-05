/******************************************************************************/
/*!
\file   Normal.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2016/11/26(yy/mm/dd)

\description
Contains Normal logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _NORMAL_H_
#define _NORMAL_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class NormalBuilder : public LogicBuilder
{

public:
	NormalBuilder() {};
	virtual ~NormalBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Normal : public GameLogic
{
public:

	Normal(Object* Owner, LogicType key);
	virtual ~Normal(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

};

#endif // _NORMAL_H_
