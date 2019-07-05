/******************************************************************************/
/*!
\file   HUD.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/09/26(yy/mm/dd)

\description
Contains HUD logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _HUD_H_
#define _HUD_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class HUDBuilder : public LogicBuilder
{

public:
	HUDBuilder() {};
	virtual ~HUDBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

//! Class hud
class HUD : public GameLogic
{
public:

	HUD(Object* Owner, LogicType key);
	virtual ~HUD(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	bool GetCooldownToggle(void) const;

private:

	void TimeManipulation(float dt);
	void Run(void);
	void Search(void);
	void ShowInfo(float dt);
	void SkillText(float dt);
	void ColorEffect(vec4& color, bool& toggle, float dt);

	vec2 mousePos;
	vec3 instOffset;
	vec4 invisible, visible;

	Object *m_needle, *m_clock, *m_footstep, *m_eye, *m_shift, *m_point,
		*m_time, *m_enemy, *m_q, *m_space, *m_lm, *m_death, *m_skillText;
	
	// For skill texts
	vec3 m_skillPos;
	vec4 skillColor;

	// For clock and needle
	vec4 m_clClr, m_needleClr;
	vec3 m_needlePos, m_clPos;

	// For foot
	vec3 m_fsPos, m_fsScl;
	vec4 m_fsClr;

	// For eye
	vec3 m_eyePos;
	vec4 m_eyeClr;

	// For q and space button popup
	vec4 m_spaceClr, m_qClr, m_shiftClr, m_pointClr;
	vec3 m_qPos, m_spacePos, m_shiftPos, m_pointPos;

	// For texts
	vec3 m_timePos, m_enemyPos, m_deathPos;

	vec3 m_cameraPos, m_smScl, m_bigScl;
	int m_enemySize;
	bool m_tmToggle, m_cooldown, m_Effect, m_alarm, m_colorToggle, m_warning;
	float dt_Stack[2], m_rotation, offset, m_radius, m_radian, cd_offset, m_blink;
	bool getEnemies, colorToggle, pointToggle;
};

#endif // _HUD_H_
