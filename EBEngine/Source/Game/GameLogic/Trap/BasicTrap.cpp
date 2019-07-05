/******************************************************************************/
/*!
\file   BasicTrap.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2016/10/06(yy/mm/dd)

\description
Contains BasicTrap logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "BasicTrap.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - BasicTrapBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* BasicTrapBuilder::BuildLogic(Object* Owner, LogicType key) const
{
    return new BasicTrap(Owner, key);
}

/******************************************************************************/
/*!
\brief - BasicTrap constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
BasicTrap::BasicTrap(Object* Owner, LogicType key)
    : GameLogic(Owner, key), waitingTime(0.f), runningTime(0.f)
{}

/******************************************************************************/
/*!
\brief - Load BasicTrap info
\param data - json parser
*/
/******************************************************************************/
void BasicTrap::Load(const Json::Value& data)
{
    if (data.isMember("WaitingTime") &&
        data["WaitingTime"].isNumeric())
        waitingTime = data["WaitingTime"].asFloat();
    if (data.isMember("RunningTime") &&
        data["RunningTime"].isNumeric())
        runningTime = data["RunningTime"].asFloat();
}

/******************************************************************************/
/*!
\brief - Initialize BasicTrap info
*/
/******************************************************************************/
void BasicTrap::Init(void)
{
    updateCycle = 0.f;
    active = false;

    m_OBM->GetObjects(AT_PLAYER, player);

    if (player.size())
    {
        player_id = player[0]->GetID();
        middle = player[0]->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
    }
    else
        player_id = 0;
}

/******************************************************************************/
/*!
\brief - Update BasicTrap info
\param dt - delta time
*/
/******************************************************************************/
void BasicTrap::Update(float dt)
{
    // OPERATION, set trap active.
    if (updateCycle > waitingTime && active == false)
    {
        updateCycle = 0;
        active = true;
        trapCondition = OPERATION;
    }
    // WAITING, wait for specific time to act.
    else if (active == false)
    {
        updateCycle += (dt * m_Owner->GetdtOffset());
        trapCondition = WAITING;
    }
    //CUTOFF
    else if (active == true && updateCycle > runningTime)
    {
        m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1.f, 1.f, 1.f, 1.f));
        active = false;
        updateCycle = 0;
        trapCondition = CUTOFF;
    }
    //ACTIVATING
    else if (active == true)
    {
        updateCycle += (dt * m_Owner->GetdtOffset());
        trapCondition = ACTIVATING;
    }
}

/******************************************************************************/
/*!
\brief - Shutdown BasicTrap info
*/
/******************************************************************************/
void BasicTrap::Shutdown(void)
{
}

/******************************************************************************/
/*!
\brief - Unload BasicTrap info
*/
/******************************************************************************/
void BasicTrap::Unload(void)
{
}

/******************************************************************************/
/*!
\brief - check it is activate or not
\return active - return it is work or not
*/
/******************************************************************************/
bool BasicTrap::CheckActive(void)
{
    return active;
}

/******************************************************************************/
/*!
\brief - control active
\param value - setting it is active or not
*/
/******************************************************************************/
void BasicTrap::SetActive(bool value)
{
    active = value;
}

/******************************************************************************/
/*!
\brief - set the cycle of trap
\param cycle - setting its cycle
*/
/******************************************************************************/
void BasicTrap::SetCycle(float cycle)
{
    updateCycle = cycle;
}

/******************************************************************************/
/*!
\brief - get player's id
\return player_id - get the id of player
*/
/******************************************************************************/
int BasicTrap::GetPlayer(void)
{
    return player_id;
}

/******************************************************************************/
/*!
\brief - get the player
\return player - return the player
*/
/******************************************************************************/
Object* BasicTrap::GetPlayerSpt(void)
{
    return player[0];
}

/******************************************************************************/
/*!
\brief - settor of running time
\param runTime - setting its running time
*/
/******************************************************************************/
void BasicTrap::SetRunningTime(float runTime)
{
    runningTime = runTime;
}

/******************************************************************************/
/*!
\brief - settor of waiting time
\param waitTime - setting its waiting time
*/
/******************************************************************************/
void BasicTrap::SetWaitingTime(float waitTime)
{
    waitingTime = waitTime;
}

/******************************************************************************/
/*!
\brief - get the time of waiting
\return waitingTime - get value
*/
/******************************************************************************/
float BasicTrap::GetWaitingTime()
{
	return waitingTime;
}

/******************************************************************************/
/*!
\brief - get the time of running
\return runningTime - get value
*/
/******************************************************************************/
float BasicTrap::GetRunningTime()
{
	return runningTime;
}
