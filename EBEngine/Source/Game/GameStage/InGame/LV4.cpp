/******************************************************************************/
/*!
\file   LV4.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/24(yy/mm/dd)

\description
Contains LV4 stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "LV4.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"

/******************************************************************************/
/*!
\brief - LV4 constructor
\param GSM - pointer to the gams state manager
*/
/******************************************************************************/
LV4::LV4(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - LV4 destructor
*/
/******************************************************************************/
LV4::~LV4()
{}

/******************************************************************************/
/*!
\brief - Load LV4's json data
*/
/******************************************************************************/
void LV4::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/InGame/LV4.json");
}

/******************************************************************************/
/*!
\brief - Initialize LV4's info
*/
/******************************************************************************/
void LV4::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();

	// Start timer of this stage
	m_time.StartTime();
}

/******************************************************************************/
/*!
\brief - Update LV4's info
\param dt - delta time
*/
/******************************************************************************/
void LV4::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown LV4's info
*/
/******************************************************************************/
void LV4::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload LV4's json data
*/
/******************************************************************************/
void LV4::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
