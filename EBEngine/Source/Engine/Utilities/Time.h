/******************************************************************************/
/*!
\file   Timer.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Timer's class and members
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _TIMER_H_
#define _TIMER_H_

#include <ctime>

class Timer
{
private:

	//! begining time
	float m_begTime;

public:

	Timer() { m_begTime = 0; };
	~Timer(){};

	/******************************************************************************/
	/*!
	\brief - Start to check time
	*/
	/******************************************************************************/
	void StartTime(void)
	{
		m_begTime = static_cast<float>(clock());
	}

	/******************************************************************************/
	/*!
	\brief - Get spent time from StartTime() moment
	*/
	/******************************************************************************/
	float GetElapsedTime(void) const
	{
		return (static_cast<float>(clock()) - m_begTime) / (CLOCKS_PER_SEC);
	}

	/******************************************************************************/
	/*!
	\brief - Singletone pattern for Timer
	*/
	/******************************************************************************/
	static Timer& GetInstance(void)
	{
		static Timer gi_timer;
		return gi_timer;
	}
};

#endif