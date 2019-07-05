/******************************************************************************/
/*!
\file   InputManager.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains InputManager's class and member

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include <map>
#include <vector>
#include <Windows.h>
#include "../Utilities/Math/MathUtils.h"

//! Key members
enum INPUT_KEY {
	KEY_INVALID, MOUSE_LEFT, MOUSE_RIGHT, MOUSE_MIDDLE = 4, 
	MOUSE_MIDDLE_UP, MOUSE_MIDDLE_DOWN, KEY_BACK = 8, KEY_TAB,
	KEY_ENTER = 13, KEY_SHIFT = 16, KEY_CONTROL, KEY_ALT,KEY_PAUSE, KEY_CAPSLOCK, 
	KEY_ESC = 27, KEY_SPACE = 32, KEY_PAGEUP, KEY_PAGEDOWN, KEY_END, KEY_HOME,
	KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN, KEY_PRINTSCR, KEY_INSERT, KEY_DELETE,
	KEY_0 = 48, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
	KEY_A = 65, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, 
	KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, 
	KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, 
	KEY_NUM_0 = 96, KEY_NUM_1, KEY_NUM_2, KEY_NUM_3, KEY_NUM_4, KEY_NUM_5, 
	KEY_NUM_6, KEY_NUM_7, KEY_NUM_8, KEY_NUM_9, KEY_MUL, KEY_ADD, 
	KEY_SUB = 109, KEY_DEC, KEY_DIV, 
	KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9,
	KEY_F10, KEY_F11, KEY_F12, KEY_F13, KEY_F14, KEY_F15, KEY_F16,
	KEY_NUMLOCK = 144, KEY_SCRLOCK, 
	KEY_SEMICOLON = 186, KEY_EQUALS, KEY_COMMA, KEY_UNDERSCORE, KEY_PERIOD, 
	KEY_SLASH, 
	KEY_BACKSLASH = 220, KEY_RIGHTBRACE, KEY_LEFTBRACE, KEY_APOSTROPHE, KEY_LAST
};

//! enum to check input triggers
enum PRESSED_STATUS {DOWN, UP};

typedef std::map<unsigned, bool> KeyMap;
typedef std::vector<unsigned> KeyRefresh;

//! InputManager class
class InputManager
{
public:
	
	//! constructor and destructor
	InputManager(void);
	~InputManager(void);

	void RenewKeys(void);

	//! Get keys' interactions
	bool KeyTriggered(WPARAM input_tobe);
	bool KeyPressed(WPARAM input_tobe);
	bool AnyKeyPressed();
	bool AnyKeyTriggered();

	//! Key Translator
	INPUT_KEY KeyTranslator(WPARAM user_input = 0);

	//! Works in wnd processor
	void PressActivate(INPUT_KEY user_input);
	void PressInactivate(INPUT_KEY user_input);
	bool GetTriggerToggle(void) const;
	void SetTriggerToggle(bool trigger);

	//! Check mouse click status
	PRESSED_STATUS GetPressedStatus(void) const;
	void SetPressedStatus(PRESSED_STATUS status);

	//! On mouse position
	const vec3& GetRawMousePosition(void) const;
	void SetRawMousePosition(WORD xPos, WORD yPos);

	//! Translate mouse position
	void SetPerspMouse(const vec3& pos);
	void SetOrthoMouse(const vec3& pos);

	//! Get fined mouse position
	const vec3& GetPerspPosition(void) const;
	const vec3& GetOrthoPosition(void) const;

	void ActivateAlt(void);
	void InactivateAlt(void);
	bool GetAlt(void);

	//Singleton pattern
	static InputManager& GetInstance(void)
	{
		static InputManager instacnce;
		return instacnce;
	}

	void RefreshTrigger(unsigned key);
	static KeyRefresh m_refresh;	//! key refresh vector

private:

	PRESSED_STATUS m_status;			//! Current status
	bool m_trigger, m_anykey, m_alt;	//! trigger and anykey checker

	KeyMap m_key;								//! key map
	vec3 m_position, m_orthoPos, m_perspPos;	//! mouse position info
};

#endif // _INPUT_MANAGER_H_