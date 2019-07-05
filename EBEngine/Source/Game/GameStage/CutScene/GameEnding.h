/******************************************************************************/
/*!
\file   GameEnding.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017-06-11(yy/mm/dd)

\description
Contains GameEnding stage class, builder class, and eaders of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _GAMEENDING_H_
#define _GAMEENDING_H_

#include "../../../Engine/StateManager/BaseStage.h"
#include "../../../Engine/StateManager/StageBuilder.h"

class GameEnding : public Stage
{
public:
	GameEnding(GameStateManager* GSM = 0, ObjectManager* OBM = 0);

	virtual ~GameEnding();
	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

};

class GameEndingBuilder : public StageBuilder
{
public:
	virtual ~GameEndingBuilder(){};

	Stage* BuildStage(GameStateManager* GSM, ObjectManager* OBM) {
		return new GameEnding(GSM, OBM);
	}

private:
};

#endif // _GAMEENDING_H_
