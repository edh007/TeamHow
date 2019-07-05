/******************************************************************************/
/*!
\file   GLManager.h
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2016/07/23(yy/mm/dd)

\description
Contains SoundManager class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _GLMANAGER_H_
#define _GLMANAGER_H_

#include "GL\glew.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\wglew.h"
#include <Windows.h>
#pragma comment(lib,"opengl32.lib")

// Freetype lib
#include <ft2build.h>
#include FT_FREETYPE_H
#pragma comment(lib,"freetype26.lib")

#include "../../../Utilities/Math/MathUtils.h"
#include "../Texture/Texture.h"
#include "../Shader/Shader.h"
#include "../../../../BaseData/GameData.h"
#include "../../../App/Application.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

class Application;
class Texture;

//! vectext buffer information
static const GLfloat g_vertex_buffer_data[] =
{
	//		X		Y		Z		U		V
	.5f, .5f, 0.f, 1.f, 0.f , /*1*/
	-.5f, .5f, 0.f, 0.f, 0.f , /*2*/
	-.5f, -.5f, 0.f, 0.f, 1.f , /*3*/

	-.5f, -.5f, 0.f, 0.f, 1.f , /*4*/
	.5f, -.5f, 0.f, 1.f, 1.f , /*5*/
	.5f, .5f, 0.f, 1.f, 0.f
};

enum UniformType {
	ANIMATION, MATRIX, SCREEN, TEXTURE, TYPE, OFFSET, COLOR,
	PROJECT, SCALE, FOWTYPE, FLIP, BLUR_TOGGLE, BLUR_AMOUNT, 
	INVERSE, SOBEL_TOGGLE, SOBEL_AMOUNT, WAVE_TOGGLE, WAVE_PHASE,
	TIME, RIPPLE_TOGGLE, UNIFORM_END
};

typedef std::unordered_map<std::string, Texture*> TextureMap;

// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    vec2 Size;    // Size of glyph
    vec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
};

typedef std::unordered_map<GLchar, Character> Characters;

//! FontData struct
struct FontData {
    FT_Face m_face;
    FT_Library m_ftlib;
    Characters m_chars;
    unsigned m_fontSize;
};

//! GLManager struct
class GLManager
{
public:

	GLManager(void);
	~GLManager(void);

    bool InitGL(Application* Appli, HWND& window, int width, int height);
    HDC GetHDC(void) const;

	void EnableOGLAPI(HWND& window);
	void DisableOGLAPI(HWND& window);
    void Resize(int x, int y);

	TextureMap& GetTextureMap(void);
    Texture* GetTexture(const char* id);
	GLuint GetUniform(UniformType type);
	void SetOGLEnvironment(void);
	void AddTexture(const char* key, const char* font_dir);

	const Shader& GetShader(void) const;
    //bool checkResize = false;

    //FONT
    // Manage font info
    Characters& GetCharacters(void);
    unsigned GetFontSize(void) const;
    void SetFontSize(unsigned fontSize);
    const FT_Face& GetFT_Face(void) const;
    const FT_Library& GetFT_Lib(void) const;
    void SetFont(unsigned fontSize);

    bool fullScreen;
    float mouseCrX;
    float mouseCrY;
    int viewportX;

    int b_height;
    int b_width;

    //NEED?
    int m_height;
    int m_width;
private:

    HDC    m_hdc;
    HGLRC  m_hglrc;

    int PixelFormat;

	GLuint m_uniform[UNIFORM_END];

	GLuint VertexArrayID;
	GLuint vertexbuffer;

	TextureMap m_texList;
	Texture* m_font;
	Shader m_sha;
    Application* app;

    // FreeType
    FT_Library m_ft;			// FreeType
    FT_Face	   m_face;			// Freetype face
    FT_UInt	   m_fontSize;		// font size
    Characters m_chars;			// Ascii storage

    float correctionValue_W;
    float correctionValue_H;
    ScreenSize b_res;
};

#endif // _GLMANAGER_H_