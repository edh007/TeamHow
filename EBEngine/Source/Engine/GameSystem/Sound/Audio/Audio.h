/******************************************************************************/
/*!
\file   Audio.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/03(yy/mm/dd)

\description
Contains Audio class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "../SoundManager/SoundManager.h"
#include "../../../Utilities/Math/MathUtils.h"

//! Audio class
class Audio
{
public:

	//! Constructor and destructor
	Audio(FMOD::System* system = 0);
	~Audio();

	void Play(void);
	void Stop(void);
	void Pause(bool boolean);
	bool IsPlaying(void);

	//! Manage mute toggle
	bool GetMuteToggle(void) const;
	void SetMuteToggle(bool toggle);

	//! Manage volume
	float GetVolume(void) const;
	void SetVolume(float volume);

	void Replay(bool toggle);

	FMOD::Channel* m_channel;	// Fmod channel
	FMOD::Sound* m_sound;		// Fmod sound

	void SetPosition(const vec3& pos);
	void SetVelocity(const vec3& vel);
	const vec3& GetPosition(void) const;
	const vec3& GetVelocity(void) const;

	const FMOD_VECTOR& GetPositionFV(void) const;
	const FMOD_VECTOR& GetVelocityFV(void) const;

private:

	bool m_isPlaying;
	float m_volume;
	bool  m_pause;
	bool  m_play;
	vec3  m_velocity, m_position;
	FMOD::System*	m_system;
	FMOD_VECTOR		m_velocityFV, m_positionFV;

};

#endif // _AUDIO_H_