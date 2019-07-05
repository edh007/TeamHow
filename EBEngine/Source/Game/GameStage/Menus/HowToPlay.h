/******************************************************************************/
/*!
\file   HowToPlay.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017-06-08(yy/mm/dd)

\description
Contains HowToPlay stage class, builder class, and eaders of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _HOWTOPLAY_H_
#define _HOWTOPLAY_H_

#include "../../../Engine/StateManager/BaseStage.h"
#include "../../../Engine/StateManager/StageBuilder.h"

class HowToPlay : public Stage
{
public:
	HowToPlay(GameStateManager* GSM = 0, ObjectManager* OBM = 0);

	virtual ~HowToPlay();
	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

};

class HowToPlayBuilder : public StageBuilder
{
public:
	virtual ~HowToPlayBuilder(){};

	Stage* BuildStage(GameStateManager* GSM, ObjectManager* OBM) {
		return new HowToPlay(GSM, OBM);
	}

private:
};

#endif // _HOWTOPLAY_H_
