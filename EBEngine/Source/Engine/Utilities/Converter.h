/******************************************************************************/
/*!
\file   Converter.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/07/31(yy/mm/dd)

\description
Contains strConverter's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _CONVERTER_H_
#define _CONVERTER_H_
#include <Windows.h>

class Converter{

public:

	/******************************************************************************/
	/*!
	\brief - Converter's Construtor
	*/
	/******************************************************************************/
	Converter() :pStr(0), pwStr(0) {};

	/******************************************************************************/
	/*!
	\brief - Converter's Destrutor
	*/
	/******************************************************************************/
	~Converter(){
		
		// Delete binded pointer
		if (pStr)	delete pStr;
		if (pwStr)	delete pwStr;
	};
	
	/******************************************************************************/
	/*!
	\brief - Convert from wchar to char
	\param str
	*/
	/******************************************************************************/
	char* ConvertWCtoC(const wchar_t* str)
	{
		//Calculate size of wchar
		int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
		//char* Bind memory
		pStr = new char[strSize];
		//Convert
		WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
		return pStr;
	}

	/******************************************************************************/
	/*!
	\brief - Convert from char to wchar
	\param str
	*/
	/******************************************************************************/
	wchar_t* ConverCtoWC(const char* str)
	{
		//Calculate size of multibyte
		int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
		//wchar* Bind memory
		pwStr = new WCHAR[strSize];
		//Convert
		MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pwStr, strSize);
		return pwStr;
	}

private:

	char *pStr;		// pointer to the one converted to string
	wchar_t *pwStr;	// pointer to the one converted to wstring

};
#endif // _CONVERTER_H_