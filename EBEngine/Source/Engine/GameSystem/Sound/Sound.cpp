/******************************************************************************/
/*!
\file   Sound.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/26(yy/mm/dd)

\description
Contains Sound class member and functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Sound.h"
#include "Audio/Audio.h"
#include "../../StateManager/GameStateManager/GameStateManager.h"

/******************************************************************************/
/*!
\brief - Sound Constructor
\param GSM - pointer to gamestate manager
*/
/******************************************************************************/
Sound::Sound(GameStateManager* GSM)
: m_GSM(GSM), m_SM(GSM->GetSoundManager()),
m_system(GSM->GetSoundManager()->GetSystem()),
m_MasterToggle(true), m_MasterVolume(.5f)
{}

/******************************************************************************/
/*!
\brief - Sound Destructor
*/
/******************************************************************************/
Sound::~Sound(void)
{}

/******************************************************************************/
/*!
\brief - Initialize Sound 
*/
/******************************************************************************/
void Sound::Init(void)
{}

/******************************************************************************/
/*!
\brief - Update Sound
*/
/******************************************************************************/
void Sound::Update(void)
{
	// Set listener's info
	m_system->set3DListenerAttributes(1,
		&listener_positionFV, &listener_velocityFV,
		&listener_lookFV, &listener_upFV);
	
	//Update all audios' volume
	for (auto it = m_audioMap.begin();
		it != m_audioMap.end(); ++it)
	{
		Audio* audio = it->second;
		
		// Lower volume in pause menu...
		if (m_GSM->GetStageSize() > 1) {
			audio->m_channel->setVolume(audio->GetVolume() *.25f);
			
			if (m_GSM->GetGameData()->resumeBGM)
				m_GSM->GetGameData()->resumeBGM->m_channel->setVolume(
					m_GSM->GetGameData()->resumeBGM->GetVolume() * .25f);
		}

		else
			audio->m_channel->setVolume(audio->GetVolume());
		
		// Set distance
		FMOD_VECTOR distanceFV;

		// BGM always follow the player's position
		if (!strcmp((it->first).c_str(), "BGM")) {
			audio->SetPosition(listener_position);
			distanceFV.x = distanceFV.y = distanceFV.z = 0.f;

			// Replay all the time
			if (!it->second->IsPlaying())
				it->second->Play();
		}

		else {
			vec3 distance = (audio->GetPosition() - listener_position);

			// Top down setting
			distanceFV.x = distance.x;
			distanceFV.y = 0.f;
			distanceFV.z = -distance.y;

			// Platform setting
			/*distanceFV.x = distance.x;
			distanceFV.y = distance.y;
			distanceFV.z = distance.z;*/
		}

		audio->m_channel->set3DAttributes(&distanceFV, &(audio->GetVelocityFV()));
	}

	m_GSM->GetSoundManager()->GetSystem()->update();
}

/******************************************************************************/
/*!
\brief - Shutdown Sound
*/
/******************************************************************************/
void Sound::Shutdown(void)
{
	for (auto it = m_audioMap.begin();
		it != m_audioMap.end(); ++it)
		it->second->Stop();

	ClearAudios();
}

/******************************************************************************/
/*!
\brief - Add audio
\param key
*/
/******************************************************************************/
void Sound::AddAudio(const char * AudioKey, const char* ResourceKey)
{
	//Unless, make new builder
	if (m_audioMap.find(AudioKey) == m_audioMap.end())
	{
		m_audioMap[AudioKey] = new Audio(m_system);
		m_system->createSound(m_SM->GetSoundMap()[ResourceKey].c_str(), FMOD_3D | FMOD_HARDWARE, 0, &m_audioMap[AudioKey]->m_sound);
		m_audioMap[AudioKey]->m_channel->setChannelGroup(m_SM->m_Cgroup);
	}
}

/******************************************************************************/
/*!
\brief - Get audio
*/
/******************************************************************************/
Audio* Sound::GetAudio(const char* key)
{
	auto found = m_audioMap.find(key)->second;
	return found;
}

/******************************************************************************/
/*!
\brief - Clear audios
*/
/******************************************************************************/
void Sound::ClearAudios(void)
{
	for (auto it = m_audioMap.begin(); it != m_audioMap.end(); ++it)
		delete (*it).second;

	m_audioMap.clear();
}

