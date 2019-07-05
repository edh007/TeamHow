/******************************************************************************/
/*!
\file   Tutorials_6.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/24(yy/mm/dd)

\description
Contains Tutorials_6 stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Tutorials_6.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"
/******************************************************************************/
/*!
\brief - Tutorials_6 constructor
\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
Tutorials_6::Tutorials_6(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - Tutorials_6 destructor
*/
/******************************************************************************/
Tutorials_6::~Tutorials_6()
{}

/******************************************************************************/
/*!
\brief - Load Tutorials_6's json data
*/
/******************************************************************************/
void Tutorials_6::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/Tutorial/Tutorials_6.json");
}

/******************************************************************************/
/*!
\brief - Initialize Tutorials_6's info
*/
/******************************************************************************/
void Tutorials_6::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();
	
	// Start timer of this stage
	m_time.StartTime();
}
/******************************************************************************/
/*!
\brief - Update Tutorials_6's info
\param dt - delta time
*/
/******************************************************************************/
void Tutorials_6::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown Tutorials_6's info
*/
/******************************************************************************/
void Tutorials_6::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload Tutorials_6's json data
*/
/******************************************************************************/
void Tutorials_6::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
