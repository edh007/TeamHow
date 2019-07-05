/******************************************************************************/
/*!
\file   Tutorials_4.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/24(yy/mm/dd)

\description
Contains Tutorials_4 stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Tutorials_4.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"
/******************************************************************************/
/*!
\brief - Tutorials_4 constructor
\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
Tutorials_4::Tutorials_4(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - Tutorials_4 destructor
*/
/******************************************************************************/
Tutorials_4::~Tutorials_4()
{}

/******************************************************************************/
/*!
\brief - Load Tutorials_4's json data
*/
/******************************************************************************/
void Tutorials_4::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/Tutorial/Tutorials_4.json");
}

/******************************************************************************/
/*!
\brief - Initialize Tutorials_4's info
*/
/******************************************************************************/
void Tutorials_4::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();
	
	// Start timer of this stage
	m_time.StartTime();
}
/******************************************************************************/
/*!
\brief - Update Tutorials_4's info
\param dt - delta time
*/
/******************************************************************************/
void Tutorials_4::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown Tutorials_4's info
*/
/******************************************************************************/
void Tutorials_4::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload Tutorials_4's json data
*/
/******************************************************************************/
void Tutorials_4::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
