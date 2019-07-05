/******************************************************************************/
/*!
\file   HowToPlayLogic.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/06/10(yy/mm/dd)

\description
Contains HowToPlayLogic logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _HOWTOPLAYLOGIC_H_
#define _HOWTOPLAYLOGIC_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class HowToPlayLogicBuilder : public LogicBuilder
{

public:
	HowToPlayLogicBuilder() {};
	virtual ~HowToPlayLogicBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Audio;
class HowToPlayLogic : public GameLogic
{
public:

	HowToPlayLogic(Object* Owner, LogicType key);
	virtual ~HowToPlayLogic(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:
	
	void SetMouse(void);
	void UpdateMouse(void);
	void SetMenuAssets(void);
	void UpdateMenuAssets(float dt);
	void UpdateKeys(float dt);

	Audio* selectSFX;
	Object* m_mouse, *m_pic1, *m_pic2, *background, *m_inst;
	vec3 mouseScl;
	vec4 bgColor;
	bool colorToggle;
	int tmpMouseId, menu_id;
	bool xInptDly;
	float dly = 0.f;

};

#endif // _HOWTOPLAYLOGIC_H_
