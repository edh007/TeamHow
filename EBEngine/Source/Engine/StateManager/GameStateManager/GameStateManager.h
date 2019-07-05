/******************************************************************************/
/*!
\file   GameStageManager.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains GameStageManager's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <stack>
#include <windows.h>
#include "../../../BaseData/GameData.h"
#include "../../../BaseData/Stages/StageType.h"
#include "../..//Utilities/Time.h"

using namespace Resolution;

//! forward declaration
class Stage;
class GLManager;
class Application;
class StageBuilder;
class SoundManager;

//! Stage stack information
struct StageInfo
{
	//! Stage stack's info
	StageType stage;
	Stage* pStage;
};
typedef std::stack<StageInfo> StageStack;
typedef std::stack<StageType> ResumeStack;

/******************************************************************************/
/*!
\class GameManager

Class used to manage all stages in the game.  Allows users to set the next
stage, restart or quit.

*/
/******************************************************************************/
class GameStateManager
{
public:

	// Constructor and Destructor
	GameStateManager(Application * pApp);
	~GameStateManager();

	/*For use in Main*/
	void Init(void);
	void Update(void);
	void Shutdown(void);

	/*Manage Stages*/
	bool IsPausing(void) const;
	bool IsQuitting(void) const;
	bool IsResuming(void) const;
	void SetNextStage(StageType stageType);
	void Pause(StageType nextStage);
	void ResumeRestart(void);
	void ResumeNextStage(StageType stageType);
	void Restart(bool isRestarted);
	void SetQuit(bool isQuitting);
	void Resume(void);
	void SetFirstStage(StageType first);
	StageType GetCurrentState(void) const;
	StageType GetNextState(void) const;
	int GetFrameCounter(void) const;
	const Timer& GetStageTimer(void) const;
	unsigned GetStageSize(void) const;

	//! Manage resolution
	ScreenSize GetResolution(void);
	void SetResolution(const ScreenSize& res);

	//! Manage window mode
	void SetFullScreen(bool scr);
	bool GetFullScreen(void) const;

	//! Pointer to app gettor
	Application* GetAppPtr(void);
	GLManager* GetGLManager(void);
	SoundManager* GetSoundManager(void);

	// Get global game data
	GameData* GetGameData(void) const;

private:

	void ProccessMessages(void);		
	void HandlingInterruption(void);	//!< Handle the app iterruption
	void TriggerInputController(void);	//!< Triggered Input Controller
	void ChangeGameState(void);			//!< Changed the current stage

	bool m_isPausing;		//!< To control if the game is pausing.
	bool m_isResuming;		//!< To control if the game is resuming.
	bool m_isQuitting;      //!< To control if the game is quitting.
	bool m_isRestarting;    //!< To control if the stage should restart.
	bool m_isResumeNext;	//!< To control if the game is resuming and change the stage.
	bool m_isResumeRestart;	//!< To control if the game is resuming and restart the stage.

	StageInfo	m_paused;	//!< A pointer to the pause stage
	Stage*		m_pStage;   //!< A pointer to the current stage
	
	StageType	m_next;     //!< The next stage to switch to
	StageType	m_current;  //!< The current stage to update
	StageType   m_1stStage;	//!< The 1st stage of this application

	ResumeStack m_ResumeStack;	//!< The resume stack to return

	GameData*		m_gameData;	//!< Game data to be used
	Application*	m_pApp;		//!< pointer to the application
	GLManager*		m_GLM;		//!< pointer to the gl manager
	SoundManager*	m_SM;		//!< pointer to the sound manager

	float m_dt;					//!< delta time
	Timer m_timer;				//!< stage timer
	int m_frameCounter;			//!< frame counter
	StageStack m_StageStack;	//!< stage stack
	StageStack m_PauseStack;	//!< pause stage stack
};

#endif //end GAME_MANAGER_H



