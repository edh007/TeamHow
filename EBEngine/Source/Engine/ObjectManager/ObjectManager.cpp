/******************************************************************************/
/*!
\file   ObjectManager.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains ObjectManager's class and member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include <algorithm>
#include "ObjectManager.h"
#include "Object/Object.h"
#include "../GameSystem/Sound/Sound.h"
#include "../GameSystem/Logic/Logic.h"
#include "../GameSystem/Graphic/Scene/Scene.h"
#include "../GameSystem/Physics/World/World.h"
#include "../GameSystem/Logic/GameLogic/GameLogic.h"
#include "../GameSystem/Graphic/GraphicManager/GLManager.h"
#include "../StateManager/GameStateManager/GameStateManager.h"

//! Init static PrototypeList map
ArchetypeMap ObjectManager::m_ATMap;

/******************************************************************************/
/*!
\brief - ObjectManager Constructor
*/
/******************************************************************************/
ObjectManager::ObjectManager(GameStateManager* GSM)
:m_GSM(GSM), id_settor(0), 
pScene(nullptr), pWorld(nullptr), pLogic(nullptr), pSound(nullptr),
pTextureMap(nullptr), pAudioMap(nullptr)
{}

/******************************************************************************/
/*!
\brief - ObjectManager Destructor
*/
/******************************************************************************/
ObjectManager::~ObjectManager(void)
{}

/******************************************************************************/
/*!
\brief - Add Object to the list
\param type - new sprite
*/
/******************************************************************************/
Object* ObjectManager::AddObject(Object* Obj)
{
	//Push it into the list
	auto found = m_ObjectList.find(Obj->GetID());

	m_ObjectList.insert(ObjectMap::value_type(
		Obj->GetID(), Obj));

	// Init logics
	if (pLogic)
		for (auto it = Obj->GetLogicList().begin();
			it != Obj->GetLogicList().end(); ++it)
		(*it).second->Init();

	// Add to the drawing list
	if (pScene 
		&& (Obj->HasComponent(CT_SPRITE) ||
			Obj->HasComponent(CT_TEXT) ||
			Obj->HasComponent(CT_PARTICLE)))
		pScene->AddSprite(Obj);

	// Add to the body list
	if (pWorld && Obj->HasComponent(CT_RIGIDBODY))
		pWorld->AddRigidBody(Obj);

	return Obj;
}

/******************************************************************************/
/*!
\brief - Add Object to the list
\param type - new sprite
*/
/******************************************************************************/
Object* ObjectManager::AddObject(ArcheType type)
{
	if (type == AT_NONE ||
		m_ATMap.find(type) == m_ATMap.end())
		return nullptr;

	// Get saved archetype
	else
	{
		// Load that info
		auto found = m_ATMap.find(type)->second;
		m_ATLoader.Load(const_cast<char*>(found.c_str()));

		// Make new object and add to the list
		return AddObject(m_ATLoader.LoadArcheType(this, type));
	}
}

/******************************************************************************/
/*!
\brief - Delete Object from the list
\param SpriteID - sprite's id
*/
/******************************************************************************/
void ObjectManager::RemoveObject(const int id)
{
	//If there is id that client to find,
	if (pScene)
		pScene->RemoveSprite(id);
	if (pWorld)
		pWorld->RemoveBody(id);

	m_RemoveList.insert(id);
}

/******************************************************************************/
/*!
\brief - Save the systems and obm's current condition
*/
/******************************************************************************/
void ObjectManager::SaveOBM(void)
{
	// Save info to the rStack
	m_PauseStack.push(m_pauseInfo);
	std::swap(m_PauseStack.top().m_PauseList, m_ObjectList);
	m_PauseStack.top().pResumeLogic = pLogic;
	m_PauseStack.top().pResumeScene = pScene;
	m_PauseStack.top().pResumeSound = pSound;
	m_PauseStack.top().pResumeWorld = pWorld;
}

/******************************************************************************/
/*!
\brief - Load the systems and obm's saved condition
*/
/******************************************************************************/
void ObjectManager::LoadOBM(void)
{
	// Check if there are stack in pause stack
	if (m_PauseStack.size()) {
		// Load the saved info
		std::swap(m_PauseStack.top().m_PauseList, m_ObjectList);
		pLogic = m_PauseStack.top().pResumeLogic;
		pScene = m_PauseStack.top().pResumeScene;
		pSound = m_PauseStack.top().pResumeSound;
		pWorld = m_PauseStack.top().pResumeWorld;

		// Init the rStack
		m_PauseStack.top().m_PauseList.clear();
		m_PauseStack.top().pResumeLogic = 0;
		m_PauseStack.top().pResumeScene = 0;
		m_PauseStack.top().pResumeSound = 0;
		m_PauseStack.top().pResumeWorld = 0;
		m_PauseStack.pop();
	}
}

