/******************************************************************************/
/*!
\file   Lightning.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/04/05(yy/mm/dd)

\description
Contains Lightning logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _LIGHTNING_H_
#define _LIGHTNING_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class LightningBuilder : public LogicBuilder
{

public:
	LightningBuilder() {};
	virtual ~LightningBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Sprite;
class Transform;
class Audio;

class Lightning : public GameLogic
{
public:

	Lightning(Object* Owner, LogicType key);
	virtual ~Lightning(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	void SetActiveToggle(bool _gettor);
	bool GetActiveToggle(void);
	void SetPosition(vec3 _gettor);
	vec3 GetPosition(void);

private:
	bool m_Active;

	Sprite* m_sprite;
	Object* m_object;
	Transform* m_trs;

	Audio* m_sound;
	float soundTime;
	bool soundToggle;
};

#endif // _LIGHTNING_H_
