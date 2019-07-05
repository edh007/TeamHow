/******************************************************************************/
/*!
\file   SettingStage.h
\author JeongJuyong
\par    email: jeykop14@gmail.com
\date   2017-04-09(yy/mm/dd)

\description
Contains SettingStage stage class, builder class, and eaders of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _SETTINGSTAGE_H_
#define _SETTINGSTAGE_H_

#include "../../../Engine/StateManager/BaseStage.h"
#include "../../../Engine/StateManager/StageBuilder.h"

class SettingStage : public Stage
{
public:
	SettingStage(GameStateManager* GSM = 0, ObjectManager* OBM = 0);

	virtual ~SettingStage();
	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

};

class SettingStageBuilder : public StageBuilder
{
public:
	virtual ~SettingStageBuilder(){};

	Stage* BuildStage(GameStateManager* GSM, ObjectManager* OBM) {
		return new SettingStage(GSM, OBM);
	}

private:
};

#endif // _SETTING_H_
