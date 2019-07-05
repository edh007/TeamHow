/******************************************************************************/
/*!
\file   WinMain.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains WinMain function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#if defined(DEBUG) | defined (_DEBUG)
#define CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif

#include "Utilities/Debug/Debug.h"
#include "Utilities/INI/iniReader.h"
#include "App/Application.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h> //WinMain

STICKYKEYS g_StartupStickyKeys = { sizeof(STICKYKEYS), 0 };
TOGGLEKEYS g_StartupToggleKeys = { sizeof(TOGGLEKEYS), 0 };
FILTERKEYS g_StartupFilterKeys = { sizeof(FILTERKEYS), 0 };


/******************************************************************************/
/*!
\brief - Control sticky keys
\param bAllowKeys
*/
/******************************************************************************/
void AllowAccessibilityShortcutKeys(bool bAllowKeys)
{
    if (bAllowKeys)
    {
        // Restore StickyKeys/etc to original state and enable Windows key      
        STICKYKEYS sk = g_StartupStickyKeys;
        TOGGLEKEYS tk = g_StartupToggleKeys;
        FILTERKEYS fk = g_StartupFilterKeys;

        SystemParametersInfo(SPI_SETSTICKYKEYS, sizeof(STICKYKEYS), &g_StartupStickyKeys, 0);
        SystemParametersInfo(SPI_SETTOGGLEKEYS, sizeof(TOGGLEKEYS), &g_StartupToggleKeys, 0);
        SystemParametersInfo(SPI_SETFILTERKEYS, sizeof(FILTERKEYS), &g_StartupFilterKeys, 0);
    }
    else
    {
        // Disable StickyKeys/etc shortcuts but if the accessibility feature is on, 
        // then leave the settings alone as its probably being usefully used

        STICKYKEYS skOff = g_StartupStickyKeys;
        if ((skOff.dwFlags & SKF_STICKYKEYSON) == 0)
        {
            // Disable the hotkey and the confirmation
            skOff.dwFlags &= ~SKF_HOTKEYACTIVE;
            skOff.dwFlags &= ~SKF_CONFIRMHOTKEY;

            SystemParametersInfo(SPI_SETSTICKYKEYS, sizeof(STICKYKEYS), &skOff, 0);
        }

        TOGGLEKEYS tkOff = g_StartupToggleKeys;
        if ((tkOff.dwFlags & TKF_TOGGLEKEYSON) == 0)
        {
            // Disable the hotkey and the confirmation
            tkOff.dwFlags &= ~TKF_HOTKEYACTIVE;
            tkOff.dwFlags &= ~TKF_CONFIRMHOTKEY;

            SystemParametersInfo(SPI_SETTOGGLEKEYS, sizeof(TOGGLEKEYS), &tkOff, 0);
        }

        FILTERKEYS fkOff = g_StartupFilterKeys;
        if ((fkOff.dwFlags & FKF_FILTERKEYSON) == 0)
        {
            // Disable the hotkey and the confirmation
            fkOff.dwFlags &= ~FKF_HOTKEYACTIVE;
            fkOff.dwFlags &= ~FKF_CONFIRMHOTKEY;

            SystemParametersInfo(SPI_SETFILTERKEYS, sizeof(FILTERKEYS), &fkOff, 0);
        }
    }
}

/******************************************************************************/
/*!
\brief - Main window function

\param instance

\return 0 

*/
/******************************************************************************/
int WINAPI WinMain(HINSTANCE instance, HINSTANCE /*prev*/, 
	LPSTR /*command line*/, int /*show*/)
{
	DEBUG_LEAK_CHECKS(-1);
	DEBUG_CREATE_CONSOLE();

	//! Set default values
	char* Title = "Empty Brain Engine";
	int Resolution = 1;
	bool ScreenMode = true;

	//! Load ini setting values
	iniReader LoadSetting("Resource/Data/Settings.ini");
	Title = LoadSetting.ReadString("Setting", "Title");
	Resolution = LoadSetting.ReadInt
		("Setting", "Resolution");
	ScreenMode = LoadSetting.ReadBool("Setting", "FullScreen");
	
	//! Values to init my application from main, these could be read from a file
	InitData initData;
	initData.instance = instance;

	//! Set title and screen mode
	initData.title = Title;
	initData.isFullScreen = ScreenMode;

	//! Set screen size
	switch (Resolution)
	{
	case 1: 
		initData.scrSize = SCR_640X480;
		break;
	case 2: 
		initData.scrSize = SCR_800X600;
		break;
	case 3: 
		initData.scrSize = SCR_1024X768;
		break;
	case 4: 
		initData.scrSize = SCR_1280X1024;
		break;
	case 5: 
		initData.scrSize = SCR_1920X1080;
		break;
	default: 
		initData.scrSize = SCR_640X480;
		break;
	}

    // Save the current sticky/toggle/filter key settings so they can be restored them later
    SystemParametersInfo(SPI_GETSTICKYKEYS, sizeof(STICKYKEYS), &g_StartupStickyKeys, 0);
    SystemParametersInfo(SPI_GETTOGGLEKEYS, sizeof(TOGGLEKEYS), &g_StartupToggleKeys, 0);
    SystemParametersInfo(SPI_GETFILTERKEYS, sizeof(FILTERKEYS), &g_StartupFilterKeys, 0);

    // Restore back when going to windowed or shutting down
    AllowAccessibilityShortcutKeys(false);

	//Start and run my application
	Application app(initData);
	if (app.DataLoaded())
		app.Update();

    DEBUG_DESTROY_CONSOLE();

    // Disable when full screen
    AllowAccessibilityShortcutKeys(true);
	return 0;
}
