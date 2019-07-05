/******************************************************************************/
/*!
\file   CreditStage.h
\author JeongJuyong
\par    email: jeykop14@gmail.com
\date   2017-04-09(yy/mm/dd)

\description
Contains CreditStage stage class, builder class, and eaders of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _CREDITSTAGE_H_
#define _CREDITSTAGE_H_

#include "../../../Engine/StateManager/BaseStage.h"
#include "../../../Engine/StateManager/StageBuilder.h"

class CreditStage : public Stage
{
public:
	CreditStage(GameStateManager* GSM = 0, ObjectManager* OBM = 0);

	virtual ~CreditStage();
	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

};

class CreditStageBuilder : public StageBuilder
{
public:
	virtual ~CreditStageBuilder(){};

	Stage* BuildStage(GameStateManager* GSM, ObjectManager* OBM) {
		return new CreditStage(GSM, OBM);
	}

private:
};

#endif // _CREDIT_H_
