/******************************************************************************/
/*!
\file   LV1.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/24(yy/mm/dd)

\description
Contains LV1 stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "../../../Engine/ObjectManager/ObjectManager.h"
#include "LV1.h"
/******************************************************************************/
/*!
\brief - LV1 constructor
\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
LV1Stage::LV1Stage(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}
/******************************************************************************/
/*!
\brief - LV1 destructor
*/
/******************************************************************************/
LV1Stage::~LV1Stage()
{

}
/******************************************************************************/
/*!
\brief - Load LV1's json data
*/
/******************************************************************************/
void LV1Stage::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/InGame/LV1.json");
}
/******************************************************************************/
/*!
\brief - Initialize LV1's info
*/
/******************************************************************************/
void LV1Stage::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();

	// Start timer of this stage
	m_time.StartTime();
}
/******************************************************************************/
/*!
\brief - Update LV1's info
\param dt - delta time
*/
/******************************************************************************/
void LV1Stage::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}
/******************************************************************************/
/*!
\brief - Shutdown LV1's info
*/
/******************************************************************************/
void LV1Stage::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload LV1's json data
*/
/******************************************************************************/
void LV1Stage::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
