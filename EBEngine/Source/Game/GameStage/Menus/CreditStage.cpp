/******************************************************************************/
/*!
\file   CreditStage.cpp
\author JeongJuyong
\par    email: jeykop14@gmail.com
\date   2017/04/09(yy/mm/dd)

\description
Contains CreditStage stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "CreditStage.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"
/******************************************************************************/
/*!
\brief - CreditStage constructor
\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
CreditStage::CreditStage(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - CreditStage destructor
*/
/******************************************************************************/
CreditStage::~CreditStage()
{}

/******************************************************************************/
/*!
\brief - Load CreditStage's json data
*/
/******************************************************************************/
void CreditStage::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/Menu/Credit.json");
}

/******************************************************************************/
/*!
\brief - Initialize CreditStage's info
*/
/******************************************************************************/
void CreditStage::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();
	
	// Start timer of this stage
	m_time.StartTime();
}
/******************************************************************************/
/*!
\brief - Update CreditStage's info
\param dt - delta time
*/
/******************************************************************************/
void CreditStage::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown CreditStage's info
*/
/******************************************************************************/
void CreditStage::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload CreditStage's json data
*/
/******************************************************************************/
void CreditStage::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
