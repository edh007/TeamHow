/******************************************************************************/
/*!
\file   MenuStage.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains MenuStage stage class, builder class, and eaders of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _MAINMENUSTAGE_H_
#define _MAINMENUSTAGE_H_

#include "../../../Engine/StateManager/BaseStage.h"
#include "../../../Engine/StateManager/StageBuilder.h"

class MenuStage : public Stage
{
public:

	MenuStage(GameStateManager* GSM = 0, ObjectManager* OBM = 0);

	virtual ~MenuStage();
	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

};

class MainMenuBuilder : public StageBuilder
{

public:

	virtual ~MainMenuBuilder(){};

	Stage* BuildStage(GameStateManager* GSM, ObjectManager* OBM) {
		return new MenuStage(GSM, OBM);
	}

private:

};

#endif // _MAINMENUSTAGE_H_