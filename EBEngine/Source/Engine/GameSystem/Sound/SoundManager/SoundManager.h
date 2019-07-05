/******************************************************************************/
/*!
\file   SoundManager.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/26(yy/mm/dd)

\description
Contains SoundManager class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _SOUND_H_
#define _SOUND_H_

#include <unordered_map>
#include "FMOD/fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

class Audio;

//! type definition audio map
typedef std::unordered_map<std::string, std::string> SoundMap;

//! Sound manager class
class SoundManager
{

public:

	//! Basic functions
	SoundManager(void);
	~SoundManager(void);

	//! Manage fmod system and loaded sounds
	bool InitFMOD(int size);
	void AddSound(const char* key, const char* SoundDir);
	void ClearSoundMap(void);
	bool ErrorCheck(FMOD_RESULT result);
	SoundMap& GetSoundMap(void);

	FMOD::System*	GetSystem(void);
	FMOD::ChannelGroup* m_Cgroup;		// Audios' channel group

private:

	FMOD::System*		m_system;		// pointer to system
	FMOD::ChannelGroup* m_MasterGroup;	// Master channel group  
	
	SoundMap		m_soundMap;		// AudioMap

};

#endif // _SOUND_H_