/******************************************************************************/
/*!
\file   Tutorials_1.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/24(yy/mm/dd)

\description
Contains Tutorials_1 stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Tutorials_1.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"
/******************************************************************************/
/*!
\brief - Tutorials_1 constructor
\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
Tutorials_1::Tutorials_1(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - Tutorials_1 destructor
*/
/******************************************************************************/
Tutorials_1::~Tutorials_1()
{}

/******************************************************************************/
/*!
\brief - Load Tutorials_1's json data
*/
/******************************************************************************/
void Tutorials_1::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/Tutorial/Tutorials_1.json");
}

/******************************************************************************/
/*!
\brief - Initialize Tutorials_1's info
*/
/******************************************************************************/
void Tutorials_1::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();
	
	// Start timer of this stage
	m_time.StartTime();
}
/******************************************************************************/
/*!
\brief - Update Tutorials_1's info
\param dt - delta time
*/
/******************************************************************************/
void Tutorials_1::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown Tutorials_1's info
*/
/******************************************************************************/
void Tutorials_1::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload Tutorials_1's json data
*/
/******************************************************************************/
void Tutorials_1::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
