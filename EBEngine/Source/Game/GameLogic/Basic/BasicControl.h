/******************************************************************************/
/*!
\file   BasicControl.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016-09-11(yy/mm/dd)

\description
Contains BasicControl class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _BasicControl_H_
#define _BasicControl_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"

class BasicControlBuilder : public LogicBuilder
{

public:
	BasicControlBuilder() {};
	virtual ~BasicControlBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class BasicControl : public GameLogic
{
public:

	BasicControl(Object* owner, LogicType key);
	virtual ~BasicControl(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	void BasicStateControl(void);

private:

};

#endif // _BasicControl_H_