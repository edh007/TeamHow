/******************************************************************************/
/*!
\file   GameIntro.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/06/11(yy/mm/dd)

\description
Contains GameIntro stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "GameIntro.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"
/******************************************************************************/
/*!
\brief - GameIntro constructor
\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
GameIntro::GameIntro(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - GameIntro destructor
*/
/******************************************************************************/
GameIntro::~GameIntro()
{}

/******************************************************************************/
/*!
\brief - Load GameIntro's json data
*/
/******************************************************************************/
void GameIntro::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/CutScene/GameIntro.json");
}

/******************************************************************************/
/*!
\brief - Initialize GameIntro's info
*/
/******************************************************************************/
void GameIntro::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();
	
	// Start timer of this stage
	m_time.StartTime();
}
/******************************************************************************/
/*!
\brief - Update GameIntro's info
\param dt - delta time
*/
/******************************************************************************/
void GameIntro::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown GameIntro's info
*/
/******************************************************************************/
void GameIntro::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload GameIntro's json data
*/
/******************************************************************************/
void GameIntro::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
