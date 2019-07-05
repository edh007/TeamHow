/******************************************************************************/
/*!
\file   GameStageManager.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains GameStageManager's class and member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "../BaseStage.h"
#include "GameStateManager.h"
#include "../../App/Application.h"
#include "../StageFactory/StageFactory.h"
#include "../../InputManager/InputManager.h"
#include "../../InputManager/XboxInput.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../GameSystem/Graphic/GraphicManager/GLManager.h"

/******************************************************************************/
/*!
\brief - GameStateManager's Constructor
*/
/******************************************************************************/
GameStateManager::GameStateManager(Application* pApp)
	:m_pApp(pApp), m_GLM(nullptr), m_SM(nullptr), m_gameData(nullptr), 
	m_frameCounter(0), m_isResumeNext(false), m_isResumeRestart(false),
	m_isPausing(false), m_pStage(nullptr), m_isResuming(false),
	m_isQuitting(false), m_isRestarting(false)
{}

/******************************************************************************/
/*!
\brief - GameStateManager's Destructor
*/
/******************************************************************************/
GameStateManager::~GameStateManager()
{
	//Pop every stack
	while (!m_StageStack.empty())
		m_StageStack.pop();

	delete m_paused.pStage;
	m_paused.pStage = 0;

 	delete m_pStage;
	m_pStage = 0;

	// Delete gamedata
	delete m_gameData;
	m_gameData = 0;
}

