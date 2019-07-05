/******************************************************************************/
/*!
\file   Application.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Application's class and member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Application.h"
#include "../Utilities/Debug/Debug.h"
#include "../InputManager/InputManager.h"
#include "../../BaseData/Logics/RegisterLogics.h"
#include "../../BaseData/Stages/RegisterStages.h"
#include "../../BaseData/Components/RegisterComponents.h"
#include "../../BaseData/ArcheTypes/RegisterArcheTypes.h"
#include "../GameSystem/Sound/SoundManager/SoundManager.h"
#include "../GameSystem/Graphic/GraphicManager/GLManager.h"
#include "../StateManager/GameStateManager/GameStateManager.h"

namespace
{
	/*!Window style if the user chooses full screen*/
	const DWORD FULLSCREEN_STYLE = WS_POPUP | WS_VISIBLE;
	/*!Window style if the user choose windowed mode*/
	const DWORD WINDOWED_STYLE = WS_POPUP | WS_CAPTION /*| WS_SYSMENU*/;
	//const DWORD WINDOWED_STYLE = WS_OVERLAPPEDWINDOW;
	
	/******************************************************************************/
	/*!
	\brief - Adjust window size that client want
	\param style - Window's style
	\param size  - Window's size
	\param xStart - Window's x starting point
	\param yStart - Window's y starting point
	*/
	/******************************************************************************/
	void AdjustAndCenterWindow(DWORD style, RECT& size, int& xStart, int& yStart)
	{
		DEVMODE dm = { 0 };
		int winWidth, winHeight;

		/*Get the size of the screen*/
		dm.dmSize = sizeof(dm);
		EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &dm);

		/*Make client area of window the correct size*/
		AdjustWindowRect(&size, style, false);

		/*Calculate new width and height*/
		winWidth = size.right - size.left;
		winHeight = size.bottom - size.top;

		/*Get start position for center*/
		xStart = (dm.dmPelsWidth / 2) - (winWidth / 2);
		yStart = (dm.dmPelsHeight / 2) - (winHeight / 2);
	}

}//end unnamed namespace

/******************************************************************************/
/*!
\brief - Build stages and game logics for game app
\return true
*/
/******************************************************************************/
bool Application::DataLoaded(void)
{
	if (check_gl && check_fmod)
	{
		// Build stages and set first stage
		RegisterStages();
		m_GSM->SetFirstStage(ST_SPLASH);

		// Build basic components
		RegisterComponents();

		// Here app loads font, sound, textures
		m_JP->InitAssetData(m_GLM, m_SM);

		// Build Logics
		RegisterLogics();

		// Add archetypes
		RegisterArcheTypes();

		return true;
	}

	return false;
}

