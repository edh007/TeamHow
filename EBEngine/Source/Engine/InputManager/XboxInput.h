/******************************************************************************/
/*!
\file   XboxInput.h
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2017/04/10(yy/mm/dd)

\description
Contains Xbox class

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _XBOX_CONTROLLER_H_
#define _XBOX_CONTROLLER_H_
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <XInput.h>
#include <cmath>
#include <vector>

const int MAX_NUM = 15;

enum XBOX_KEYSETTING
{
	INVALID = 0,
	DPAD_UP ,
	DPAD_DOWN ,
	DPAD_LEFT ,
	DPAD_RIGHT ,
	START ,
	BACK ,
	LEFT_THUMB ,
	RIGHT_THUMB ,
	LEFT_SHOULDER ,
	RIGHT_SHOULDER ,
	XBOX_A ,
	XBOX_B ,
	XBOX_X ,
	XBOX_Y ,
	LAST  // 15
};



// XBOX Controller Class Definition
class XboxInput
{

    private:
    XINPUT_STATE _controllerState;
	XINPUT_KEYSTROKE _controllerStroke;
    int _controllerNum;
    float deadzoneX;
    float deadzoneY;
    static XboxInput *m_instance;
    bool wasConnected;

	// Setting Vibration
	int m_intensity;
	float m_time;
	bool m_vibToggle;
	float m_elapsedTime;

    public:

	XboxInput(void);
	XboxInput(float dzX, float dzY) : deadzoneX(dzX), deadzoneY(dzY) {}
    bool Update(float dt);
    int  GetPort();
    bool CheckConnection();
    XINPUT_STATE GetState();
    bool IsConnected();
    bool Refresh();
    void Vibrate(int leftVal = 0, int rightVal = 0);
    static XboxInput* Instance(void);
    static void DestroyInstance(void);

	void SetVibration(int _intensity, float _time);

    float leftStickX;
    float leftStickY;
    float rightStickX;
    float rightStickY;
    float leftTrigger;
    float rightTrigger;

    const int DPAD_UP = 0x0001;
    const int DPAD_DOWN = 0x0002;
    const int DPAD_LEFT = 0x0004;
    const int DPAD_RIGHT = 0x0008;
    const int START = 0x0010;
    const int BACK = 0x0020;
    const int LEFT_THUMB = 0x0040;
    const int RIGHT_THUMB = 0x0080;
    const int LEFT_SHOULDER = 0x0100;
    const int RIGHT_SHOULDER = 0x0200;
    const int XBOX_A = 0x1000;
    const int XBOX_B = 0x2000;
    const int XBOX_X = 0x4000;
    const int XBOX_Y = 0x8000;

    bool m_PrevButtonPressed[MAX_NUM]; // Previous frame button states
    bool m_ButtonPressed[MAX_NUM];      // Current frame button states       
    bool m_ButtonsTrigger[MAX_NUM]; // Buttons pressed on current frame

    void RefreshState();
    bool GetButtonTrigger(int _button);
    bool GetAnyButtonTrigger(void);
    bool GetButtonPressed(int _button);

	int GetKey(XBOX_KEYSETTING wPa)
	{
		switch (wPa)
		{
		case XBOX_KEYSETTING::DPAD_UP:		return DPAD_UP;
		case XBOX_KEYSETTING::DPAD_DOWN:	return DPAD_DOWN;
		case XBOX_KEYSETTING::DPAD_LEFT:	return DPAD_LEFT;
		case XBOX_KEYSETTING::DPAD_RIGHT:	return DPAD_RIGHT;
		case XBOX_KEYSETTING::START:		return START;
		case XBOX_KEYSETTING::BACK:			return BACK;
		case XBOX_KEYSETTING::LEFT_THUMB:	return LEFT_THUMB;
		case XBOX_KEYSETTING::RIGHT_THUMB:	return RIGHT_THUMB;
		case XBOX_KEYSETTING::LEFT_SHOULDER: return LEFT_SHOULDER;
		case XBOX_KEYSETTING::RIGHT_SHOULDER: return RIGHT_SHOULDER;
		case XBOX_KEYSETTING::XBOX_A:		return XBOX_A;
		case XBOX_KEYSETTING::XBOX_B:		return XBOX_B;
		case XBOX_KEYSETTING::XBOX_X:		return XBOX_X;
		case XBOX_KEYSETTING::XBOX_Y:		return XBOX_Y;
		default:							return 0;
		}
	}

    XBOX_KEYSETTING GetKey(int _Key)
    {
        switch (_Key)
        {
        case  0x0001:       return XBOX_KEYSETTING::DPAD_UP;
        case  0x0002:       return XBOX_KEYSETTING::DPAD_DOWN;
        case  0x0004:       return XBOX_KEYSETTING::DPAD_LEFT;
        case  0x0008:       return XBOX_KEYSETTING::DPAD_RIGHT;
        case  0x0010:       return XBOX_KEYSETTING::START;
        case  0x0020:       return XBOX_KEYSETTING::BACK;
        case  0x0040:       return XBOX_KEYSETTING::LEFT_THUMB;
        case  0x0080:       return XBOX_KEYSETTING::RIGHT_THUMB;
        case  0x0100:       return XBOX_KEYSETTING::LEFT_SHOULDER;
        case  0x0200:       return XBOX_KEYSETTING::RIGHT_SHOULDER;
        case  0x1000:       return XBOX_KEYSETTING::XBOX_A;
        case  0x2000:       return XBOX_KEYSETTING::XBOX_B;
        case  0x4000:       return XBOX_KEYSETTING::XBOX_X;
        case  0x8000:       return XBOX_KEYSETTING::XBOX_Y;
        default:			return INVALID;
        }
    }
};
#endif

