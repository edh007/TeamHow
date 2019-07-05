/******************************************************************************/
/*!
\file   RegisterLogics.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/01(yy/mm/dd)

\description
Contains logics' headers and init logics builder function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _REGISTER_LOGICS_H_
#define _REGISTER_LOGICS_H_

#include <thread>
#include "LogicType.h"
#include "../../Engine/GameSystem/Logic/LogicFactory/LogicFactory.h"

#include "../../Game/GameLogic/Player/Slow.h"
#include "../../Game/GameLogic/Player/Player.h"
#include "../../Game/GameLogic/Player/SuperPower.h"
#include "../../Game/GameLogic/Player/Punch.h"

#include "../../Game/GameLogic/Tutorial/Tutorial.h"

#include "../../Game/GameLogic/HUD/Arrow.h"
#include "../../Game/GameLogic/HUD/HUD.h"
#include "../../Game/GameLogic/HUD/GameOver.h"
#include "../../Game/GameLogic/HUD/Grade.h"

#include "../../Game/GameLogic/Menus/MenuSelect.h"
#include "../../Game/GameLogic/Menus/MainScreen.h"
#include "../../Game/GameLogic/Menus/Setting.h"
#include "../../Game/GameLogic/Menus/Credit.h"
#include "../../Game/GameLogic/Menus/Splash.h"
#include "../../Game/GameLogic/Menus/HowToPlayLogic.h"

#include "../../Game/GameLogic/Basic/BasicControl.h"
#include "../../Game/GameLogic/Basic/FadeScreen.h"
#include "../../Game/GameLogic/Basic/CutScene.h"

#include "../../Game/GameLogic/Enemy/Enemy.h"
#include "../../Game/GameLogic/Enemy/Damage.h"

#include "../../Game/GameLogic/Trap/Alarm.h"
#include "../../Game/GameLogic/Trap/Web.h"
#include "../../Game/GameLogic/Trap/BasicTrap.h"
#include "../../Game/GameLogic/Trap/Laser.h"
#include "../../Game/GameLogic/Trap/Turret.h"
#include "../../Game/GameLogic/Trap/Lightning.h"
#include "../../Game/GameLogic/Trap/TurretTarget.h"

#include "../../Game/GameLogic/Particle/Normal.h"
#include "../../Game/GameLogic/Particle/ParticleManager.h"

#include "../../Game/GameLogic/Environment/NodeSettor.h"
#include "../../Game/GameLogic/Environment/Door.h"
#include "../../Game/GameLogic/Environment/OuterWall.h"
#include "../../Game/GameLogic/Environment/Fov.h"
#include "../../Game/GameLogic/Environment/Chopper.h"

#include "../../Game/GameLogic/Items/Bullet.h"
#include "../../Game/GameLogic/Items/Target.h"

/******************************************************************************/
/*!
\brief - Register logics.
		 User should customize this part manually!
*/
/******************************************************************************/
inline void RegisterLogics(void)
{
	//std::thread lc_thread[LOGIC_LOAD_END];

	//// Basic logics
	//lc_thread[BASIC_HUD] = std::thread(LogicFactory::AddBuilder, BASIC_HUD, new HUDBuilder);
	//lc_thread[OPENING] = std::thread(LogicFactory::AddBuilder, OPENING, new OpeningBuilder);
	//lc_thread[NODE_SETTOR] = std::thread(LogicFactory::AddBuilder, NODE_SETTOR, new NodeSettorBuilder);
	//lc_thread[SLOW] = std::thread(LogicFactory::AddBuilder, SLOW, new SlowBuilder);
	//lc_thread[BASIC_CONTROL] = std::thread(LogicFactory::AddBuilder, BASIC_CONTROL, new BasicControlBuilder);
	//lc_thread[BULLET] = std::thread(LogicFactory::AddBuilder, BULLET, new BulletBuilder);
	//lc_thread[PATHFINDING] = std::thread(LogicFactory::AddBuilder, PATHFINDING, new PathFindingBuilder);
	//lc_thread[GAMEOVER] = std::thread(LogicFactory::AddBuilder, GAMEOVER, new GameOverBuilder);
	//lc_thread[MENUSELECT] = std::thread(LogicFactory::AddBuilder, MENUSELECT, new MenuSelectBuilder);
	//lc_thread[MAINSCREEN] = std::thread(LogicFactory::AddBuilder, MAINSCREEN, new MainScreenBuilder);
	//lc_thread[FILEIO] = std::thread(LogicFactory::AddBuilder, FILEIO, new FileIOBuilder);

	//// Player logic
	//lc_thread[PLAYER] = std::thread(LogicFactory::AddBuilder, PLAYER, new PlayerBuilder);
	//lc_thread[SEARCH] = std::thread(LogicFactory::AddBuilder, SEARCH, new SearchBuilder);
	//lc_thread[FOOTSTEP] = std::thread(LogicFactory::AddBuilder, FOOTSTEP, new FootstepBuilder);
	//lc_thread[BATTLE] = std::thread(LogicFactory::AddBuilder, BATTLE, new BattleBuilder);

	//// Enemy logic
	//lc_thread[DAMAGE] = std::thread(LogicFactory::AddBuilder, DAMAGE, new DamageBuilder);
	//lc_thread[CHASE] = std::thread(LogicFactory::AddBuilder, CHASE, new ChaseBuilder);
	//lc_thread[PATROL] = std::thread(LogicFactory::AddBuilder, PATROL, new PatrolBuilder);
	//lc_thread[ENEMY] = std::thread(LogicFactory::AddBuilder, ENEMY, new EnemyBuilder);

	//// Trap logic
	//lc_thread[TRAP] = std::thread(LogicFactory::AddBuilder, TRAP, new BasicTrapBuilder);
	//lc_thread[WEB] = std::thread(LogicFactory::AddBuilder, WEB, new WebBuilder);
	//lc_thread[LASER] = std::thread(LogicFactory::AddBuilder, LASER, new LaserBuilder);
	//lc_thread[DOG] = std::thread(LogicFactory::AddBuilder, DOG, new DogBuilder);
	//lc_thread[GLASS] = std::thread(LogicFactory::AddBuilder, GLASS, new GlassBuilder);

	//lc_thread[NORMAL] = std::thread(LogicFactory::AddBuilder, NORMAL, new NormalBuilder);
	//lc_thread[PARTICLEMANAGER] = std::thread(LogicFactory::AddBuilder, PARTICLEMANAGER, new ParticleManagerBuilder);
	//lc_thread[TURRET] = std::thread(LogicFactory::AddBuilder, TURRET, new TurretBuilder);
	//lc_thread[FIST] = std::thread(LogicFactory::AddBuilder, FIST, new FistBuilder);

	//// Environment
	//lc_thread[DOOR] = std::thread(LogicFactory::AddBuilder, DOOR, new DoorBuilder);

	//// Items
	//lc_thread[TARGET] = std::thread(LogicFactory::AddBuilder, TARGET, new TargetBuilder);

	//for (int lc_num = 1; lc_num < LOGIC_LOAD_END; ++lc_num)
	//	if (lc_thread[lc_num].joinable())
	//		lc_thread[lc_num].join();

	LogicFactory::AddBuilder(SETTING, new SettingBuilder);
	LogicFactory::AddBuilder(CREDIT, new CreditBuilder);
	LogicFactory::AddBuilder(HOWTOPLAY, new HowToPlayLogicBuilder);

	LogicFactory::AddBuilder(ENEMY, new EnemyBuilder);
	LogicFactory::AddBuilder(DAMAGE, new DamageBuilder);

	LogicFactory::AddBuilder(SUPERPOWER, new SuperPowerBuilder);
	LogicFactory::AddBuilder(PLAYER, new PlayerBuilder);
	LogicFactory::AddBuilder(PUNCH, new PunchBuilder);

	LogicFactory::AddBuilder(FADE, new FadeScreenBuilder);
	LogicFactory::AddBuilder(MAINSCREEN, new MainScreenBuilder);
	LogicFactory::AddBuilder(CUTSCENE, new CutSceneBuilder);
	LogicFactory::AddBuilder(MENUSELECT, new MenuSelectBuilder);
    LogicFactory::AddBuilder(TUTORIAL, new TutorialBuilder);
	LogicFactory::AddBuilder(GAMEOVER, new GameOverBuilder);
    LogicFactory::AddBuilder(GRADE, new GradeBuilder);
	
	LogicFactory::AddBuilder(BASIC_CONTROL, new BasicControlBuilder);
	LogicFactory::AddBuilder(SLOW, new SlowBuilder);
	LogicFactory::AddBuilder(NODE_SETTOR, new NodeSettorBuilder);
	LogicFactory::AddBuilder(SPLASH, new SplashBuilder);
	LogicFactory::AddBuilder(BASIC_HUD, new HUDBuilder);
	LogicFactory::AddBuilder(ARROW, new ArrowBuilder);

	LogicFactory::AddBuilder(ALARM, new AlarmBuilder);
	LogicFactory::AddBuilder(CHOPPER, new ChopperBuilder);
	LogicFactory::AddBuilder(LASER, new LaserBuilder);
	LogicFactory::AddBuilder(WEB, new WebBuilder);
	LogicFactory::AddBuilder(BULLET, new BulletBuilder);
	LogicFactory::AddBuilder(TRAP, new BasicTrapBuilder);
	LogicFactory::AddBuilder(TURRETTARGET, new TurretTargetBuilder);
	LogicFactory::AddBuilder(LIGHTNING, new LightningBuilder);
	LogicFactory::AddBuilder(TURRET, new TurretBuilder);
	LogicFactory::AddBuilder(PARTICLEMANAGER, new ParticleManagerBuilder);
	LogicFactory::AddBuilder(NORMAL, new NormalBuilder);

	LogicFactory::AddBuilder(DOOR, new DoorBuilder);
	LogicFactory::AddBuilder(OUTER_WALL, new OuterWallBuilder);
	LogicFactory::AddBuilder(PLAYER_FOV, new FovBuilder);

	LogicFactory::AddBuilder(TARGET, new TargetBuilder);
}

#endif // _REGISTER_LOGICS_H_