/******************************************************************************/
/*!
\brief - Function that will initialize the GameStateManager data.
\return - NONE
*/
/******************************************************************************/
void GameStateManager::Init(void)
{
	m_GLM = m_pApp->GetGLM();
	m_SM = m_pApp->GetSM();

	//Init GSM info
	m_gameData = new GameData();
	m_gameData->dt = 0;

	m_current = m_next = m_1stStage;
}
/******************************************************************************/
/*!
\brief - Main game loop that controls Stage switching.
\return - NONE
*/
/******************************************************************************/
void GameStateManager::Update(void)
{
	int counter = 0;
	float dt_Stack = 0.f;
	m_gameData->dt = 0;
	m_timer.StartTime();

	// If gms is on resuming, nothing to init again
	if (!m_isResuming)
	{
		// if we are not restarting, we need to change stages
		// but if this refresh is for pausing stage,
		// no need to change stage
		if (!m_isRestarting && !m_isPausing)
			ChangeGameState();

		// If restarted once, then shut the toggle down
		else if (m_isRestarting) m_isRestarting = false;

		// If paused once, then shut the toggle down
		else if (m_isPausing) m_isPausing = false;

		//Load Init current stage
		m_StageStack.top().pStage->Load();
		m_StageStack.top().pStage->Init();
	}

	else {
		m_isResuming = false;
		m_isResumeNext = false;
		if (m_isResumeRestart) {
			m_isResumeRestart = false;
			m_isRestarting = true;
		}
	}
	// Vsync
	// This does control the frame rate per second
	wglSwapIntervalEXT(1);

	//Update stage in a loop until a stage change/quit/restart is requested.
	while (!m_isQuitting && !m_isRestarting && m_current == m_next
		&& !m_isPausing && !m_isResuming)
	{	
		HandlingInterruption();

		m_dt = m_gameData->dt;
		m_timer.StartTime();	// Start timer per a frame

        XboxInput::Instance()->Update(m_dt);		//Update the Xbox Controller // XBOX
		ProccessMessages();							// Proccess Messages
		m_StageStack.top().pStage->Update(m_dt);	// Update the top stack stage with game data
		TriggerInputController();					//Triggered Input Controller

        XboxInput::Instance()->RefreshState();
		SwapBuffers(m_pApp->GetGLM()->GetHDC());	//Swap Buffer

		counter++;									// Frame counter
		dt_Stack += m_dt;							// Stack dt
		m_gameData->dt = m_timer.GetElapsedTime();	// Renew dt

		// If dt stack is over 1 second,
		// update the frame
		if (dt_Stack >= 1.f)
		{
			m_frameCounter = counter;
			dt_Stack = 0.f;
			counter = 0;
		}
	}

	// If paused the app, 
	// push pause stage to the stack 
	if (m_isPausing) {
		m_ResumeStack.push(m_current);	// Push to the resume stack
		m_PauseStack.push(m_paused);	// Push to the pause stack
		m_next = m_current = m_PauseStack.top().stage;
		m_pApp->GetOBM()->SaveOBM();	// Save objects to the temp list
		m_StageStack.push(m_paused);	// Push pause to the current stack
	}

	// If resume the app, 
	// pop pause stage from the stack 
	else if (m_isResuming || m_isRestarting)
	{
		m_StageStack.top().pStage->Shutdown();
		m_StageStack.top().pStage->Unload();

		if (m_isResuming)
		{
			m_pApp->GetOBM()->LoadOBM();	// Load the objects from the temp list
			m_StageStack.pop();				// Remove current stage

			// Get rid of multiple 
			// pause stack stages
			m_PauseStack.pop();
			delete m_paused.pStage;

			// If there are several pause stack...
			if (m_PauseStack.size())	
				m_paused.pStage = m_PauseStack.top().pStage;		
			// If not...
			else
				m_paused.pStage = nullptr;

			// If gsm resumes and need to change stage once more,
			// do not this
            if (!m_isResumeNext)
            {
                m_next = m_current = m_ResumeStack.top();
				m_ResumeStack.pop();
            }
		}
	}

	// If User quit at the puased stage,
	else if (m_isQuitting)
	{
		// then shutdown every stage from the stack
		while (!m_StageStack.empty())
		{
			m_StageStack.top().pStage->Shutdown();
			m_StageStack.top().pStage->Unload();
			m_StageStack.pop();
		
			// Return the pause info to the obm list
			m_pApp->GetOBM()->LoadOBM();
		}
	}

	// Non for upper cases, just shutdown current stage
	else
	{
		m_StageStack.top().pStage->Shutdown();
		m_StageStack.top().pStage->Unload();
	}

}
/******************************************************************************/
/*!
\brief - Deallocates game resources
\return - NONE
*/
/******************************************************************************/
void GameStateManager::Shutdown(void)
{
    // XBOX
	bool xInput = XboxInput::Instance()->IsConnected();
	if (xInput)
		XboxInput::Instance()->Vibrate(0, 0);
	XboxInput::Instance()->DestroyInstance();

	//The last stage doesn't get deleted in the loop, so it is deleted here.
	delete m_pStage;
	m_pStage = 0;
	
}

/******************************************************************************/
/*!
\brief - Get toggle of pausing
\return - m_isPausing
*/
/******************************************************************************/
bool GameStateManager::IsPausing(void) const
{
	return m_isPausing;
}

/******************************************************************************/
/*!
\brief - Lets client know if quit has been requested.
\return - True if the GameStateManager will quit, false otherwise.
*/
/******************************************************************************/
bool GameStateManager::IsQuitting(void) const
{
	return m_isQuitting;
}

/******************************************************************************/
/*!
\brief - Lets client know if quit has been requested.
\return - True if the GameStateManager will resume, false otherwise.
*/
/******************************************************************************/
bool GameStateManager::IsResuming(void) const
{
	return m_isResuming;
}
/******************************************************************************/
/*!
\brief - Let the client request a stage change.
\param stageType - The stageType to change to.
*/
/******************************************************************************/
void GameStateManager::SetNextStage(StageType stageType)
{
	m_next = stageType;
}

