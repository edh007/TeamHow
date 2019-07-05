/******************************************************************************/
/*!
\file   iniReader.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/07/28(yy/mm/dd)

\description
Contains iniReader class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _INIREADER_H_
#define _INIREADER_H_

#include "../Math/MathUtils.h"

//! iniReader class
class iniReader
{
public:

	//! Constuctor and destructor
	iniReader(const char* fileName);
	~iniReader();

	//! Reading functions
	int ReadInt(char *section, char* key);
	float ReadFloat(char *section, char* key);
	bool ReadBool(char *section, char* key);
	char* ReadString(char *section, char* key);

	vec3 ReadVec3(char *section, char* key);
	vec4 ReadVec4(char *section, char* key);

private:

	char m_fileName[255];	// ini file name to read
	char* m_stringResult;	// temp string storage

};

#endif _INIREADER_H_