/******************************************************************************/
/*!
\brief - Application Constructor
\param initData - Application's init data
*/
/******************************************************************************/
Application::Application(const InitData& initData)
	:check_fmod(false), check_gl(false), interrupted(false), m_returnFullScr(false)
{
	//ONLY CALSS ONCE;
	DEBUG_CALL_CHECK();

	//Code data form initData
	m_instance = initData.instance;
	m_scrSize.width = initData.scrSize.width;
	m_scrSize.height = initData.scrSize.height;
	m_returnFullScr = m_isFullScreen = initData.isFullScreen;
	m_style = (initData.isFullScreen) ? FULLSCREEN_STYLE : WINDOWED_STYLE;
	m_isQuitting = false;

	//Set up our WNDCLASS(defaults)
	m_winClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW; //OpenGL
	m_winClass.cbClsExtra = 0;
	m_winClass.cbSize = sizeof(WNDCLASSEX);
	m_winClass.cbWndExtra = 0;
	m_winClass.lpszMenuName = 0;
	m_winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_winClass.hInstance = initData.instance;					//Instance from main 
	
	// Set Icon and cursor for app
	m_winClass.hIcon = (HICON)LoadImage(nullptr, "Resource/Texture/Icon/icon256.ico", IMAGE_ICON, 256, 256, LR_LOADFROMFILE);
	m_winClass.hIconSm = (HICON)LoadImage(nullptr, "Resource/Texture/Icon/icon32.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);

	//m_winClass.hCursor = (HCURSOR)LoadImage(nullptr, "Resource/Texture/Icon/cursor.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
	m_winClass.hCursor = LoadCursorFromFile("Resource/Texture/Icon/aim.ani");

	m_winClass.lpszClassName = initData.title;		//Window class name
	m_winClass.lpfnWndProc = WinProc;				//Static member
	SetCursor(m_winClass.hCursor);

	//Register our window class
	RegisterClassEx(&m_winClass);

	//Make client are the size that we want
	int xStart;
	int yStart;
	RECT size = { 0 };
	size.right = initData.scrSize.width;
	size.bottom = initData.scrSize.height;
	
	if (m_isFullScreen)
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = m_scrSize.width;			// Selected Screen Width
		dmScreenSettings.dmPelsHeight = m_scrSize.height;		// Selected Screen Height

		dmScreenSettings.dmPelsWidth = GetSystemMetrics(SM_CXSCREEN);
		dmScreenSettings.dmPelsHeight = GetSystemMetrics(SM_CYSCREEN);
		SetScreenSizeX(GetSystemMetrics(SM_CXSCREEN));
		SetScreenSizeY(GetSystemMetrics(SM_CYSCREEN));

		size.right = GetScreenSizeX();
		size.bottom = GetScreenSizeY();

		dmScreenSettings.dmBitsPerPel = 32;						// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	
	AdjustAndCenterWindow(m_style, size, xStart, yStart);

	//Now create our window
	m_window = CreateWindow(
		initData.title,			//Class name
		initData.title,			//Window Title
		m_style,				//Window style
		xStart,					//x Starting pos
		yStart,					//y Starting pos
		size.right - size.left,	//Width
		size.bottom - size.top,	//Height
		0,						//Parent Window
		0,						//Menu
		m_instance,				//Hinstance
		this					//Lparm This will be available in WM_CREATE
		);

    if (m_isFullScreen)
    {
        HDC hDC = GetWindowDC(nullptr);
        SetWindowPos(m_window, nullptr, 0, 0, GetDeviceCaps(hDC, HORZRES),
            GetDeviceCaps(hDC, VERTRES), SWP_FRAMECHANGED);
    }

	/******************* Bind OBM and GSM *******************/
	m_GSM = new GameStateManager(this);
	m_OBM = new ObjectManager(m_GSM);

	/******************* Load json data as string *******************/
	m_JP = new JsonParser;
	m_JP->Load("Resource/Data/AssetData.json");

	/******************** Set sound system; FMOD ********************/
	m_SM = new SoundManager;
	check_fmod = m_SM->InitFMOD(m_JP->CheckLoadedSounds());

	/******************** Set Open GL ********************/ 
	m_GLM = new GLManager;
	check_gl = m_GLM->InitGL(this, m_window, m_scrSize.width, m_scrSize.height);

	/*****************************************************/

	//Make sure window is showing and messages have been sent
	ShowWindow(m_window, true);
	UpdateWindow(m_window);

	if (!m_isFullScreen)
		SetFullScreen(false);
}

/******************************************************************************/
/*!
\brief - Application Destructor
*/
/******************************************************************************/
Application::~Application(void)
{
	//Only Call Once
	DEBUG_CALL_CHECK();

	// Clear all archetypes
	ObjectManager::ClearArcheTypes();

	// Clear gl and sm
	delete m_GLM;
	delete m_GSM;
	delete m_OBM;
	delete m_SM;
	delete m_JP;

	m_GLM = 0;
	m_GSM = 0;
	m_OBM = 0;
	m_SM = 0;
	m_JP = 0;

	// Clear all components, logics and stages
	LogicFactory::ClearBuilderMap();
	ComponentFactory::ClearBuilderMap();
	StageFactory::ClearBuilderMap();

	UnregisterClass(LPCTSTR(m_winClass.lpszClassName), m_instance);

	m_instance = 0;
}

/******************************************************************************/
/*!
\brief - Update Application 
*/
/******************************************************************************/
void Application::Update(void)
{
	//Only Call Once
	DEBUG_CALL_CHECK();
	m_GSM->Init();
	while (!m_isQuitting)
	{

		//Update GameManager
		m_GSM->Update();

		//If GameManager is Quitting, set Close message
		m_isQuitting = m_GSM->IsQuitting();
	}
	m_GSM->Shutdown();
}

/******************************************************************************/
/*!
\brief - Quit application
*/
/******************************************************************************/
void Application::Quit(void)
{
	SendMessage(m_window, WM_CLOSE, 0, 0);
}

/******************************************************************************/
/*!
\brief - Get GLManager
\return m_GLM - pointer to GLManager
*/
/******************************************************************************/
GLManager* Application::GetGLM(void) const
{
	return m_GLM;
}

/******************************************************************************/
/*!
\brief - Get Sound Manager
\return m_SM - pointer to Sound Manager
*/
/******************************************************************************/
SoundManager* Application::GetSM(void) const
{
	return m_SM;
}

/******************************************************************************/
/*!
\brief - Get Object Manager
\return m_OBM
*/
/******************************************************************************/
ObjectManager* Application::GetOBM(void)
{
	return m_OBM;
}

/******************************************************************************/
/*!
\brief - Get Game State Manager
\return m_GSM
*/
/******************************************************************************/
GameStateManager* Application::GetGSM(void) const
{
	return m_GSM;
}

/******************************************************************************/
/*!
\brief - Set interruption toggle
\param toggle
*/
/******************************************************************************/
void Application::SetInterrupted(bool toggle)
{
	interrupted = toggle; 
}

/******************************************************************************/
/*!
\brief - Get interruption toggle
\return interrupted
*/
/******************************************************************************/
bool Application::GetInterrupted(void) const
{
	return interrupted;
}

/******************************************************************************/
/*!
\brief - Get apllication;s resolution
\return m_scrSize - screen size of app
*/
/******************************************************************************/
const ScreenSize& Application::GetResolution(void) const
{
	return m_scrSize;
}

/******************************************************************************/
/*!
\brief - Set apllication;s resolution
\param res - screen size of app that client want
*/
/******************************************************************************/
void Application::SetResolution(const ScreenSize& res)
{
	m_scrSize.width = res.width;
	m_scrSize.height = res.height;
	SetWindowPos(m_window, 0, 0, 0, m_scrSize.width, m_scrSize.height, SWP_NOMOVE);
	
	m_GLM->Resize(m_scrSize.width, m_scrSize.height);
}

/******************************************************************************/
/*!
\brief - Set apllication;s window mode
\param fullscreen - bool toggle to set app's window mode
*/
/******************************************************************************/
void Application::SetFullScreen(bool fullscreen, bool intended)
{
	m_isFullScreen = fullscreen;
	
	if (intended)
		m_returnFullScr = m_isFullScreen;

	RECT size = { 0 };
	size.right = m_scrSize.width;
	size.bottom = m_scrSize.height;

	DEVMODE dmScreenSettings;								// Device Mode
	memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
	dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
	dmScreenSettings.dmPelsWidth = m_scrSize.width;			// Selected Screen Width
	dmScreenSettings.dmPelsHeight = m_scrSize.height;		// Selected Screen Height
	dmScreenSettings.dmBitsPerPel = 32;						// Selected Bits Per Pixel
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	if (m_isFullScreen)
	{
		int xStart, yStart;
        dmScreenSettings.dmPelsWidth = GetSystemMetrics(SM_CXSCREEN); 
        dmScreenSettings.dmPelsHeight = GetSystemMetrics(SM_CYSCREEN);
		SetScreenSizeX(GetSystemMetrics(SM_CXSCREEN));
		SetScreenSizeY(GetSystemMetrics(SM_CYSCREEN));

		// Reset style
		m_style = FULLSCREEN_STYLE;

		// Set fullscreen mode
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		AdjustAndCenterWindow(m_style, size, xStart, yStart);
		
		//Remove caption
		DWORD dwStyle = GetWindowLong(m_window, GWL_STYLE);
		DWORD dwRemove = WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
		DWORD dwNewStyle = dwStyle & ~dwRemove;
		SetWindowLong(m_window, GWL_STYLE, dwNewStyle);

		HDC hDC = GetWindowDC(nullptr);
		SetWindowPos(m_window, nullptr, 0, 0, GetDeviceCaps(hDC, HORZRES),
			GetDeviceCaps(hDC, VERTRES), SWP_FRAMECHANGED);
	}

	else
	{
		int appPosX = (GetSystemMetrics(SM_CXSCREEN) / 2 );
		int appPosY = (GetSystemMetrics(SM_CYSCREEN) / 2 );

		// Reset style
		m_style = WINDOWED_STYLE;

		// Set Windowed Mode
		ChangeDisplaySettings(nullptr, 0);
		AdjustAndCenterWindow(m_style, size, appPosX, appPosY);

		// Add caption
		DWORD dwStyle = GetWindowLong(m_window, GWL_STYLE);
		DWORD dwAdd = WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
		DWORD dwNewStyle = dwStyle | dwAdd;
		SetWindowLong(m_window, GWL_STYLE, dwNewStyle);

		SetWindowPos(m_window, nullptr, appPosX, appPosY,
			m_scrSize.width, m_scrSize.height, SWP_FRAMECHANGED);
	}

    if(m_GLM)
        m_GLM->Resize(m_scrSize.width, m_scrSize.height);
}

/******************************************************************************/
/*!
\brief - Get apllication;s window mode
\return m_isFullScreen - bool toggle of app's window mode
*/
/******************************************************************************/
bool Application::GetFullScreen(void) const
{
	return m_isFullScreen;
}

/******************************************************************************/
/*!
\brief - Application's window procedure
\return 0
*/
/******************************************************************************/
LRESULT CALLBACK Application::WinProc(HWND win, UINT msg, WPARAM wp, LPARAM lp)
{
	static Application* s_pApp = 0;

	// Keyboard input
	switch (msg)
	{
	case WM_SYSKEYUP:
		InputManager::GetInstance().InactivateAlt();
		InputManager::GetInstance().SetPressedStatus(UP);
		break;

	case WM_SYSKEYDOWN:
		InputManager::GetInstance().ActivateAlt();
		InputManager::GetInstance().SetPressedStatus(DOWN);
		break;

	case WM_KEYUP:
		InputManager::GetInstance().PressInactivate(InputManager::GetInstance().KeyTranslator(wp));
		InputManager::GetInstance().SetPressedStatus(UP);
		break;

	case WM_KEYDOWN:
		InputManager::GetInstance().PressActivate(InputManager::GetInstance().KeyTranslator(wp));
		InputManager::GetInstance().SetPressedStatus(DOWN);
		break;
	}

	// Mouse input
	switch (msg)
	{
		//Button Down
	case WM_MOUSEMOVE:
		InputManager::GetInstance().SetRawMousePosition(LOWORD(lp), HIWORD(lp));
		break;
		
	case WM_LBUTTONDOWN:
		InputManager::GetInstance().PressActivate(MOUSE_LEFT);
		InputManager::GetInstance().SetPressedStatus(DOWN);
		break;

	case WM_RBUTTONDOWN:
		InputManager::GetInstance().PressActivate(MOUSE_RIGHT);
		InputManager::GetInstance().SetPressedStatus(DOWN);
		break;

	case WM_MBUTTONDOWN:
		InputManager::GetInstance().PressActivate(MOUSE_MIDDLE);
		InputManager::GetInstance().SetPressedStatus(DOWN);
		break;

		//Button Up
	case WM_LBUTTONUP:
		InputManager::GetInstance().PressInactivate(MOUSE_LEFT);
		InputManager::GetInstance().SetPressedStatus(UP);
		break;

	case WM_RBUTTONUP:
		InputManager::GetInstance().PressInactivate(MOUSE_RIGHT);
		InputManager::GetInstance().SetPressedStatus(UP);
		break;

	case WM_MBUTTONUP:
		InputManager::GetInstance().PressInactivate(MOUSE_MIDDLE);
		InputManager::GetInstance().SetPressedStatus(UP);
		break;

	case WM_MOUSEWHEEL:
	{
		short direction = short(HIWORD(wp));

		if (direction > 0)
			InputManager::GetInstance().PressActivate(MOUSE_MIDDLE_UP);

		else if (direction < 0)
			InputManager::GetInstance().PressActivate(MOUSE_MIDDLE_DOWN);

		break;
	}
	}

	// Others
	switch (msg)
	{
	
	// Handle the application interrupted
	case WM_ACTIVATEAPP: 
	{
		if (!wp) {
			s_pApp->SetInterrupted(true);
			ShowWindow(win, SW_MINIMIZE);
		}
		else 
			s_pApp->SetInterrupted(false);
		break;
	}
	
	case WM_CREATE:
	{
		//Contain all data we pass to CreateWindow
		CREATESTRUCT* pCS = reinterpret_cast<CREATESTRUCT*>(lp);
		s_pApp = reinterpret_cast<Application*>(pCS->lpCreateParams);
		
		//Create graphics here..
		break;
	}

	case WM_CLOSE:
	{
		//First destroy the graphics here...

		//Then destroy the window
		//Chance to interrupt...

		DestroyWindow(win);
		break;
	}

	//Where window is actually destroyed
	case WM_DESTROY:
	{
		//Stop game loop
		s_pApp->m_isQuitting = true;
		s_pApp->m_window = 0;
		PostQuitMessage(0);
		break;
	}

	case WM_QUIT:
	{
		break;
	}

	default:
		// Process the left-over messages
		return DefWindowProc(win, msg, wp, lp);
	}

	return 0;

}
