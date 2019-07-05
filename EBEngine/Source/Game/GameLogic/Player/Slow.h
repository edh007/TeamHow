/******************************************************************************/
/*!
\file   Slow.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/11/07(yy/mm/dd)

\description
Contains Slow logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _SLOW_H_
#define _SLOW_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class SlowBuilder : public LogicBuilder
{

public:
	SlowBuilder() {};
	virtual ~SlowBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Slow : public GameLogic
{
public:

	Slow(Object* Owner, LogicType key);
	virtual ~Slow(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	void ActivateSlow(bool toggle);
	bool GetSlowToggle(void) const;
	bool IsSlow(void) const;

	void SetSlowOffset(float offset);
	float GetSlowOffset(void) const;

private:

	// Shield info
	float gauge;

	// Slow toggle
	float m_offset;
	bool m_slowActivated;
	bool m_toggle;
};

#endif // _SLOW_H_
