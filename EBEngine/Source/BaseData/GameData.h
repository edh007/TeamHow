/******************************************************************************/
/*!
\file   GameData.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains stage type, game data, resolution for screen size

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include "../Engine/Utilities/Math/MathUtils.h"

class Object;
class Audio;

/*! This game data will be used! */
struct GameData
{
	// delta time
	float dt;

	// Cheat toggle
	bool immortal, silent;

	// Setting info
	float volume;
	vec2 resolution;
	Audio* resumeBGM;
	bool quitApp, gameEnded, restart;

	// Camera
	vec3 cameraPos;
	float camera_y;

	// Mouse
	int mouseID;
	bool onMenuMouse;

	// Keyboard
	bool menuKeyPressed;

	// Menu Screen
	int menuSelection;
	bool confirm;

	// Tutorial toggle
	bool unlockSearch, unlockTM;

	// Main chracter's info
	Object* player, *fist;
	int player_id, player_death, player_condition, player_lastCondition, player_frame, player_point;
    bool player_Active, searchToggle, tmToggle, sprPnchParticleTog, pnchTog,
		player_chopper, frameRange, grade_Fade, enoughPoint, clicked;
	vec3 player_pos;
	float player_searchDist, footstack, dtPower;

	// Trap Toggle
	bool radarToggle;

	// For Gradings
	float timeElapsed, sneakTime, dashTime, gradeTime;
	int sneakKill, dashKill, killedEnemies;

	// FOG viewsight range
	float realViewSight;
	bool fogToggle;

	// Game Over Condition
	bool gameoverCondition;

	// Game Clear Condition
    bool gameclearCondition;
	bool gamenextCondition;
    bool gamegradeCondition;

	// XBOX Condition
	bool xboxVibToggle;
	float xboxVibIntnsty;

	// Using for target
	bool createTablet;

};

/*! This resolutions are standard for this engine! */
namespace Resolution{

	//Resolution Setup
	struct ScreenSize
	{
		int width;
		int height;

		bool operator == (const ScreenSize rhs) {
			return (width == rhs.width && rhs.height == height);
		};

		bool operator != (const ScreenSize rhs) {
			return (width != rhs.width || rhs.height != height);
		};
	};

	const ScreenSize SCR_640X480{ 640, 480 };
	const ScreenSize SCR_800X600{ 800, 600 };
	const ScreenSize SCR_1024X768{ 1024, 768 };
	const ScreenSize SCR_1280X1024{ 1280, 1024 };
	const ScreenSize SCR_1920X1080{ 1920, 1080 };

};

#endif // _GAMEDATA_H_