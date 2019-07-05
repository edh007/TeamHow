/******************************************************************************/
/*!
\file   LV2.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/24(yy/mm/dd)

\description
Contains LV2 stage class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _LV2_H_
#define _LV2_H_

#include "../../../Engine/StateManager/BaseStage.h"
#include "../../../Engine/StateManager/StageBuilder.h"

class LV2 : public Stage
{
public:
	LV2(GameStateManager* GSM = 0, ObjectManager* OBM = 0);

	virtual ~LV2();
	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

};

class LV2Builder : public StageBuilder
{
public:
	virtual ~LV2Builder(){};

	Stage* BuildStage(GameStateManager* GSM, ObjectManager* OBM) {
		return new LV2(GSM, OBM);
	}

private:
};

#endif // _LV2_H_
