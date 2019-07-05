/******************************************************************************/
/*!
\file   PauseStage.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains PauseStage stage class, builder class, and eaders of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "../../../Engine/StateManager/BaseStage.h"
#include "../../../Engine/StateManager/StageBuilder.h"

class PauseStage : public Stage
{
public:

	PauseStage(GameStateManager* GSM = 0, ObjectManager* OBM = 0);

	virtual ~PauseStage();
	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

};

class PauseBuilder : public StageBuilder
{

public:

	virtual ~PauseBuilder(){};

	Stage* BuildStage(GameStateManager* GSM, ObjectManager* OBM) {
		return new PauseStage(GSM, OBM);
	}

private:

};
