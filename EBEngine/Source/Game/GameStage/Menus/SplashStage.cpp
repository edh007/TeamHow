/******************************************************************************/
/*!
\file   SplashStage.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/11/15(yy/mm/dd)

\description
Contains SplashStage stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "SplashStage.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"

/******************************************************************************/
/*!
\brief - SplashStage constructor
\param GSM - pointer to the gams state manager
*/
/******************************************************************************/
SplashStage::SplashStage(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - SplashStage destructor
*/
/******************************************************************************/
SplashStage::~SplashStage()
{}

/******************************************************************************/
/*!
\brief - Load SplashStage's json data
*/
/******************************************************************************/
void SplashStage::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/Menu/Splash.json");
}

/******************************************************************************/
/*!
\brief - Initialize SplashStage's info
*/
/******************************************************************************/
void SplashStage::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();

	// Start timer of this stage
	m_time.StartTime();
}

/******************************************************************************/
/*!
\brief - Update SplashStage's info
\param dt - delta time
*/
/******************************************************************************/
void SplashStage::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown SplashStage's info
*/
/******************************************************************************/
void SplashStage::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload SplashStage's json data
*/
/******************************************************************************/
void SplashStage::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
