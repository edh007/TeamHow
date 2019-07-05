/******************************************************************************/
/*!
\file   MenuSelect.h
\author Jeong Juyong
\par    email: jeykop14@gmail.com
\date   2016/10/31(yy/mm/dd)

\description
Contains MenuSelect logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _MENUSELECT_H_
#define _MENUSELECT_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

enum MenuSelection {M_PLAY, M_SETTING, M_CREDIT, M_QUIT, 
	M_BACK, P_RESTART, P_HOWTOPLAY, P_GOTOMENU, P_SETTING,
	/*R_1024X768, R_1280X1024, R_1920X1080,*/
	S_ON, S_OFF,
	V_LEFT, V_RIGHT,
	/*S_SAVE, S_LOAD,*/
	C_YES, C_NO, S_NONE};

class MenuSelectBuilder : public LogicBuilder
{

public:
	MenuSelectBuilder() {};
	virtual ~MenuSelectBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Text;
class Audio;
class MenuSelect : public GameLogic
{
public:

	MenuSelect(Object* Owner, LogicType key);
	virtual ~MenuSelect(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	void SetTexts(std::string texts);
	void DoConfirm(void);

	std::string saveData;
    
private:
	void GetMouse(float dt);
	void DoResponse(void);
	void ColorEffect( float dt);
	void MakeConfirm(void);

	vec3 m_pos, m_scale;
	vec4 m_color;

	Audio* selectSfx;

	MenuSelection m_select;
    Object* menu_text;

	Object *m_ask, *m_askText;
	Object *m_yes;
	Object *m_no;

    int b_w, b_h;

	bool tc[3], sfxBool;
};

#endif // _MENUSELECT_H_
