/******************************************************************************/
/*!
\file   LV1.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/24(yy/mm/dd)

\description
Contains LV1 stage class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _LV1STAGE_H_
#define _LV1STAGE_H_

#include "../../../Engine/StateManager/BaseStage.h"
#include "../../../Engine/StateManager/StageBuilder.h"

class LV1Stage : public Stage
{
public:

	LV1Stage(GameStateManager* GSM = 0, ObjectManager* OBM = 0);

	virtual ~LV1Stage();
	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

};

class LV1Builder : public StageBuilder
{

public:
	virtual ~LV1Builder(){};

	Stage* BuildStage(GameStateManager* GSM, ObjectManager* OBM) {
		return new LV1Stage(GSM, OBM);
	}

private:

};

#endif // _LV1STAGE_H_