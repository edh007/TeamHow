/******************************************************************************/
/*!
\file   Credit.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/04/11(yy/mm/dd)

\description
Contains Credit logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _CREDIT_H_
#define _CREDIT_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class CreditBuilder : public LogicBuilder
{

public:
	CreditBuilder() {};
	virtual ~CreditBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Audio;
class Credit : public GameLogic
{
public:

	Credit(Object* Owner, LogicType key);
	virtual ~Credit(void) {};

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
	void UpdateKeys(void);

	Audio* selectSFX;
	Object* m_mouse, *title, *m_creditList, *m_creditContents, *background;
	vec3 mouseScl;
	vec4 bgColor;
	bool colorToggle;
	int tmpMouseId, menu_id;
    bool xInptDly;
    float dly = 0.f;
};

#endif // _CREDIT_H_
