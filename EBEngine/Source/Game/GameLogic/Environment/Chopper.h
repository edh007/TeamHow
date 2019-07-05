/******************************************************************************/
/*!
\file   Chopper.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/05/24(yy/mm/dd)

\description
Contains Chopper logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _CHOPPER_H_
#define _CHOPPER_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class ChopperBuilder : public LogicBuilder
{

public:
	ChopperBuilder() {};
	virtual ~ChopperBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Audio;
class Chopper : public GameLogic
{
public:

	Chopper(Object* Owner, LogicType key);
	virtual ~Chopper(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

	Audio* m_audio;
	Object* m_propeller;
	bool m_activate, m_chopperGone;
};

#endif // _CHOPPER_H_
