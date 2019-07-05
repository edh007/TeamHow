/******************************************************************************/
/*!
\file   Audio.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/14(yy/mm/dd)

\description
Contains Audio class member and functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Audio.h"

/******************************************************************************/
/*!
\brief - Audio Constructor
\param system - pointer to fmod main system
*/
/******************************************************************************/
Audio::Audio(FMOD::System* system)
:m_system(system), m_channel(0), m_sound(0),
m_volume(0.5f), m_pause(false), m_play(true),
m_position(vec3()), m_velocity(vec3()), m_isPlaying(false)
{

}

/******************************************************************************/
/*!
\brief - Audio Destructor
*/
/******************************************************************************/
Audio::~Audio() 
{
	m_sound->release();
}

/******************************************************************************/
/*!
\brief - Play audio
*/
/******************************************************************************/
void Audio::Play(void)
{
	if (m_play)
		m_system->playSound(FMOD_CHANNEL_FREE, m_sound, false, &m_channel);

}

/******************************************************************************/
/*!
\brief - Stop audio
*/
/******************************************************************************/
void Audio::Stop(void)
{
	m_channel->stop();
}

/******************************************************************************/
/*!
\brief - Pause audio
\param boolean - toggle
*/
/******************************************************************************/
void Audio::Pause(bool boolean)
{
	m_channel->setPaused(boolean);
}

/******************************************************************************/
/*!
\brief - Check if the audio is playing or not
\param boolean - m_isPlaying
*/
/******************************************************************************/
bool Audio::IsPlaying(void)
{
	m_channel->isPlaying(&m_isPlaying);
	return m_isPlaying;
}

/******************************************************************************/
/*!
\brief - Set Mute Toggle
\param boolean - toggle
*/
/******************************************************************************/
void Audio::SetMuteToggle(bool toggle)
{
	m_play = toggle;
}

/******************************************************************************/
/*!
\brief - Get Mute Toggle
\return m_play
*/
/******************************************************************************/
bool Audio::GetMuteToggle(void) const
{
	return m_play;
}

/******************************************************************************/
/*!
\brief - Get Volume
\return m_volume
*/
/******************************************************************************/
float Audio::GetVolume(void) const
{
	return m_volume;
}

/******************************************************************************/
/*!
\brief - Set Volume
\param volume
*/
/******************************************************************************/
void Audio::SetVolume(float volume)
{
	m_volume = volume;
}

/******************************************************************************/
/*!
\brief - Set audio to replay
\param toggle
*/
/******************************************************************************/
void Audio::Replay(bool toggle)
{
	if (toggle)
		m_sound->setMode(FMOD_3D | FMOD_HARDWARE | FMOD_LOOP_NORMAL);

	else 
		m_channel->setMode(FMOD_3D | FMOD_HARDWARE | FMOD_LOOP_OFF);
}

/******************************************************************************/
/*!
\brief - Set audio's position
\param pos
*/
/******************************************************************************/
void Audio::SetPosition(const vec3 & pos)
{
	m_position = pos;

	m_positionFV.x = pos.x;
	m_positionFV.y = pos.y;
	m_positionFV.z = pos.z;
}

/******************************************************************************/
/*!
\brief - Set audio's velocity
\param vel
*/
/******************************************************************************/
void Audio::SetVelocity(const vec3 & vel)
{
	m_velocity = vel;

	m_velocityFV.x = vel.x;
	m_velocityFV.y = vel.y;
	m_velocityFV.z = vel.z;
}

/******************************************************************************/
/*!
\brief - Get audio's position
\return m_position
*/
/******************************************************************************/
const vec3& Audio::GetPosition(void) const
{
	return m_position;
}

/******************************************************************************/
/*!
\brief - Get audio's velocity
\return m_velocity
*/
/******************************************************************************/
const vec3& Audio::GetVelocity(void) const
{
	return m_velocity;
}

/******************************************************************************/
/*!
\brief - Get audio's velocity
\return m_velocity
*/
/******************************************************************************/
const FMOD_VECTOR & Audio::GetPositionFV(void) const
{
	return m_positionFV;
}

/******************************************************************************/
/*!
\brief - Get audio's velocity
\return m_velocity
*/
/******************************************************************************/
const FMOD_VECTOR & Audio::GetVelocityFV(void) const
{
	return m_velocityFV;
}

