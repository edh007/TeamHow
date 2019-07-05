/******************************************************************************/
/*!
\file   Tutorials_2.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/24(yy/mm/dd)

\description
Contains Tutorials_2 stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Tutorials_2.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"
/******************************************************************************/
/*!
\brief - Tutorials_2 constructor
\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
Tutorials_2::Tutorials_2(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - Tutorials_2 destructor
*/
/******************************************************************************/
Tutorials_2::~Tutorials_2()
{}

/******************************************************************************/
/*!
\brief - Load Tutorials_2's json data
*/
/******************************************************************************/
void Tutorials_2::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/Tutorial/Tutorials_2.json");
}

/******************************************************************************/
/*!
\brief - Initialize Tutorials_2's info
*/
/******************************************************************************/
void Tutorials_2::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();
	
	// Start timer of this stage
	m_time.StartTime();
}
/******************************************************************************/
/*!
\brief - Update Tutorials_2's info
\param dt - delta time
*/
/******************************************************************************/
void Tutorials_2::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown Tutorials_2's info
*/
/******************************************************************************/
void Tutorials_2::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload Tutorials_2's json data
*/
/******************************************************************************/
void Tutorials_2::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