/******************************************************************************/
/*!
\brief - Let the client request a stage change after pause.
\param stageType - The stageType to change to.
*/
/******************************************************************************/
void GameStateManager::Pause(StageType stageType)
{
	// Proper addition
	//if (m_StageStack.size() < 2) {
		m_isPausing = true;
		// Add m_pStage to stage stack
		m_paused.pStage = StageFactory::CreateStage(stageType, this, m_pApp->GetOBM());
		m_paused.stage = stageType;
	//}

	//// Error message
	//else 
	//	std::cout << "You cannot add stages more than 2!\n";
}

/******************************************************************************/
/*!
\brief - Resume and move to the next stage
\param stageType - The stageType to change to.
*/
/******************************************************************************/
void GameStateManager::ResumeRestart(void)
{
	// Proper addition
	//if (m_StageStack.size() == 2) {
	m_isPausing = false;
	m_isResumeRestart = true;
	m_isResuming = true;
}

/******************************************************************************/
/*!
\brief - Resume and move to the next stage
\param stageType - The stageType to change to.
*/
/******************************************************************************/
void GameStateManager::ResumeNextStage(StageType stageType)
{
	// Proper addition
	//if (m_StageStack.size() == 2) {
		m_isPausing = false;
		m_isResumeNext = true;
		m_isResuming = true;
		m_next = stageType;
	//}

	//// Error message
	//else 
	//	std::cout << "You cannot resume on non pause state!\n";
}

/******************************************************************************/
/*!
\brief - Allows the client to request that the game quit.
\param isQuitting - he bool value to set to.
\return - NONE
*/
/******************************************************************************/
void GameStateManager::SetQuit(bool isQuitting)
{
	m_isQuitting = isQuitting;
}
/******************************************************************************/
/*!
\brief - Function to delete old stage and create a new one.
\return - NONE
*/
/******************************************************************************/
void GameStateManager::ChangeGameState(void)
{
	//Update information that was changed last frame.
	m_current = m_next;
	m_isRestarting = false;

	//Delete the old stage
	delete m_pStage;
	m_pStage = 0;

	//dynamically allocate a new stage based on the current state (use a swtich)
	m_pStage = StageFactory::CreateStage(m_current, this, GetAppPtr()->GetOBM());

	// This is to prevent crash
	if(!m_StageStack.empty()) m_StageStack.pop();

	// Add m_pStage to stage stack
	m_StageStack.push(StageInfo{ m_current, m_pStage });
}

