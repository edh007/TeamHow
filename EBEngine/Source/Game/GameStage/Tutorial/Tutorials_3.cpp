/******************************************************************************/
/*!
\file   Tutorials_3.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/24(yy/mm/dd)

\description
Contains Tutorials_3 stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Tutorials_3.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"
/******************************************************************************/
/*!
\brief - Tutorials_3 constructor
\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
Tutorials_3::Tutorials_3(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - Tutorials_3 destructor
*/
/******************************************************************************/
Tutorials_3::~Tutorials_3()
{}

/******************************************************************************/
/*!
\brief - Load Tutorials_3's json data
*/
/******************************************************************************/
void Tutorials_3::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/Tutorial/Tutorials_3.json");
}

/******************************************************************************/
/*!
\brief - Initialize Tutorials_3's info
*/
/******************************************************************************/
void Tutorials_3::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();
	
	// Start timer of this stage
	m_time.StartTime();
}
/******************************************************************************/
/*!
\brief - Update Tutorials_3's info
\param dt - delta time
*/
/******************************************************************************/
void Tutorials_3::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown Tutorials_3's info
*/
/******************************************************************************/
void Tutorials_3::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload Tutorials_3's json data
*/
/******************************************************************************/
void Tutorials_3::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
