/******************************************************************************/
/*!
\file   StageType.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/10/01(yy/mm/dd)

\description
Contains stages types

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _STAGES_TYPE_H_
#define _STAGES_TYPE_H_

/*! Enum of all stage types in the game */
enum  StageType {

    // Tutorials
    ST_TUTORIALS_1,
    ST_TUTORIALS_2,
    ST_TUTORIALS_3,
    ST_TUTORIALS_4,
    ST_TUTORIALS_5,
    ST_TUTORIALS_6,

    // Ingame
    ST_LV1,
    ST_LV2,
    ST_LV3,
    ST_LV4,
	ST_LV5,

	// Menus
	ST_MENU,
	ST_CREDIT,
	ST_SETTING,
	ST_PAUSE,
	ST_SPLASH,
	ST_HTP,

	// CutScenes
	ST_INTRO,
	ST_ENDING,

	ST_END
};

#endif //_STAGES_TYPE_H_