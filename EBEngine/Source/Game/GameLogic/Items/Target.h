/******************************************************************************/
/*!
\file   Target.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2016/11/08(yy/mm/dd)

\description
Contains Target logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _Target_H_
#define _Target_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class TargetBuilder : public LogicBuilder
{

public:
	TargetBuilder() {};
	virtual ~TargetBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Audio;

class Target : public GameLogic
{
public:

	Target(Object* Owner, LogicType key);
	virtual ~Target(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	bool CheckItem(void);
	void SetItem(bool value);
private:
	bool playerGet;
	std::vector<Object*> player;
	int player_id;

	Audio* m_sound;
	float soundTime;
	bool soundToggle;

};

#endif // _Target_H_
