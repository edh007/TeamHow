/******************************************************************************/
/*!
\file   MainMenu.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains MainMenu's class functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "MainMenu.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"

/******************************************************************************/
/*!
\brief - MenuStage constructor
\param GSM - pointer to the gams state manager
*/
/******************************************************************************/
MenuStage::MenuStage(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - MenuStage destructor
*/
/******************************************************************************/
MenuStage::~MenuStage()
{

}

/******************************************************************************/
/*!
\brief - Load MenuStage's json data
*/
/******************************************************************************/
void MenuStage::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/Menu/Main.json");
}

/******************************************************************************/
/*!
\brief - Initialize MenuStage's info
*/
/******************************************************************************/
void MenuStage::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();

	// Start timer of this stage
	m_time.StartTime();
}

/******************************************************************************/
/*!
\brief - Update MenuStage's info
\param dt - delta time
*/
/******************************************************************************/
void MenuStage::Update(float dt)
{	
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown MenuStage's info
*/
/******************************************************************************/
void MenuStage::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload MenuStage's json data
*/
/******************************************************************************/
void MenuStage::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
