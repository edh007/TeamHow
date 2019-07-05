/******************************************************************************/
/*!
\file   Tutorials_5.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/24(yy/mm/dd)

\description
Contains Tutorials_5 stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Tutorials_5.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"
/******************************************************************************/
/*!
\brief - Tutorials_5 constructor
\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
Tutorials_5::Tutorials_5(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - Tutorials_5 destructor
*/
/******************************************************************************/
Tutorials_5::~Tutorials_5()
{}

/******************************************************************************/
/*!
\brief - Load Tutorials_5's json data
*/
/******************************************************************************/
void Tutorials_5::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/Tutorial/Tutorials_5.json");
}

/******************************************************************************/
/*!
\brief - Initialize Tutorials_5's info
*/
/******************************************************************************/
void Tutorials_5::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();
	
	// Start timer of this stage
	m_time.StartTime();
}
/******************************************************************************/
/*!
\brief - Update Tutorials_5's info
\param dt - delta time
*/
/******************************************************************************/
void Tutorials_5::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown Tutorials_5's info
*/
/******************************************************************************/
void Tutorials_5::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload Tutorials_5's json data
*/
/******************************************************************************/
void Tutorials_5::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
