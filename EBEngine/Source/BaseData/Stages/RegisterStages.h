/******************************************************************************/
/*!
\file   RegisterStage.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains stages' headers and init stages builder function
This will be called at application files

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _REGISTER_STAGES_H_
#define _REGISTER_STAGES_H_

#include <thread>
#include "../../Engine/StateManager/StageFactory/StageFactory.h"

#include "../../Game/GameStage/Menus/Pause.h"
#include "../../Game/GameStage/Menus/MainMenu.h"
#include "../../Game/GameStage/Menus/SplashStage.h"
#include "../../Game/GameStage/Menus/SettingStage.h"
#include "../../Game/GameStage/Menus/CreditStage.h"
#include "../../Game/GameStage/Menus/HowToPlay.h"

#include "../../Game/GameStage/InGame/LV1.h"
#include "../../Game/GameStage/InGame/LV2.h"
#include "../../Game/GameStage/InGame/LV3.h"
#include "../../Game/GameStage/InGame/LV4.h"
#include "../../Game/GameStage/InGame/LV5.h"

#include "../../Game/GameStage/Tutorial/Tutorials_1.h"
#include "../../Game/GameStage/Tutorial/Tutorials_2.h"
#include "../../Game/GameStage/Tutorial/Tutorials_3.h"
#include "../../Game/GameStage/Tutorial/Tutorials_4.h"
#include "../../Game/GameStage/Tutorial/Tutorials_5.h"
#include "../../Game/GameStage/Tutorial/Tutorials_6.h"

#include "../../Game/GameStage/CutScene/GameIntro.h"
#include "../../Game/GameStage/CutScene/GameEnding.h"

/******************************************************************************/
/*!
\brief - Register stages.
User should customize this part manually!
*/
/******************************************************************************/
inline void RegisterStages(void)
{
	//std::thread st_thread[ST_END];

	//// Register stages
	//st_thread[ST_MENU] = std::thread(StageFactory::AddBuilder, ST_MENU, new MainMenuBuilder);
	//st_thread[ST_LV1] = std::thread(StageFactory::AddBuilder, ST_LV1, new LV1Builder);
	//st_thread[ST_LV2] = std::thread(StageFactory::AddBuilder, ST_LV2, new LV2Builder);
	//st_thread[ST_LV3] = std::thread(StageFactory::AddBuilder, ST_LV3, new LV3Builder);
	//st_thread[ST_LV4] = std::thread(StageFactory::AddBuilder, ST_LV4, new LV4Builder);
	//st_thread[ST_PAUSE] = std::thread(StageFactory::AddBuilder, ST_PAUSE, new PauseBuilder);
	//st_thread[ST_SPLASH] = std::thread(StageFactory::AddBuilder, ST_SPLASH, new SplashBuilder);

	//for (int st_num = 0; st_num < ST_END; ++st_num)
	//	if (st_thread[st_num].joinable())
	//		st_thread[st_num].join();

	// Ingame
	StageFactory::AddBuilder(ST_LV1, new LV1Builder);
	StageFactory::AddBuilder(ST_LV2, new LV2Builder);
	StageFactory::AddBuilder(ST_LV3, new LV3Builder);
	StageFactory::AddBuilder(ST_LV4, new LV4Builder);
	StageFactory::AddBuilder(ST_LV5, new LV5Builder);

	// Menus
	StageFactory::AddBuilder(ST_MENU, new MainMenuBuilder);
	StageFactory::AddBuilder(ST_CREDIT, new CreditStageBuilder);
	StageFactory::AddBuilder(ST_SETTING, new SettingStageBuilder);
	StageFactory::AddBuilder(ST_PAUSE, new PauseBuilder);
	StageFactory::AddBuilder(ST_SPLASH, new SplashStageBuilder);
	StageFactory::AddBuilder(ST_HTP, new HowToPlayBuilder);

	// Tutorials
	StageFactory::AddBuilder(ST_TUTORIALS_1, new Tutorials_1Builder);
	StageFactory::AddBuilder(ST_TUTORIALS_2, new Tutorials_2Builder);
	StageFactory::AddBuilder(ST_TUTORIALS_3, new Tutorials_3Builder);
	StageFactory::AddBuilder(ST_TUTORIALS_4, new Tutorials_4Builder);
	StageFactory::AddBuilder(ST_TUTORIALS_5, new Tutorials_5Builder);
	StageFactory::AddBuilder(ST_TUTORIALS_6, new Tutorials_6Builder);

	StageFactory::AddBuilder(ST_INTRO, new GameIntroBuilder);
	StageFactory::AddBuilder(ST_ENDING, new GameEndingBuilder);
}

#endif //_REGISTER_STAGES_H_