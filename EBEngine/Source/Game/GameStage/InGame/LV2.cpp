/******************************************************************************/
/*!
\file   LV2.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/24(yy/mm/dd)

\description
Contains LV2 stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "LV2.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"

/******************************************************************************/
/*!
\brief - LV2 constructor
\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
LV2::LV2(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - LV2 destructor
*/
/******************************************************************************/
LV2::~LV2()
{}

/******************************************************************************/
/*!
\brief - Load LV2's json data
*/
/******************************************************************************/
void LV2::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/InGame/LV2.json");
}

/******************************************************************************/
/*!
\brief - Initialize LV2's info
*/
/******************************************************************************/
void LV2::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();
	
	// Start timer of this stage
	m_time.StartTime();
}

/******************************************************************************/
/*!
\brief - Update LV2's info
\param dt - delta time
*/
/******************************************************************************/
void LV2::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown LV2's info
*/
/******************************************************************************/
void LV2::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload LV2's json data
*/
/******************************************************************************/
void LV2::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