/******************************************************************************/
/*!
\brief - Get audio map from sound system
\return m_audioMap
*/
/******************************************************************************/
AudioMap& Sound::GetAudioMap(void)
{
	return m_audioMap;
}

/******************************************************************************/
/*!
\brief - Set all audios' play toggle
\param toggle
*/
/******************************************************************************/
void Sound::SetMasterMuteToggle(bool toggle)
{
	m_MasterToggle = toggle;
	for (auto it = m_audioMap.begin();
		it != m_audioMap.end(); ++it)
		it->second->SetMuteToggle(m_MasterToggle);
}

/******************************************************************************/
/*!
\brief - Get master play toggle
\return m_MasterToggle
*/
/******************************************************************************/
bool  Sound::GetMasterMuteToggle(void) const
{
	return m_MasterToggle;
}

/******************************************************************************/
/*!
\brief - Set all audios' volume
\param volume
*/
/******************************************************************************/
void Sound::SetMasterVolume(float volume)
{
	m_MasterVolume = volume;
	for (auto it = m_audioMap.begin();
		it != m_audioMap.end(); ++it)
		it->second->m_channel->setVolume(m_MasterVolume);
}

/******************************************************************************/
/*!
\brief - Get master volume
\return m_MasterVolume
*/
/******************************************************************************/
float Sound::GetMasterVolume(void) const
{
	return m_MasterVolume;
}

/******************************************************************************/
/*!
\brief - Set listener's position
\param vel
*/
/******************************************************************************/
void Sound::SetListenerPosition(const vec3 & pos)
{
	listener_position = pos;

	listener_positionFV.x = pos.x;
	listener_positionFV.y = pos.y;
	listener_positionFV.z = pos.z;
}

/******************************************************************************/
/*!
\brief - Set listener's velocity
\param vel
*/
/******************************************************************************/
void Sound::SetListenerVelocity(const vec3 & vel)
{
	listener_velocity = vel;

	listener_velocityFV.x = vel.x;
	listener_velocityFV.y = vel.y;
	listener_velocityFV.z = vel.z;
}

/******************************************************************************/
/*!
\brief - Set listener's up and look
\param up
\param look
*/
/******************************************************************************/
void Sound::SetListenerUpnLook(const vec3 & up, const vec3 & look)
{
	listener_up = up;
	listener_look = look;

	listener_upFV.x = up.x;
	listener_upFV.y = up.y;
	listener_upFV.z = up.z;
	listener_lookFV.x = look.x;
	listener_lookFV.y = look.y;
	listener_lookFV.z = look.z;
}

/******************************************************************************/
/*!
\brief - Get listener's position
\return listener_position
*/
/******************************************************************************/
const vec3& Sound::GetListenerPosition(void) const
{
	return listener_position;
}

/******************************************************************************/
/*!
\brief - Get listener's velocity
\return listener_velocity
*/
/******************************************************************************/
const vec3& Sound::GetListenerVelocity(void) const
{
	return listener_velocity;
}

/******************************************************************************/
/*!
\brief - Get listener's up
\return listener_up
*/
/******************************************************************************/
const vec3& Sound::GetListenerUp(void) const
{
	return listener_up;
}

/******************************************************************************/
/*!
\brief - Get listener's  look
\return listener_look
*/
/******************************************************************************/
const vec3& Sound::GetListenerLook(void) const
{
	return listener_look;
}

/******************************************************************************/
/*!
\brief - Get listener's position
\return listener_position
*/
/******************************************************************************/
const FMOD_VECTOR& Sound::GetListenerPositionFV(void) const
{
	return listener_positionFV;
}

/******************************************************************************/
/*!
\brief - Get listener's velocity
\return listener_velocity
*/
/******************************************************************************/
const FMOD_VECTOR& Sound::GetListenerVelocityFV(void) const
{
	return listener_velocityFV;
}

/******************************************************************************/
/*!
\brief - Get listener's up
\return listener_up
*/
/******************************************************************************/
const FMOD_VECTOR& Sound::GetListenerUpFV(void) const
{
	return listener_upFV;
}

/******************************************************************************/
/*!
\brief - Get listener's  look
\return listener_look
*/
/******************************************************************************/
const FMOD_VECTOR& Sound::GetListenerLookFV(void) const
{
	return listener_lookFV;
}