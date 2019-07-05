/******************************************************************************/
/*!
\file   MainScreen.h
\author Jeong Juyong
\par    email: jeykop14@gmail.com
\date   2016/10/31(yy/mm/dd)

\description
Contains MainScreen logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _MAINSCREEN_H_
#define _MAINSCREEN_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class MainScreenBuilder : public LogicBuilder
{

public:
	MainScreenBuilder() {};
	virtual ~MainScreenBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Audio;
class MainScreen : public GameLogic
{
public:

	MainScreen(Object* Owner, LogicType key);
	virtual ~MainScreen(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

	void UpdateKeys(void);
	void SetMouse(void);
	void UpdateMouse(float dt);
	void SetMenuAssets(void);
	void UpdateMenuAssets(float dt);

	std::vector<Object*> menuList;
	int menu_id;
	Audio* m_fist, *selectSfx;

	// Menu assets info
	Object *title, *fist, *background;	
	Object *m_mouse;
	bool toggle, fistToggle, colorToggle;
	float rotate, fistSpeed;
	vec3 titlePos, menuPos, mouseScl, fistScl;
	vec4 bgColor;
    bool xInptDly;
    float dly = 0.f;
};

#endif // _MAINSCREEN_H_
