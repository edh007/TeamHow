/******************************************************************************/
/*!
\file   HowToPlay.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/06/08(yy/mm/dd)

\description
Contains HowToPlay stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "HowToPlay.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"
/******************************************************************************/
/*!
\brief - HowToPlay constructor
\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
HowToPlay::HowToPlay(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - HowToPlay destructor
*/
/******************************************************************************/
HowToPlay::~HowToPlay()
{}

/******************************************************************************/
/*!
\brief - Load HowToPlay's json data
*/
/******************************************************************************/
void HowToPlay::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/Menu/HowToPlay.json");
}

/******************************************************************************/
/*!
\brief - Initialize HowToPlay's info
*/
/******************************************************************************/
void HowToPlay::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();
	
	// Start timer of this stage
	m_time.StartTime();
}
/******************************************************************************/
/*!
\brief - Update HowToPlay's info
\param dt - delta time
*/
/******************************************************************************/
void HowToPlay::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown HowToPlay's info
*/
/******************************************************************************/
void HowToPlay::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload HowToPlay's json data
*/
/******************************************************************************/
void HowToPlay::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
