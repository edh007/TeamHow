/******************************************************************************/
/*!
\file   GameOver.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2016/12/13(yy/mm/dd)

\description
Contains GameOver logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"
#include "../../../BaseData/Stages/StageType.h"

class GameOverBuilder : public LogicBuilder
{

public:
	GameOverBuilder() {};
	virtual ~GameOverBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Audio;
class GameOver : public GameLogic
{
public:

	GameOver(Object* Owner, LogicType key);
	virtual ~GameOver(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

	float showTime;
	float waitTime;
    float clearShowTime;
	std::vector<Object*> door;
	int door_id;
	std::vector<Object*> player;
	int player_id;

	StageType next;
	Object* chopper;
	Audio* m_victory;

    bool showingStage = true;
};

#endif // _GAMEOVER_H_
