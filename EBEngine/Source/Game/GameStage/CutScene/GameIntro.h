/******************************************************************************/
/*!
\file   GameIntro.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017-06-11(yy/mm/dd)

\description
Contains GameIntro stage class, builder class, and eaders of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _GAMEINTRO_H_
#define _GAMEINTRO_H_

#include "../../../Engine/StateManager/BaseStage.h"
#include "../../../Engine/StateManager/StageBuilder.h"

class GameIntro : public Stage
{
public:
	GameIntro(GameStateManager* GSM = 0, ObjectManager* OBM = 0);

	virtual ~GameIntro();
	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

};

class GameIntroBuilder : public StageBuilder
{
public:
	virtual ~GameIntroBuilder(){};

	Stage* BuildStage(GameStateManager* GSM, ObjectManager* OBM) {
		return new GameIntro(GSM, OBM);
	}

private:
};

#endif // _GAMEINTRO_H_
