/******************************************************************************/
/*!
\file   LV4.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/24(yy/mm/dd)

\description
Contains LV4 stage class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _LV4_H_
#define _LV4_H_

#include "../../../Engine/StateManager/BaseStage.h"
#include "../../../Engine/StateManager/StageBuilder.h"

class LV4 : public Stage
{
public:
	LV4(GameStateManager* GSM = 0, ObjectManager* OBM = 0);

	virtual ~LV4();
	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

};

class LV4Builder : public StageBuilder
{
public:
	virtual ~LV4Builder(){};

	Stage* BuildStage(GameStateManager* GSM, ObjectManager* OBM) {
		return new LV4(GSM, OBM);
	}

private:
};

#endif // _LV4_H_
