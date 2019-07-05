/******************************************************************************/
/*!
\file   Random.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Random's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <cstdlib>
#include "Math\MathUtils.h"

class Random
{

public:

	/******************************************************************************/
	/*!
	\brief - Get Random integer
	\param left - range to start
	\param right - range to end
	*/
	/******************************************************************************/
	int	GetRandomInt(int left = INT_MIN, int right = INT_MAX)
	{
		int result = left + rand() % (right - left + 1);
		return result;
	};

	/******************************************************************************/
	/*!
	\brief - Get Random floating number
	\param left - range to start
	\param right - range to end
	*/
	/******************************************************************************/
	float GetRandomFloat(float left = FLT_MIN, float right = FLT_MAX)
	{	
		float result = left + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (right - left)));
		return result;
	};

	/******************************************************************************/
	/*!
	\brief - Get Random Vec3
	\param left - range to start
	\param right - range to end
	*/
	/******************************************************************************/
	vec3 GetRandomVec3(float left = FLT_MIN, float right = FLT_MAX)
	{
		vec3 result;
		result.x = left + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (right - left)));
		result.y = left + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (right - left)));
		result.z = left + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (right - left)));

		return result;
	}

	/******************************************************************************/
	/*!
	\brief - Get Random Vec2
	\param left - range to start
	\param right - range to end
	*/
	/******************************************************************************/
	vec2 GetRandomVec2(float left = FLT_MIN, float right = FLT_MAX)
	{
		vec2 result;
		result.x = left + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (right - left)));
		result.y = left + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (right - left)));

		return result;
	}

	/******************************************************************************/
	/*!
	\brief - Simgletone pattern for Random class
	*/
	/******************************************************************************/
	static Random& GetInstance(void)
	{
		static Random random;
		return random;
	}

private:

	/******************************************************************************/
	/*!
	\brief - Random Constructor
	*/
	/******************************************************************************/
	Random(void){
		//Set seed
		srand((unsigned)clock());
	};
};

#endif // _RANDOM_H_