/******************************************************************************/
/*!
\brief - Check if list has the obhect or not
\param SpriteID - sprite's id
*/
/******************************************************************************/
bool ObjectManager::HasObject(const int id)
{
	//Get object
	auto it = m_ObjectList.find(id);

	//Compare the id from user input
	if (it != m_ObjectList.end())
		return true;

	return false;
}

/******************************************************************************/
/*!
\brief - Clear Object List
*/
/******************************************************************************/
void ObjectManager::ClearObjectMap(void)
{
	//Remove the all objects in the lsit
	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end(); )
	{
		// Normally remove objs
		if (it->second->GetRemoveToggle())
			RemoveObject((it++)->second->GetID());

		// If obj to be remain, don't remove
		else
		{
			// But if app's to be quit, remove anyway 
			if (m_GSM->IsQuitting())
				RemoveObject((it++)->second->GetID());

			// unless, just pass
			else
				it++;
		}
	}

	RemoveObjects();
}

/******************************************************************************/
/*!
\brief - Get Sprite List
\return m_ObjectList
*/
/******************************************************************************/
const ObjectMap& ObjectManager::GetObjectMap(void) const
{
	//return the list
	return m_ObjectList;
}

/******************************************************************************/
/*!
\brief - Bind scene and world
\param pApp - pointer to app to bind to scene
*/
/******************************************************************************/
void ObjectManager::BindGameSystem(void)
{
	id_settor = m_ObjectList.size();

	pSound = new Sound(m_GSM);
	pWorld = new World(m_GSM);
	pScene = new Scene(m_GSM);
	pLogic = new Logic(this);

	// Get audio map form sound system
	pAudioMap = &pSound->GetAudioMap();
	pTextureMap = &m_GSM->GetGLManager()->GetTextureMap();
}

/******************************************************************************/
/*!
\brief - Load stage info and init
\param dir - Json file;s directory to load stage info
*/
/******************************************************************************/
void ObjectManager::LoadStageData(char* dir)
{
	m_StageLoader.Load(dir);
	m_StageLoader.InitLoadedData(this);
}

/******************************************************************************/
/*!
\brief - Initialize scene and world
*/
/******************************************************************************/
void ObjectManager::InitGameSystem(void)
{
	// Initialize game system
	pLogic->Init();
	pWorld->Init();
	pScene->Init();
	pSound->Init();
}

/******************************************************************************/
/*!
\brief - Update scene and world
*/
/******************************************************************************/
void ObjectManager::UpdateGameSystem(float dt)
{
	// Update game system
	pLogic->Update(dt);
	pWorld->Update(dt);
	pScene->Update(dt);
	pSound->Update();

	// Remove objects to be deleted
	// every 1 frame
	RemoveObjects();
}

/******************************************************************************/
/*!
\brief - Shutdown scene and world
*/
/******************************************************************************/
void ObjectManager::ShutdownGameSystem(void)
{
	//Shutdown basic trunks
	if (pScene)
		pScene->Shutdown();

	if (pWorld)
		pWorld->Shutdown();

	if (pLogic)
		pLogic->Shutdown();

	if (pSound)
		pSound->Shutdown();

	//Delete dynamic scene, world
	delete pScene;
	delete pWorld;
	delete pSound;

	pScene = 0;
	pWorld = 0;
	pSound = 0;
}

/******************************************************************************/
/*!
\brief - Unload stage info
*/
/******************************************************************************/
void ObjectManager::UnloadStageData(void)
{
	if (pLogic)
		pLogic->Unload();

	//Delete dynamic logic
	delete pLogic;
	pLogic = 0;

	// Clear object list
	ClearObjectMap();
}

/******************************************************************************/
/*!
\brief - Get pointer to the scene
\return pScene
*/
/******************************************************************************/
Scene* ObjectManager::GetGameScene(void) const
{
	return pScene;
}

/******************************************************************************/
/*!
\brief - Get pointer to the world
\return pWorld
*/
/******************************************************************************/
World* ObjectManager::GetGameWorld(void) const
{
	return pWorld;
}

