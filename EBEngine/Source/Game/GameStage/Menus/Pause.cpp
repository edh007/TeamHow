/******************************************************************************/
/*!
\file   Pause.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Pause's class functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "../../../Engine/ObjectManager/ObjectManager.h"
#include "Pause.h"

/******************************************************************************/
/*!
\brief - PauseStage constructor
\param GSM - pointer to the gams state manager
*/
/******************************************************************************/
PauseStage::PauseStage(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - PauseStage destructor
*/
/******************************************************************************/
PauseStage::~PauseStage()
{

}

/******************************************************************************/
/*!
\brief - Load PauseStage's json data
*/
/******************************************************************************/
void PauseStage::Load(void)
{
	// Bind basic systems
	m_OBM->BindGameSystem();
	
	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/Menu/Pause.json");
}

/******************************************************************************/
/*!
\brief - Initialize PauseStage's info
*/
/******************************************************************************/
void PauseStage::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();

	// Start timer of this stage
	m_time.StartTime();
}

/******************************************************************************/
/*!
\brief - Update PauseStage's info
\param dt - delta time
*/
/******************************************************************************/
void PauseStage::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown PauseStage's info
*/
/******************************************************************************/
void PauseStage::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload PauseStage's json data
*/
/******************************************************************************/
void PauseStage::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
