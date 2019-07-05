/******************************************************************************/
/*!
\file   GameEnding.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/06/11(yy/mm/dd)

\description
Contains GameEnding stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "GameEnding.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"
/******************************************************************************/
/*!
\brief - GameEnding constructor
\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
GameEnding::GameEnding(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - GameEnding destructor
*/
/******************************************************************************/
GameEnding::~GameEnding()
{}

/******************************************************************************/
/*!
\brief - Load GameEnding's json data
*/
/******************************************************************************/
void GameEnding::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/CutScene/GameEnding.json");
}

/******************************************************************************/
/*!
\brief - Initialize GameEnding's info
*/
/******************************************************************************/
void GameEnding::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();
	
	// Start timer of this stage
	m_time.StartTime();
}
/******************************************************************************/
/*!
\brief - Update GameEnding's info
\param dt - delta time
*/
/******************************************************************************/
void GameEnding::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown GameEnding's info
*/
/******************************************************************************/
void GameEnding::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload GameEnding's json data
*/
/******************************************************************************/
void GameEnding::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
