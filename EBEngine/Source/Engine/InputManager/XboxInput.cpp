/******************************************************************************/
/*!
\file   XboxInput.cpp
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2017/04/10(yy/mm/dd)

\description
Contains Xbox class

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "XboxInput.h"
#define XUSER_MAX_COUNT 4
#include <iostream>

//! Singleton Instance
XboxInput *XboxInput::m_instance = nullptr;

/******************************************************************************/
/*!
\brief - XboxInput Constructor
*/
/******************************************************************************/
XboxInput::XboxInput(void)
	: deadzoneX(0.05f), deadzoneY(0.02f), wasConnected(true), m_elapsedTime(0.f), m_vibToggle(false), m_time(0.f)
{
	for (int i = 0; i < MAX_NUM; ++i)
	{
        m_PrevButtonPressed[i] = false;
        m_ButtonPressed[i] = false;
        m_ButtonsTrigger[i] = false;
	}
}

/******************************************************************************/
/*!
\brief - XboxInput Constructor
\param a - check Value rhs
\param b - Check Value lhs
\return a - if a is bigger one
\return b - if b is bigger or same one
*/
/******************************************************************************/
float fmaxf(float &a, float &b)
{
	if(a>b) return a;
	return b;
}

/******************************************************************************/
/*!
\brief - XboxInput Update
\param dt - check Value rhs
\return wasConnected - if b is bigger or same one
*/
/******************************************************************************/
bool XboxInput::Update(float dt)
{
	if(!XboxInput::Instance()->Refresh())
	{
		if(wasConnected)
			wasConnected = false;
	}
	else
	{
		if(!wasConnected)
		{
			wasConnected = true;
			XboxInput::Instance()->GetPort();
		}
	}

	// Set the Xbox Input Toggle
	bool xInput = XboxInput::Instance()->IsConnected();

	if (xInput)
	{
		if (m_vibToggle == true)
		{
			XboxInput::Instance()->Vibrate(m_intensity, m_intensity);

			m_elapsedTime += dt;
			if (m_elapsedTime > m_time)
			{
				m_vibToggle = false;
				m_elapsedTime = 0;
			}
		}
		else
		{
			XboxInput::Instance()->Vibrate(0, 0);
		}
	}

	 //Iterate through all gamepad buttons
	for (int i = 0; i < MAX_NUM; i++)
	{
        
		// Set button state for current frame
        m_ButtonPressed[i] = (GetState().Gamepad.wButtons & GetKey(XBOX_KEYSETTING(i))) == GetKey(XBOX_KEYSETTING(i));

		// Set 'DOWN' state for current frame
        m_ButtonsTrigger[i] = !m_PrevButtonPressed[i] && m_ButtonPressed[i];
	}
	return wasConnected;
}

/******************************************************************************/
/*!
\brief - Get button pressed
\param _button - get address of button
\return true - true if button is pressed, false if not
*/
/******************************************************************************/
bool XboxInput::GetButtonPressed(int _button)
{
    if (GetState().Gamepad.wButtons & _button)
        return true; // The button is pressed
    return false; // The button is not pressed
}

/******************************************************************************/
/*!
\brief - Get button trigger
\param _button - get address of button
\return m_ButtonsTrigger - if it is true, it is triggered
*/
/******************************************************************************/
bool XboxInput::GetButtonTrigger(int _button)
{
    return m_ButtonsTrigger[GetKey(_button)];
}

/******************************************************************************/
/*!
\brief - Get any button trigger
\return m_ButtonsTrigger - if it is true, it is triggered
*/
/******************************************************************************/
bool XboxInput::GetAnyButtonTrigger(void)
{
    if (m_ButtonsTrigger[GetKey(XBOX_A)] || m_ButtonsTrigger[GetKey(XBOX_B)] || 
        m_ButtonsTrigger[GetKey(XBOX_X)] || m_ButtonsTrigger[GetKey(XBOX_Y)])
        return true;
    else
        return false;
}

/******************************************************************************/
/*!
\brief - Refresh the state with memory copy
*/
/******************************************************************************/
void XboxInput::RefreshState()
{
    memcpy(m_PrevButtonPressed, m_ButtonPressed, sizeof(m_PrevButtonPressed));
}

/******************************************************************************/
/*!
\brief - Setting the Vibration
\param _intensity - intensity of the vibration
\param _time - how long it maintains
*/
/******************************************************************************/
void XboxInput::SetVibration(int _intensity, float _time)
{
	m_intensity = _intensity;
	m_time = _time;
	m_vibToggle = true;
}

