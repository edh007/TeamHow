/******************************************************************************/
/*!
\file   Text.cpp
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2016/07/23(yy/mm/dd)

\description
Contains text's class member functions: maybe it have to make and delete each stage

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Text.h"
#include "../Texture/Texture.h"
#include "../../../ObjectManager/Object/Object.h"
#include "../../../ObjectManager/ObjectManager.h"
#include "../../../StateManager/GameStateManager/GameStateManager.h"
#include "../../../Component/ComponentFactory/ComponentFactory.h"


/******************************************************************************/
/*!
\brief - TextBuilder constructor
\param Owner - Owner of this Component
\param key - ComponentType
\return new Text
*/
/******************************************************************************/
Component* TextBuilder::BuildComponent(Object* Owner, ComponentType key) const {
	return new Text(Owner, key);
};

/******************************************************************************/
/*!
\brief - Text constructor
\param Owner - Owner of this logic
\param key - ComponentType
*/
/******************************************************************************/
Text::Text(Object* Owner, ComponentType key)
	: Component(Owner, key), m_color(vec4(1,1,1,1))
{
	// Preset transform
	if (!m_Owner->HasComponent(CT_TRANSFORM))
		m_Owner->AddComponent(ComponentFactory::CreateComponent(m_Owner, CT_TRANSFORM));

    // Get ft data from gl manager
    m_data.m_face = Owner->GetOBM()->GetGSM()->GetGLManager()->GetFT_Face();
    m_data.m_ftlib = Owner->GetOBM()->GetGSM()->GetGLManager()->GetFT_Lib();
    m_data.m_chars = Owner->GetOBM()->GetGSM()->GetGLManager()->GetCharacters();
    m_data.m_fontSize = Owner->GetOBM()->GetGSM()->GetGLManager()->GetFontSize();
}

/******************************************************************************/
/*!
\brief - Text Destructor
*/
/******************************************************************************/
Text::~Text(void)
{
}

/******************************************************************************/
/*!
\brief - Setting the color of the text with parameter color
\param color - Setting value of the text's color
*/
/******************************************************************************/
void Text::SetColor(const vec4& color)
{
	m_color = color;
}

/******************************************************************************/
/*!
\brief - Getting the color of the text class
\return m_color - return the color of the Text
*/
/******************************************************************************/
vec4 Text::GetColor(void) const
{
	return m_color;
}

/******************************************************************************/
/*!
\brief - Set the text inside the class
\param text - setting the text to print out.
*/
/******************************************************************************/
void Text::SetText(const char* text, ...)
{
    va_list ap;

    va_start(ap, text);
    vsprintf_s(m_textStorage, text, ap);
    va_end(ap);

    m_text = m_textStorage;
}

/******************************************************************************/
/*!
\brief - Get the text of this component
\return m_text - return the text data of this component
*/
/******************************************************************************/
const std::string& Text::GetText(void) const
{
    return m_text;
}

/******************************************************************************/
/*!
\brief - Set the font size with input
\param size - setting the fontsize
*/
/******************************************************************************/
void Text::SetFontSize(unsigned size)
{
	if (m_data.m_fontSize == size)
		return;

    m_data.m_chars.clear();

    FT_Set_Pixel_Sizes(m_data.m_face, 0, size);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph 
        if (FT_Load_Char(m_data.m_face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            m_data.m_face->glyph->bitmap.width,
            m_data.m_face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            m_data.m_face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            texture,
            vec2(static_cast<float>(m_data.m_face->glyph->bitmap.width),
            static_cast<float>(m_data.m_face->glyph->bitmap.rows)),
            vec2(static_cast<float>(m_data.m_face->glyph->bitmap_left),
            static_cast<float>(m_data.m_face->glyph->bitmap_top)),
            static_cast<GLuint>(m_data.m_face->glyph->advance.x)
        };
        m_data.m_chars.insert(std::pair<char, Character>(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    m_data.m_fontSize = size;
}

/******************************************************************************/
/*!
\brief - Get the fontdata
\return m_data - return the font data
*/
/******************************************************************************/
FontData& Text::GetFontData(void)
{
    return m_data;
}

/******************************************************************************/
/*!
\brief - Set the fontdata
\param face - getting the freetype face
\param lib - getting the freetype library
*/
/******************************************************************************/
void Text::SetFontData(const FT_Face& face, const FT_Library& lib)
{
    m_data.m_face = face;
    m_data.m_ftlib = lib;
}