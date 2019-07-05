/******************************************************************************/
/*!
\file   Tutorials_4.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017-05-24(yy/mm/dd)

\description
Contains Tutorials_4 stage class, builder class, and eaders of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _TUTORIALS_4_H_
#define _TUTORIALS_4_H_

#include "../../../Engine/StateManager/BaseStage.h"
#include "../../../Engine/StateManager/StageBuilder.h"

class Tutorials_4 : public Stage
{
public:
	Tutorials_4(GameStateManager* GSM = 0, ObjectManager* OBM = 0);

	virtual ~Tutorials_4();
	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

};

class Tutorials_4Builder : public StageBuilder
{
public:
	virtual ~Tutorials_4Builder(){};

	Stage* BuildStage(GameStateManager* GSM, ObjectManager* OBM) {
		return new Tutorials_4(GSM, OBM);
	}

private:
};

#endif // _TUTORIALS_4_H_
