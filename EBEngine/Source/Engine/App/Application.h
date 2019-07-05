/******************************************************************************/
/*!
\file   Application.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Application's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef APPLICATION_H
#define APPLICATION_H
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "../../BaseData/GameData.h"

class GLManager;
class JsonParser;
class SoundManager;
class ObjectManager;
class GameStateManager;

using namespace Resolution;

//! Used in main to give initial values to the application.
struct InitData
{
	LPCTSTR		title;
	HINSTANCE	instance;
	bool		isFullScreen;
	ScreenSize	scrSize;
};

//! Used as the staring point for the program
class Application
{
public:

	Application(const InitData& initData);
	~Application(void);

	//Application functions called by main
	void Update(void);

	//Function to contorl the window
	void Quit(void);
	bool DataLoaded(void);

	//Manager screen mode
	bool GetFullScreen(void) const;
	void SetFullScreen(bool fullScreen, bool intended = true);
	const ScreenSize& GetResolution(void) const;
	void SetResolution(const ScreenSize& res);

	GLManager* GetGLM(void) const;			//!< GL Manager
	SoundManager* GetSM(void) const;		//!< Sound Manager
	ObjectManager* GetOBM(void);			//!< Object Manager
	GameStateManager* GetGSM(void) const;	//!< Game State Manager

	void SetInterrupted(bool toggle);
	bool GetInterrupted(void) const;

	int GetScreenSizeX() { return screenSizeX; }
	void SetScreenSizeX(int x) { screenSizeX = x; }
	int GetScreenSizeY() { return screenSizeY; }
	void SetScreenSizeY(int y) { screenSizeY = y; }

	bool m_returnFullScr, m_scrToggle;

private:
	static LRESULT CALLBACK WinProc(HWND win, UINT msg, WPARAM wp, LPARAM pl);

	HINSTANCE  m_instance;		//!< The instance from main
	WNDCLASSEX m_winClass;		//!< The windows class
	DWORD	   m_style;			//!< The windows style
	HWND	   m_window;		//!< The handle to the window
	bool       m_isQuitting;	//!< flag for quitting
	bool	   m_isFullScreen;	//!< flag for fullscreen
	ScreenSize m_scrSize;		//!< The window width and height

	bool interrupted;
	bool check_fmod, check_gl;

	GLManager* m_GLM;
	SoundManager* m_SM;
	ObjectManager* m_OBM;
	GameStateManager* m_GSM;
	
	JsonParser* m_JP;

	int screenSizeX;
	int screenSizeY;

}; //end GameEngine


#endif // APPLICATION_H