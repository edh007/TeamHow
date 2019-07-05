/******************************************************************************/
/*!
\file   LV5.cpp
\author DonghoLee
\par    email: edongho007@gmail.com
\date   2017/06/13(yy/mm/dd)

\description
Contains LV5 stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "LV5.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"
/******************************************************************************/
/*!
\brief - LV5 constructor
\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
LV5::LV5(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - LV5 destructor
*/
/******************************************************************************/
LV5::~LV5()
{}

/******************************************************************************/
/*!
\brief - Load LV5's json data
*/
/******************************************************************************/
void LV5::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/InGame/LV5.json");
}

/******************************************************************************/
/*!
\brief - Initialize LV5's info
*/
/******************************************************************************/
void LV5::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();
	
	// Start timer of this stage
	m_time.StartTime();
}
/******************************************************************************/
/*!
\brief - Update LV5's info
\param dt - delta time
*/
/******************************************************************************/
void LV5::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown LV5's info
*/
/******************************************************************************/
void LV5::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload LV5's json data
*/
/******************************************************************************/
void LV5::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
