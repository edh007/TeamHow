/******************************************************************************/
/*!
\file   Text.h
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2016/07/24(yy/mm/dd)

\description
Contains Sprite class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _TEXT_H_
#define _TEXT_H_

#include <string>
#include "../GraphicManager/GLManager.h"
#include "../../../Utilities/Math/MathUtils.h"
#include "../../../Component/Component.h"
#include "../../../Component/ComponentBuilder.h"

class Texture;

//! Text builder class
class TextBuilder : public ComponentBuilder
{
public:
	TextBuilder() {};
	virtual ~TextBuilder() {};
	virtual Component* BuildComponent(Object* Owner, ComponentType key) const;

};

//! Text class
class Text : public Component
{
public:

	//! Constructor and destructor
	Text(Object* Owner = 0, ComponentType key = CT_TEXT);
	virtual ~Text(void);

	//! Text functions
	void SetText(const char* text, ...);
	const std::string& GetText(void) const;

	//! Font data functions
	FontData& GetFontData(void);
	void SetFontData(const FT_Face& face, const FT_Library& lib);

	void SetColor(const vec4& color);
	vec4 GetColor(void) const;
    void SetFontSize(unsigned size);

private:
	vec4 m_color;
	std::string m_text;
	FontData m_data;
	char m_textStorage[1024];
    
};

#endif // _SCENE_H_