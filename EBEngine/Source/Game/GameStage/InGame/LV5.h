/******************************************************************************/
/*!
\file   LV5.h
\author DonghoLee
\par    email: edongho007@gmail.com
\date   2017-06-13(yy/mm/dd)

\description
Contains LV5 stage class, builder class, and eaders of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _LV5_H_
#define _LV5_H_

#include "../../../Engine/StateManager/BaseStage.h"
#include "../../../Engine/StateManager/StageBuilder.h"

class LV5 : public Stage
{
public:
	LV5(GameStateManager* GSM = 0, ObjectManager* OBM = 0);

	virtual ~LV5();
	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

};

class LV5Builder : public StageBuilder
{
public:
	virtual ~LV5Builder(){};

	Stage* BuildStage(GameStateManager* GSM, ObjectManager* OBM) {
		return new LV5(GSM, OBM);
	}

private:
};

#endif // _LV5_H_
