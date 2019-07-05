/******************************************************************************/
/*!
\file   SoundManager.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/26(yy/mm/dd)

\description
Contains SoundManager's class member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "SoundManager.h"
#include "../Audio/Audio.h"
#include "../../../Utilities/Debug/Debug.h"

/******************************************************************************/
/*!
\brief - SoundManager Constructor
*/
/******************************************************************************/
SoundManager::SoundManager(void)
:m_system(nullptr)
{}

/******************************************************************************/
/*!
\brief - SoundManager Destructor
*/
/******************************************************************************/
SoundManager::~SoundManager(void)
{
	ClearSoundMap();
	m_system->release();
	m_system->close();
}

/******************************************************************************/
/*!
\brief - Initialize SoundManager
\param pApp - pointer to application
\param size - The number of sound to load
*/
/******************************************************************************/
bool SoundManager::InitFMOD(int size)
{
	FMOD::System_Create(&m_system);
	FMOD_RESULT result = m_system->init(size * 100, FMOD_INIT_NORMAL, 0);
	m_system->createChannelGroup("Cgroup", &m_Cgroup);
	m_system->getMasterChannelGroup(&m_MasterGroup);
	m_MasterGroup->addGroup(m_Cgroup);
	m_system->set3DSettings(100.f, 100.f, 100.f);
	
	return ErrorCheck(result);
}

/******************************************************************************/
/*!
\brief - Check sound's error
\param pApp - pointer to application
\param result - function's result
*/
/******************************************************************************/
bool SoundManager::ErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		MessageBox(nullptr, "Failed to init basic sound system.",
			"FMOD Error", MB_OK);
		return false;
	}

	return true;
}

/******************************************************************************/
/*!
\brief - Get fmod's m_system
\return m_system
*/
/******************************************************************************/
FMOD::System* SoundManager::GetSystem(void)
{
	return m_system;
}

/******************************************************************************/
/*!
\brief - Get pointer to sound
\param key - sound key
\param SoundDir - sound type
*/
/******************************************************************************/
void SoundManager::AddSound(const char* key, const char* SoundDir)
{
	//Unless, make new builder
	m_soundMap[key] = SoundDir;
}

/******************************************************************************/
/*!
\brief - Clear sound map
*/
/******************************************************************************/
void SoundManager::ClearSoundMap(void)
{
	m_soundMap.clear();
}

/******************************************************************************/
/*!
\brief - Get Audio Map
\return m_audioMap
*/
/******************************************************************************/
SoundMap& SoundManager::GetSoundMap(void)
{
	return m_soundMap;
}