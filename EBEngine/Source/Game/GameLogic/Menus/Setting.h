/******************************************************************************/
/*!
\file   Setting.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/04/11(yy/mm/dd)

\description
Contains Setting logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _SETTING_H_
#define _SETTING_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class SettingBuilder : public LogicBuilder
{

public:
	SettingBuilder() {};
	virtual ~SettingBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Audio;
class Setting : public GameLogic
{
public:

	Setting(Object* Owner, LogicType key);
	virtual ~Setting(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

	void UpdateKeys(void);
	void SetMouse();

	void UpdateMouse(void);
	void SetMenuAssets(void);
	void UpdateMenuAssets(float dt);

	int menu_id;

	// Menu assets info
	Audio* selectSFX;
	Object *title, *background, *m_mouse, *m_volumeText;
	bool colorToggle;
	vec3 titlePos, mouseScl;
	vec4 bgColor;
	int tmpMouseId;
    bool xInptDly;
    float dly = 0.f;
};

#endif // _SETTING_H_
