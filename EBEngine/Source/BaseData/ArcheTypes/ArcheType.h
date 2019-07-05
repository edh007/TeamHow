/******************************************************************************/
/*!
\file   ArcheType.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/09/25(yy/mm/dd)

\description
Contains header files(ArcheType) to provide users base engine

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _ARCHETYPE_HEADER_
#define _ARCHETYPE_HEADER_

#include <string>

enum ArcheType{AT_NONE, 

	// Basic archetype
	AT_NODE, AT_NODESETTOR, AT_FADE,
	AT_HUD, AT_TUTORIAL, AT_FILEIO,
	AT_GAMEOVER, AT_FLOOR, AT_MENU,
	AT_MOUSE, AT_CREDIT, AT_CONFIRM,

	// Player
	AT_PLAYER, AT_PUNCH, AT_FOOT,

	// Enemy
	AT_ENEMY, AT_FOV, AT_BULLET, AT_EFIST,

	// Environment
	AT_BACKGROUND, AT_DOOR, AT_CHOPPER,
	AT_TARGET, AT_FOG, AT_WALL, AT_WINDOW,

	// Trap
	AT_TURRET, AT_ALARM,
	AT_WEB, AT_AIM,

	// Others...
	AT_GLASS, AT_LASER,
	AT_BOMB, AT_AFTERIMAGE, AT_LANTERN,
	
	AT_END
};

/******************************************************************************/
/*!
\brief - Convert sring key to enum(ArcheType).
User should customize this part manually!
*/
/******************************************************************************/
inline ArcheType ArcheTypeConverter (const std::string& key)
{
	// Default archetype
	if (key == "NONE")
		return AT_NONE;

	// Player
	else if (key == "PLAYER")
		return AT_PLAYER;

	// Enemy
	else if (key == "ENEMY")
		return AT_ENEMY;

	// Trap
	else if (key == "ALARM")
		return AT_ALARM;
    else if (key == "LASER")
        return AT_LASER;
    else if (key == "TURRET")
        return AT_TURRET;
    else if (key == "AIM")
        return AT_AIM;
    else if (key == "WEB")
        return AT_WEB;

	// Effect
    else if (key == "BOMB")
        return AT_BOMB;
    else if (key == "AFTERIMAGE")
        return AT_AFTERIMAGE;
    else if (key == "LANTERN")
        return AT_LANTERN;

	// Environment type
	else if (key == "WALL")
		return AT_WALL;
	else if (key == "DOOR")
		return AT_DOOR;
	else if (key == "WINDOW")
		return AT_WINDOW;
	else if (key == "BACKGROUND")
		return AT_BACKGROUND;
	else if (key == "FOG")
		return AT_FOG;
	else if (key == "FLOOR")
		return AT_FLOOR;

	// Items
	else if (key == "TARGET")
		return AT_TARGET;

	// Other hud
	else if (key == "GAMEOVER")
		return AT_GAMEOVER;
	else if (key == "MENU")
		return AT_MENU;
	else if (key == "HUD")
		return AT_HUD;
	else if (key == "TUTORIAL")
		return 	AT_TUTORIAL;
	else if (key == "FILEIO")
		return 	AT_FILEIO;
	else if (key == "NODESETTOR")
		return 	AT_NODESETTOR;
	else if (key == "CREDIT")
		return 	AT_CREDIT;

	// Default
	else
		return AT_NONE;
}

#endif //_ARCHETYPE_HEADER_
