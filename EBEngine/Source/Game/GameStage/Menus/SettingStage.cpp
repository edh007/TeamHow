/******************************************************************************/
/*!
\file   SettingStage.cpp
\author JeongJuyong
\par    email: jeykop14@gmail.com
\date   2017/04/09(yy/mm/dd)

\description
Contains SettingStage stage class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "SettingStage.h"
#include "../../../Engine/ObjectManager/ObjectManager.h"
/******************************************************************************/
/*!
\brief - SettingStage constructor
\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
SettingStage::SettingStage(GameStateManager* GSM, ObjectManager* OBM)
{
	m_GSM = GSM;
	m_OBM = OBM;
}

/******************************************************************************/
/*!
\brief - SettingStage destructor
*/
/******************************************************************************/
SettingStage::~SettingStage()
{}

/******************************************************************************/
/*!
\brief - Load SettingStage's json data
*/
/******************************************************************************/
void SettingStage::Load(void)
{
	//Bind basic systems
	m_OBM->BindGameSystem();

	// Load json data
	m_OBM->LoadStageData("Resource/Data/Stages/Menu/Setting.json");
}

/******************************************************************************/
/*!
\brief - Initialize SettingStage's info
*/
/******************************************************************************/
void SettingStage::Init(void)
{
	// Init basic systems
	m_OBM->InitGameSystem();
	
	// Start timer of this stage
	m_time.StartTime();
}
/******************************************************************************/
/*!
\brief - Update SettingStage's info
\param dt - delta time
*/
/******************************************************************************/
void SettingStage::Update(float dt)
{
	// Update basic systems
	m_OBM->UpdateGameSystem(dt);
}

/******************************************************************************/
/*!
\brief - Shutdown SettingStage's info
*/
/******************************************************************************/
void SettingStage::Shutdown(void)
{
	// Shutdown basic systems
	m_OBM->ShutdownGameSystem();
}

/******************************************************************************/
/*!
\brief - Unload SettingStage's json data
*/
/******************************************************************************/
void SettingStage::Unload(void)
{
	// Unload stage data
	m_OBM->UnloadStageData();
}