/******************************************************************************/
/*!
\brief - Get the port number
\return _controllerNum - number of port : 1 ~ 4
*/
/******************************************************************************/
int XboxInput::GetPort()
{
	return _controllerNum + 1;
}

/******************************************************************************/
/*!
\brief - Get the state of the Xinput
\return _controllerState - intensity of the vibration
*/
/******************************************************************************/
XINPUT_STATE XboxInput::GetState()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	XInputGetState(_controllerNum, &_controllerState);

	return _controllerState;
}

/******************************************************************************/
/*!
\brief - check the number of connection
\return controllerId - checked result
*/
/******************************************************************************/
bool XboxInput::CheckConnection()
{
	int controllerId = -1;

	for (DWORD i = 0; i < XUSER_MAX_COUNT && controllerId == -1; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		if (XInputGetState(i, &state) == ERROR_SUCCESS)
			controllerId = i;
	}

	_controllerNum = controllerId;

	return controllerId != -1;
}

/******************************************************************************/
/*!
\brief - check it is connected or not
\return bool - checked connected
*/
/******************************************************************************/
bool XboxInput::IsConnected()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(_controllerNum, &_controllerState);

	if(Result == ERROR_SUCCESS)
		return true;

	else
		return false;
}

/******************************************************************************/
/*!
\brief - Refresh the Xbox Input
\return bool - Returns false if the controller has been disconnected
*/
/******************************************************************************/
bool XboxInput::Refresh()
{
	if (_controllerNum == -1)
		CheckConnection();

	if (_controllerNum != -1)
	{
		ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
		if (XInputGetState(_controllerNum, &_controllerState) != ERROR_SUCCESS)
		{
			_controllerNum = -1;
			return false;
		}

		float normLX = fmaxf(-1, (float) _controllerState.Gamepad.sThumbLX / 32767);
		float normLY = fmaxf(-1, (float) _controllerState.Gamepad.sThumbLY / 32767);

		leftStickX = (abs(normLX) < deadzoneX ? 0 : (abs(normLX) - deadzoneX) * (normLX / abs(normLX)));
		leftStickY = (abs(normLY) < deadzoneY ? 0 : (abs(normLY) - deadzoneY) * (normLY / abs(normLY)));

		if (deadzoneX > 0) leftStickX *= 1 / (1 - deadzoneX);
		if (deadzoneY > 0) leftStickY *= 1 / (1 - deadzoneY);

		float normRX = fmaxf(-1, (float) _controllerState.Gamepad.sThumbRX / 32767);
		float normRY = fmaxf(-1, (float) _controllerState.Gamepad.sThumbRY / 32767);

		rightStickX = (abs(normRX) < deadzoneX ? 0 : (abs(normRX) - deadzoneX) * (normRX / abs(normRX)));
		rightStickY = (abs(normRY) < deadzoneY ? 0 : (abs(normRY) - deadzoneY) * (normRY / abs(normRY)));

		if (deadzoneX > 0) rightStickX *= 1 / (1 - deadzoneX);
		if (deadzoneY > 0) rightStickY *= 1 / (1 - deadzoneY);

		leftTrigger = (float) _controllerState.Gamepad.bLeftTrigger / 255;
		rightTrigger = (float) _controllerState.Gamepad.bRightTrigger / 255;

		return true;
	}
	return false;
}

/******************************************************************************/
/*!
\brief - Setting the Vibrate with left & right motor
\param leftVal - left motor intensity
\param rightVal - right motor intensity
*/
/******************************************************************************/
void XboxInput::Vibrate(int leftVal, int rightVal)
{
	// Create a Vibraton State
	XINPUT_VIBRATION Vibration;

	// Zeroise the Vibration
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	// Set the Vibration Values
	Vibration.wLeftMotorSpeed = WORD(leftVal);
	Vibration.wRightMotorSpeed = WORD(rightVal);

	// Vibrate the controller
	XInputSetState(_controllerNum, &Vibration);
}

/******************************************************************************/
/*!
\brief - If there is no instance, create
\return m_instance - return instance
*/
/******************************************************************************/
XboxInput *XboxInput::Instance()
{
	if (m_instance == nullptr)
		m_instance = new XboxInput();
	return (m_instance);
}

/******************************************************************************/
/*!
\brief - Destroy the Instance
*/
/******************************************************************************/
void XboxInput::DestroyInstance()
{
	if (m_instance == nullptr)
		return ;
	delete m_instance;
	m_instance = nullptr;
}