/******************************************************************************/
/*!
\brief - Get pointer to the Sound
\return soundPtr
*/
/******************************************************************************/
Sound* ObjectManager::GetGameSound(void) const
{
	return pSound;
}

/******************************************************************************/
/*!
\brief - Get pointer to the Logic
\return pLogic
*/
/******************************************************************************/
Logic* ObjectManager::GetGameLogic(void) const
{
	return pLogic;
}

/******************************************************************************/
/*!
\brief - Get pointer to m_GSM
\return m_GSM
*/
/******************************************************************************/
GameStateManager* ObjectManager::GetGSM(void)
{
	return m_GSM;
}

/******************************************************************************/
/*!
\brief - Get audio
\param key
*/
/******************************************************************************/
Texture* ObjectManager::GetTexture(const char* key)
{
	return pTextureMap->find(key)->second;
}

/******************************************************************************/
/*!
\brief - Get audio
\param key
*/
/******************************************************************************/
Audio* ObjectManager::GetAudio(const char* key)
{
	return pSound->GetAudio(key); 
}

/******************************************************************************/
/*!
\brief - Get next sprite's id
\return id_settor
*/
/******************************************************************************/
const int ObjectManager::GetNextID(void)
{
	return id_settor++;
}

/******************************************************************************/
/*!
\brief - Get next sprite's id
\return m_ObjectList.size()
*/
/******************************************************************************/
const int ObjectManager::GetObjectAmount(void) const
{
	return m_ObjectList.size();
}

/******************************************************************************/
/*!
\brief - Remove objs booked on the list
*/
/******************************************************************************/
void ObjectManager::RemoveObjects(void)
{
	if (m_RemoveList.size())
	{
		for (auto it = m_RemoveList.begin(); it != m_RemoveList.end(); )
		{
			// Find the one to remove
			auto found = m_ObjectList.find(*it);

			//Delete it
			if (found != m_ObjectList.end())
			{
				delete found->second;
				found->second = 0;
				m_ObjectList.erase(*it++);
			}

			else
				it++;
		}

		m_RemoveList.clear();
	}
}

/******************************************************************************/
/*!
\brief - Build archetype
\param type - archetype to pre-build
\param file - directory
*/
/******************************************************************************/
void ObjectManager::AddArcheType(ArcheType type, const char* file)
{
	auto found = m_ATMap.find(type);
	if (found == m_ATMap.end())
	{
		// Insert
		m_ATMap.insert(
			ArchetypeMap::value_type(
				type, file));
	}
}

/******************************************************************************/
/*!
\brief - Check if there is specific archetype
\param type
\return bool
*/
/******************************************************************************/
bool ObjectManager::HasArcheType(ArcheType type)
{
	//Get object
	auto it = m_ATMap.find(type);

	//Compare the id from user input
	if (it != m_ATMap.end())
		return true;

	return false;
}

/******************************************************************************/
/*!
\brief - Get archetype object
\return Pointer to obj
*/
/******************************************************************************/
Object* ObjectManager::GetArhceType(ArcheType type)
{
	auto found = m_ATMap.find(type)->second;
	JsonParser tempLoader;
	tempLoader.Load(const_cast<char*>(found.c_str()));
	return tempLoader.LoadArcheType(this, type);
}

/******************************************************************************/
/*!
\brief - Remove all archetypes
*/
/******************************************************************************/
void ObjectManager::ClearArcheTypes(void)
{
	m_ATMap.clear();
}

/******************************************************************************/
/*!
\brief - Get Sprite from the OBM
\param type - sprite's archeType
\param list - list to store objs
*/
/******************************************************************************/
void ObjectManager::GetObjects(ArcheType type, std::vector<Object*>& list)
{
	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end(); ++it)
		if ((*it).second && ((*it).second->GetArcheType() == type))
			list.push_back((*it).second);
}

/******************************************************************************/
/*!
\brief - Get Sprite from the OBM
\param type - sprite's logicType
\param list - list to store objs
*/
/******************************************************************************/
void ObjectManager::GetObjects(LogicType type, std::vector<Object*>& list)
{
	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end(); ++it)
		if ((*it).second && ((*it).second->HasLogic(type)))
			list.push_back((*it).second);
}

/******************************************************************************/
/*!
\brief - Get Sprite from the OBM
\param id - sprite's archeType
*/
/******************************************************************************/
Object* ObjectManager::GetGameObject(const int id)
{
	auto found = m_ObjectList.find(id);

	// if found one is in the list,
	// return it
	if (found != m_ObjectList.end())
		return found->second;

	// if not, return 0
	return nullptr;
}