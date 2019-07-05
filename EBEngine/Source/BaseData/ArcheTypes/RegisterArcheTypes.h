/******************************************************************************/
/*!
\file   RegisterArcheTypes.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/10/01(yy/mm/dd)

\description
Contains archertypes' headers and init archertypes builder function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _REGISTER_ARCHETYPES_H_
#define _REGISTER_ARCHETYPES_H_

#include <thread>
#include "../../Engine/ObjectManager/ObjectManager.h"

/******************************************************************************/
/*!
\brief - Build archertypes.
User should customize this part manually!
*/
/******************************************************************************/
inline void RegisterArcheTypes(void)
{
	//std::thread at_thread[AT_LOAD_END];
	//at_thread[AT_PLAYER] = std::thread(ObjectManager::AddArcheType, AT_PLAYER, "Resource/Data/ArcheType/Player.json");
	//at_thread[AT_ENEMY] = std::thread(ObjectManager::AddArcheType, AT_ENEMY, "Resource/Data/ArcheType/Enemy.json");
	/*at_thread[AT_WEB] = std::thread(ObjectManager::AddArcheType, AT_WEB, "Resource/Data/ArcheType/Web.json");
	at_thread[AT_LASER] = std::thread(ObjectManager::AddArcheType, AT_LASER, "Resource/Data/ArcheType/Laser.json");
	at_thread[AT_DOG] = std::thread(ObjectManager::AddArcheType, AT_DOG, "Resource/Data/ArcheType/Dog.json");
	at_thread[AT_TURRET] = std::thread(ObjectManager::AddArcheType, AT_TURRET, "Resource/Data/ArcheType/Turret.json");
	at_thread[AT_GLASS] = std::thread(ObjectManager::AddArcheType, AT_GLASS, "Resource/Data/ArcheType/Glass.json");
	at_thread[AT_BOMB] = std::thread(ObjectManager::AddArcheType, AT_BOMB, "Resource/Data/ArcheType/Bomb.json");
	at_thread[AT_AFTERIMAGE] = std::thread(ObjectManager::AddArcheType, AT_AFTERIMAGE, "Resource/Data/ArcheType/AfterImage.json");
	at_thread[AT_LANTERN] = std::thread(ObjectManager::AddArcheType, AT_LANTERN, "Resource/Data/ArcheType/Lantern.json");
	at_thread[AT_TARGET] = std::thread(ObjectManager::AddArcheType, AT_TARGET, "Resource/Data/ArcheType/Target.json");
	at_thread[AT_DOOR] = std::thread(ObjectManager::AddArcheType, AT_DOOR, "Resource/Data/ArcheType/Door.json");
	at_thread[AT_BACKGROUND] = std::thread(ObjectManager::AddArcheType, AT_BACKGROUND, "Resource/Data/ArcheType/Background.json");
	at_thread[AT_WALL] = std::thread(ObjectManager::AddArcheType, AT_WALL, "Resource/Data/ArcheType/Wall.json");
	at_thread[AT_GAMEOVER] = std::thread(ObjectManager::AddArcheType, AT_GAMEOVER, "Resource/Data/ArcheType/GameOver.json");
	for (int at_num = 1; at_num < AT_LOAD_END; ++at_num)
		if (at_thread[ArcheType(at_num)].joinable())
			at_thread[ArcheType(at_num)].join();*/

	// Register archtypes
	ObjectManager::AddArcheType(AT_PLAYER, "Resource/Data/ArcheType/Player/Player.json");

	// Enemies
	ObjectManager::AddArcheType(AT_ENEMY, "Resource/Data/ArcheType/Enemy/Enemy.json");
	
	// Traps
	ObjectManager::AddArcheType(AT_WEB, "Resource/Data/ArcheType/Trap/Web.json");
	ObjectManager::AddArcheType(AT_LASER, "Resource/Data/ArcheType/Trap/Laser.json");
	ObjectManager::AddArcheType(AT_TURRET, "Resource/Data/ArcheType/Trap/Turret.json");
	ObjectManager::AddArcheType(AT_ALARM, "Resource/Data/ArcheType/Trap/Alarm.json");
    
	// Visual Effects
	ObjectManager::AddArcheType(AT_BOMB, "Resource/Data/ArcheType/Bomb.json");
	ObjectManager::AddArcheType(AT_AFTERIMAGE, "Resource/Data/ArcheType/AfterImage.json");
	ObjectManager::AddArcheType(AT_LANTERN, "Resource/Data/ArcheType/Lantern.json");

	// Environments
	ObjectManager::AddArcheType(AT_TARGET, "Resource/Data/ArcheType/Environment/Target.json");
	ObjectManager::AddArcheType(AT_DOOR, "Resource/Data/ArcheType/Environment/Door.json");
	ObjectManager::AddArcheType(AT_BACKGROUND, "Resource/Data/ArcheType/Environment/Background.json");
	ObjectManager::AddArcheType(AT_FLOOR, "Resource/Data/ArcheType/Environment/Floor.json");
	ObjectManager::AddArcheType(AT_WALL, "Resource/Data/ArcheType/Environment/Wall.json");

	ObjectManager::AddArcheType(AT_GAMEOVER, "Resource/Data/ArcheType/GameOver.json");
}

#endif // _REGISTER_ARCHETYPES_H_