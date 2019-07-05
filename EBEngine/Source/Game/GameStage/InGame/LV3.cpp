/******************************************************************************/
/*!
\file   LV3.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/24(yy/mm/dd)

\description
Contains LV3 stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "LV3.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"


/******************************************************************************/
/*!
\brief - LV3 constructor
\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
LV3::LV3(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - LV3 destructor
*/
/******************************************************************************/
LV3::~LV3()
{}

/******************************************************************************/
/*!
\brief - Load LV3's json data
*/
/******************************************************************************/
void LV3::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/InGame/LV3.json");
}

/******************************************************************************/
/*!
\brief - Initialize LV3's info
*/
/******************************************************************************/
void LV3::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();

	// Start timer of this stage
	m_time.StartTime();
}

/******************************************************************************/
/*!
\brief - Update LV3's info
\param dt - delta time
*/
/******************************************************************************/
void LV3::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown LV3's info
*/
/******************************************************************************/
void LV3::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload LV3's json data
*/
/******************************************************************************/
void LV3::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
