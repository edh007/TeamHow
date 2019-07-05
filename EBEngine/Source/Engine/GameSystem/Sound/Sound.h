/******************************************************************************/
/*!
\file   Sound.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/26(yy/mm/dd)

\description
Contains Sound class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "SoundManager/SoundManager.h"
#include "../../Utilities/Math/MathUtils.h"

class GameStateManager;

//! type definition audio map
typedef std::unordered_map<std::string, Audio*> AudioMap;

//! Sound system class
class Sound{

public:

	//! Basic functions
	Sound(GameStateManager* GSM);
	~Sound(void);

	//! Loop functions
	void Init(void);
	void Update(void);
	void Shutdown(void);

	void AddAudio(const char* AudioKey, const char* ResourceKey);
	Audio* GetAudio(const char* key);
	void ClearAudios(void);
	AudioMap& GetAudioMap(void);

	void SetMasterMuteToggle(bool toggle);
	bool  GetMasterMuteToggle(void) const;
	
	void SetMasterVolume(float volume);
	float GetMasterVolume(void) const;
	
	void SetListenerPosition(const vec3& pos);
	void SetListenerVelocity(const vec3& vel);
	void SetListenerUpnLook(const vec3& up, const vec3& look);

	const vec3& GetListenerPosition(void) const;
	const vec3& GetListenerVelocity(void) const;
	const vec3& GetListenerUp(void) const;
	const vec3& GetListenerLook(void) const;

	const FMOD_VECTOR& GetListenerPositionFV(void) const;
	const FMOD_VECTOR& GetListenerVelocityFV(void) const;
	const FMOD_VECTOR& GetListenerUpFV(void) const;
	const FMOD_VECTOR& GetListenerLookFV(void) const;

private:

	GameStateManager* m_GSM;
	SoundManager* m_SM;

	// Range of vulume is 0.f < v < 1.f
	float m_MasterVolume;
	bool m_MasterToggle;

	FMOD::System*	m_system;
	AudioMap		m_audioMap;

	// user position attributes
	vec3 listener_position, listener_velocity, listener_up, listener_look;
	FMOD_VECTOR listener_positionFV, listener_velocityFV, listener_upFV, listener_lookFV;
};