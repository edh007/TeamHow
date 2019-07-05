/******************************************************************************/
/*!
\file   ObjectManager.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains ObjectManager's class
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <set>
#include <stack>
#include <unordered_map>
#include "../Utilities/Json/JsonParser.h"
#include "../../BaseData/Logics/LogicType.h"

class Audio;
class Sound;
class Scene;
class Logic;
class World;
class Texture;
class GameStateManager;

//! type definition for maps and set
typedef std::set<int> RemoveList;
typedef std::unordered_map<int, Object*> ObjectMap;
typedef std::unordered_map<std::string, Audio*> AudioMap;
typedef std::unordered_map<std::string, Texture*> TextureMap;
typedef std::unordered_map <ArcheType, std::string> ArchetypeMap;

//! ObjectManager class
class ObjectManager
{
public:
	
	//! Constructor and Destructoer
	ObjectManager(GameStateManager* GSM);
	~ObjectManager();

	//! Functions manages objects
	void GetObjects(ArcheType type, std::vector<Object*>& list);
	void GetObjects(LogicType type, std::vector<Object*>& list);
	Object* GetGameObject(const int id);

	// Object managing functions
	Object* AddObject(Object* Obj);
	Object* AddObject(ArcheType type);
	bool HasObject(const int id);
	void RemoveObject(const int id);
	void SaveOBM(void);
	void LoadOBM(void);

	//! Manage list
	void ClearObjectMap(void);
	const ObjectMap& GetObjectMap(void) const;

	//! Manage main system
	void BindGameSystem(void);
	void LoadStageData(char* dir);
	void InitGameSystem(void);
	void UpdateGameSystem(float dt);
	void ShutdownGameSystem(void);
	void UnloadStageData(void);

	//! Game System gettor
	Scene* GetGameScene(void) const;
	World* GetGameWorld(void) const;
	Logic* GetGameLogic(void) const;
	Sound* GetGameSound(void) const;
	GameStateManager* GetGSM(void);

	// Asset map caller
	Texture* GetTexture(const char* key);
	Audio* GetAudio(const char* key);

	// Object id settor
	const int GetNextID(void);
	const int GetObjectAmount(void) const;

	// Archetype managing functions
	static void AddArcheType(ArcheType type, const char* file);
	static bool HasArcheType(ArcheType type);
	Object* GetArhceType(ArcheType type);
	static void ClearArcheTypes(void);

private:

	void RemoveObjects(void);

	//! Game systems
	Scene* pScene;
	World* pWorld;
	Logic* pLogic;
	Sound* pSound;

	AudioMap* pAudioMap;		//! Audio asset map from sound system
	TextureMap* pTextureMap;	//! artasset asset map from graphic system

	int id_settor;				//! Id settor
	JsonParser m_StageLoader;	//! Json Parser
	JsonParser m_ATLoader;		//! ArcheType Parser
	ObjectMap m_ObjectList;		//! Sprites info

	GameStateManager* m_GSM;	//! Pointer to GameStateManager
	RemoveList m_RemoveList;	//! Object list to delete after 1 frame

	static ArchetypeMap m_ATMap;	//! List holds pre-set prototypes

	struct PauseInfo {
		ObjectMap	m_PauseList;	//! Sprites info
		Scene*		pResumeScene;
		World*		pResumeWorld;
		Logic*		pResumeLogic;
		Sound*		pResumeSound;
	};

	typedef std::stack<PauseInfo> ResumeStack;

	PauseInfo	m_pauseInfo;
	ResumeStack m_PauseStack;
};

#endif //_OBJECTMANAGER_H_