/******************************************************************************/
/*!
\brief - Manage proccess messages
*/
/******************************************************************************/
void GameStateManager::ProccessMessages(void)
{
	MSG message;
	while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

/******************************************************************************/
/*!
\brief - Handle interruption
*/
/******************************************************************************/
void GameStateManager::HandlingInterruption(void)
{
	if (m_pApp->GetInterrupted()
		&& m_current != ST_PAUSE
		&& m_StageStack.size() == 1)
		Pause(ST_PAUSE);

	if (m_pApp->m_returnFullScr) {
		if (m_pApp->GetInterrupted()
			&& !m_pApp->m_scrToggle
			&& m_pApp->GetFullScreen()) {
			m_pApp->SetFullScreen(false, false);
			m_pApp->m_scrToggle = true;
		}

		else if (!m_pApp->GetInterrupted()
			&& m_pApp->m_scrToggle
			&& !m_pApp->GetFullScreen()) {
			m_pApp->SetFullScreen(true, false);
			m_pApp->m_scrToggle = false;
		}
	}
}

/******************************************************************************/
/*!
\brief - Refresh key input status 
*/
/******************************************************************************/
void GameStateManager::TriggerInputController(void)
{
	if (InputManager::m_refresh.size()) {

		// Set trigger toggle to false
		if (InputManager::GetInstance().GetPressedStatus() == DOWN)
			InputManager::GetInstance().SetTriggerToggle(false);

		// Refresh the keys' boolean value
		else {
			for (auto it : InputManager::m_refresh)
				InputManager::GetInstance().RefreshTrigger(it);

			// Delete all the key in the vector
			InputManager::m_refresh.clear();
			InputManager::GetInstance().SetTriggerToggle(true);
		}
	}

	// Reset mouse wheel's status
	InputManager::GetInstance().PressInactivate(MOUSE_MIDDLE_UP);
	InputManager::GetInstance().PressInactivate(MOUSE_MIDDLE_DOWN);
}

/******************************************************************************/
/*!
\brief - Restart stage
\param isRestarted
*/
/******************************************************************************/
void GameStateManager::Restart(bool isRestarted)
{
	m_isRestarting = isRestarted;
}

/******************************************************************************/
/*!
\brief - Resume stage
*/
/******************************************************************************/
void GameStateManager::Resume(void)
{
	// Resume to previous stage
	//if (m_StageStack.size() == 2) {
		//Bo back to the last state
		m_isPausing = false;
		m_isResuming = true;
	//}

	// Error message
	//else
	//	std::cout << "You cannot resume on non pause state!\n";
}

/******************************************************************************/
/*!
\brief - Set First Stage of app
\param first - stage to be 1st
*/
/******************************************************************************/
void GameStateManager::SetFirstStage(StageType first)
{
	m_1stStage = first;
}

/******************************************************************************/
/*!
\brief - Get current state
\return m_current
*/
/******************************************************************************/
StageType GameStateManager::GetCurrentState(void) const
{
	return m_current;
}

/******************************************************************************/
/*!
\brief - Get next state
\return m_next
*/
/******************************************************************************/
StageType GameStateManager::GetNextState(void) const
{
	return m_next;
}

/******************************************************************************/
/*!
\brief - Get frame per a sec
\return m_frameCounter
*/
/******************************************************************************/
int GameStateManager::GetFrameCounter(void) const
{
	return m_frameCounter;
}

/******************************************************************************/
/*!
\brief - Get current stage' timer
\return m_time
*/
/******************************************************************************/
const Timer& GameStateManager::GetStageTimer(void) const
{
	return m_StageStack.top().pStage->m_time;
}

/******************************************************************************/
/*!
\brief - Get the number of stage
\return m_StageStack.size();
*/
/******************************************************************************/
unsigned GameStateManager::GetStageSize(void) const
{
	return m_StageStack.size();
}

/******************************************************************************/
/*!
\brief - Get aplication's resolution
\return app's resolution
*/
/******************************************************************************/
ScreenSize GameStateManager::GetResolution(void)
{
	return m_pApp->GetResolution();
}

/******************************************************************************/
/*!
\brief - Set aplication's resolution
\param res - screen resolution
*/
/******************************************************************************/
void GameStateManager::SetResolution(const ScreenSize& res)
{
	m_pApp->SetResolution(res);
}

/******************************************************************************/
/*!
\brief - Set aplication's screen mode
\param scr - screen mode (full ? windowed)
*/
/******************************************************************************/
void GameStateManager::SetFullScreen(bool scr)
{
	m_pApp->SetFullScreen(scr);
}

/******************************************************************************/
/*!
\brief - Get aplication's screen mode
\return app's screen mode
*/
/******************************************************************************/
bool GameStateManager::GetFullScreen(void) const
{
	return m_pApp->GetFullScreen();
}

/******************************************************************************/
/*!
\brief - Get pointer to the app
\return m_pApp
*/
/******************************************************************************/
Application* GameStateManager::GetAppPtr(void)
{
	return m_pApp;
}

/******************************************************************************/
/*!
\brief - Get pointer to the GL Manager
\return GLManager
*/
/******************************************************************************/
GLManager* GameStateManager::GetGLManager(void)
{
	return m_GLM;
}

/******************************************************************************/
/*!
\brief - Get pointer to the Sound Manager
\return SoundManager
*/
/******************************************************************************/
SoundManager* GameStateManager::GetSoundManager(void)
{
	return m_SM;
}

/******************************************************************************/
/*!
\brief - Get m_gameData
*/
/******************************************************************************/
GameData* GameStateManager::GetGameData(void) const
{
	return m_gameData;
}