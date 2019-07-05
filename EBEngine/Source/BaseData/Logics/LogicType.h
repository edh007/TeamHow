/******************************************************************************/
/*!
\file   LogicType.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/09/10(yy/mm/dd)

\description
Contains Logictypr function.

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _LOGICTYPE_H_
#define _LOGICTYPE_H_

#include <string>

enum LogicType {NONE_LOGIC,

	// Basic app utility
	MENUSELECT, MAINSCREEN, /*FILEIO,*/ TUTORIAL,
	SPLASH, BASIC_CONTROL, FADE, SETTING, CREDIT,
	CUTSCENE, HOWTOPLAY,

	// Ingame logic
	SLOW, NODE_SETTOR, BASIC_HUD, GAMEOVER, GRADE,
	
	// Player logic
	PLAYER, PUNCH, SUPERPOWER,

	// Environment logic
	TARGET, DOOR, ARROW, OUTER_WALL,
	PLAYER_FOV, CHOPPER,

	// Enemy logic
	BULLET, WEB, ENEMY, DAMAGE,
	
	// Trap logic
	TRAP, LASER,  ALARM, TURRET, LIGHTNING,
	TURRETTARGET,
	NORMAL, PARTICLEMANAGER, 
	WINDOW,

	LOGIC_END
};

/******************************************************************************/
/*!
\brief - Convert sring key to enum(Logic type).
User should customize this part manually!
*/
/******************************************************************************/
inline LogicType LogicTypeConverter(const std::string& key)
{
	// Basic logis
	if (key == "BASIC_CONTROL")
		return BASIC_CONTROL;
	else if (key == "SPLASH")
		return SPLASH;
	else if (key == "HUD")
		return BASIC_HUD;
	else if (key == "OUTER_WALL")
		return OUTER_WALL;
	else if (key == "SLOW")
		return SLOW;
	else if (key == "GAMEOVER")
		return GAMEOVER;
    else if (key == "GRADE")
        return GRADE;
	else if (key == "CUTSCENE")
		return CUTSCENE;
	else if (key == "HOWTOPLAY")
		return HOWTOPLAY;
	else if (key == "NODESETTOR")
		return 	NODE_SETTOR;
	else if (key == "FADE")
		return 	FADE;
	else if (key == "SETTING")
		return 	SETTING;
	else if (key == "CREDIT")
		return 	CREDIT;

	// Player info
	else if (key == "PLAYER")
		return PLAYER;
	else if (key == "SUPERPOWER")
		return SUPERPOWER;
	else if (key == "PUNCH")
		return PUNCH;

	// Enemy Type
	else if (key == "ENEMY")
		return ENEMY;
	else if (key == "DAMAGE")
		return DAMAGE;

	// Trap Type
	else if (key == "ALARM")
		return ALARM;
	else if (key == "TRAP")
		return TRAP;
	else if (key == "LASER")
		return LASER;
	else if (key == "WEB")
		return WEB;
    else if (key == "NORMAL")
		return NORMAL;
	else if (key == "TURRET")
		return TURRET;
	else if (key == "LIGHTNING")
		return LIGHTNING;
	else if (key == "TURRETTARGET")
		return TURRETTARGET;
	else if (key == "TARGET")
		return TARGET;
	else if (key == "MENUSELECT")
		return MENUSELECT;
	else if (key == "MAINSCREEN")
		return MAINSCREEN;
    else if (key == "TUTORIAL")
        return TUTORIAL;
    else if (key == "PARTICLEMANAGER")
        return PARTICLEMANAGER;

	// Environment
	else if (key == "WINDOW")
		return WINDOW;
	else if (key == "DOOR")
		return DOOR;
	else if (key == "ARROW")
		return ARROW;
	else if (key == "PLAYER_FOV")
		return PLAYER_FOV;

	else
		return NONE_LOGIC;
};

#endif //_LOGICTYPE_H_