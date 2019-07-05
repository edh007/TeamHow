/******************************************************************************/
/*!
\file   SplashStage.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016-11-15(yy/mm/dd)

\description
Contains SplashStage stage class, builder class, and eaders of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _SPLASHSTAGE_H_
#define _SPLASHSTAGE_H_

#include "../../../Engine/StateManager/BaseStage.h"
#include "../../../Engine/StateManager/StageBuilder.h"

class SplashStage : public Stage
{
public:
	SplashStage(GameStateManager* GSM = 0, ObjectManager* OBM = 0);

	virtual ~SplashStage();
	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

};

class SplashStageBuilder : public StageBuilder
{
public:
	virtual ~SplashStageBuilder(){};

	Stage* BuildStage(GameStateManager* GSM, ObjectManager* OBM) {
		return new SplashStage(GSM, OBM);
	}

private:
};

#endif // _SPLASHSTAGE_H_
