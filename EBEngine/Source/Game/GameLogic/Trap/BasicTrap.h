/******************************************************************************/
/*!
\file   BasicTrap.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2016/10/06(yy/mm/dd)

\description
Contains BasicTrap logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _BASICTRAP_H_
#define _BASICTRAP_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

enum TrapCondition { ACTIVATING, CUTOFF, OPERATION, WAITING };

class BasicTrapBuilder : public LogicBuilder
{

public:
    BasicTrapBuilder() {};
    virtual ~BasicTrapBuilder() {};
    virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class BasicTrap : public GameLogic
{
public:

    BasicTrap(Object* Owner, LogicType key);
    virtual ~BasicTrap(void) {};

    virtual void Load(const Json::Value& data);
    virtual void Init(void);
    virtual void Update(float dt);
    virtual void Shutdown(void);
    virtual void Unload(void);


    bool CheckActive(void);
    void SetActive(bool value);
    int GetPlayer(void);
	Object* GetPlayerSpt(void);
    void SetCycle(float cycle);
    void SetRunningTime(float runTime);
    void SetWaitingTime(float waitTime);
	float GetWaitingTime();
	float GetRunningTime();
    TrapCondition trapCondition;
private:
    float updateCycle;
    float waitingTime;
    float runningTime;
    bool active;
    int player_id;

    std::vector<Object*> player;
    vec3 middle;
};

#endif // _BASICTRAP_H_
