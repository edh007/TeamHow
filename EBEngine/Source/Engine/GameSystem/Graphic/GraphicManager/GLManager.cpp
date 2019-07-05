/******************************************************************************/
/*!
\file   GLManager.cpp
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2016/07/23(yy/mm/dd)

\description
Contains Graphicmanager's class member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "GLManager.h"


/******************************************************************************/
/*!
\brief - GLManager constructor
*/
/******************************************************************************/
GLManager::GLManager(void)
	:m_hdc(nullptr), m_hglrc(nullptr)
{
}

/******************************************************************************/
/*!
\brief - GLManager destructor
*/
/******************************************************************************/
GLManager::~GLManager(void)
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(m_sha.programID);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteTextures(1, &m_uniform[TEXTURE]);

	for (auto it = m_texList.begin(); it != m_texList.end(); ++it)
		delete it->second;

    m_texList.clear();

	delete m_font;

    //FONT
    // Destroy FreeType once we're finished
    FT_Done_Face(m_face);
    FT_Done_FreeType(m_ft);
}

/******************************************************************************/
/*!
\brief - setting the whole font to use with the fontSize
\param fontSize - size of the font
*/
/******************************************************************************/
void GLManager::SetFont(unsigned fontSize)
{
    m_fontSize = fontSize;

    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&m_ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    // Load font as face
    //FT_Face face;
    if (FT_New_Face(m_ft, "Resource/Font/Default.ttf", 0, &m_face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(m_face, 0, m_fontSize);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph 
        if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
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
            m_face->glyph->bitmap.width,
            m_face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            m_face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            texture,
            vec2(static_cast<float>(m_face->glyph->bitmap.width), static_cast<float>(m_face->glyph->bitmap.rows)),
            vec2(static_cast<float>(m_face->glyph->bitmap_left), static_cast<float>(m_face->glyph->bitmap_top)),
			static_cast<GLuint>(m_face->glyph->advance.x)
        };
        m_chars.insert(std::pair<char, Character>(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

/******************************************************************************/
/*!
\brief - Get the characters
\return m_chars - return characters
*/
/******************************************************************************/
Characters& GLManager::GetCharacters(void)
{
    return m_chars;
}

/******************************************************************************/
/*!
\brief - Return the freetype face
\return m_face - return freetype face
*/
/******************************************************************************/
const FT_Face& GLManager::GetFT_Face(void) const
{
    return m_face;
}

/******************************************************************************/
/*!
\brief - Get freetype library
\return m_ft - return value
*/
/******************************************************************************/
const FT_Library& GLManager::GetFT_Lib(void) const
{
    return m_ft;
}

/******************************************************************************/
/*!
\brief - Get freetype font size
\return m_fontSize - return value
*/
/******************************************************************************/
unsigned GLManager::GetFontSize(void) const
{
    return m_fontSize;
}

/******************************************************************************/
/*!
\brief - Set freetype font size
\param fontSize - setting value
*/
/******************************************************************************/
void GLManager::SetFontSize(unsigned fontSize)
{
    m_fontSize = fontSize;
}

/******************************************************************************/
/*!
\brief - Initialize graphic manager
\param Appli - check application is created
\param window - handle the window
\param width - width of the screen
\param height - height of the screen
*/
/******************************************************************************/
bool GLManager::InitGL(Application* Appli, HWND& window, int width, int height)
{
    //CHECK APPLICATION...
    UNREFERENCED_PARAMETER(Appli);
    app = Appli;

	EnableOGLAPI(window);

    //Before using shader, initialize glew.
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return false;
    }

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_height = height;
    m_width = width;
    b_height = height;
    b_width = width;

	if (app->GetFullScreen() == true)
		Resize(m_width, m_height);
	else
		glViewport(0, 0, m_width, m_height);

	SetOGLEnvironment();
    SetFont(20);
    return true;
}

/******************************************************************************/
/*!
\brief - Get the HDC
\return m_hdc - return the HDC
*/
/******************************************************************************/
HDC GLManager::GetHDC(void) const
{
    return m_hdc;
}

/******************************************************************************/
/*!
\brief - Get the texture map
\return m_texList - list that saved all textures
*/
/******************************************************************************/
TextureMap & GLManager::GetTextureMap(void)
{
	return m_texList;
}

/******************************************************************************/
/*!
\brief - Get the exact texture to use
\param key - searching the map with key
\return m_texList[key] - return the found texture
*/
/******************************************************************************/
Texture* GLManager::GetTexture(const char* key)
{
    //check if id number is not EXIST
    if (m_texList[key] == 0)
        return nullptr;

    return m_texList[key];
}

/******************************************************************************/
/*!
\brief - Get Uniform
\param type - find the exact type
\return m_uniform[type] - return the found uniform type's value
*/
/******************************************************************************/
GLuint GLManager::GetUniform(UniformType type)
{
	return m_uniform[type];
}

/******************************************************************************/
/*!
\brief - Setting the environments of the graphic
*/
/******************************************************************************/
void GLManager::SetOGLEnvironment(void)
{
	//Need to create VAO(Vertex Array Object) and set it as the current one: Do this once your window is created (= after the OpenGL Context creation) and before any other OpenGL call.
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuffer); // Generate 1 buffer, put the resulting identifier in vertexbuffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); //talk about 'vertexbuffer' buffer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW); //give vertices to openGL.
																									   // 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size : X + Y + Z => 3
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		5 * sizeof(GLfloat),	// stride
		(GLvoid*)0				// array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		1,                              // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                              // size : U+V => 2
		GL_FLOAT,                       // type
		GL_FALSE,                        // normalized?
		5 * sizeof(GLfloat),			// stride
		(GLvoid*)(3 * sizeof(GLfloat))	// array buffer offset
	);

	// Create and compile our GLSL program from the shaders
	m_sha.programID = m_sha.LoadShaders("Resource/Shader/SimpleVertexShader.glsl", "Resource/Shader/SimpleFragmentShader.glsl");

	// Use our shader
	glUseProgram(m_sha.programID);

	// Get a handle for our "ModelViewProjection(MVP)" uniform, only during the initialization
	m_uniform[MATRIX] = glGetUniformLocation(m_sha.programID, "MVP");
	m_uniform[ANIMATION] = glGetUniformLocation(m_sha.programID, "Animation");
	m_uniform[TYPE] = glGetUniformLocation(m_sha.programID, "Type");
	m_uniform[SCREEN] = glGetUniformLocation(m_sha.programID, "Screensize");
	m_uniform[OFFSET] = glGetUniformLocation(m_sha.programID, "offset");
	m_uniform[COLOR] = glGetUniformLocation(m_sha.programID, "color");
	m_uniform[PROJECT] = glGetUniformLocation(m_sha.programID, "projection");
	m_uniform[SCALE] = glGetUniformLocation(m_sha.programID, "scale");
    m_uniform[FOWTYPE] = glGetUniformLocation(m_sha.programID, "FowType");
    m_uniform[FLIP] = glGetUniformLocation(m_sha.programID, "Flip");
	m_uniform[BLUR_TOGGLE] = glGetUniformLocation(m_sha.programID, "BlurToggle");
	m_uniform[BLUR_AMOUNT] = glGetUniformLocation(m_sha.programID, "BlurAmount");
	m_uniform[INVERSE] = glGetUniformLocation(m_sha.programID, "InverseToggle");
	m_uniform[SOBEL_TOGGLE] = glGetUniformLocation(m_sha.programID, "SobelToggle");
	m_uniform[SOBEL_AMOUNT] = glGetUniformLocation(m_sha.programID, "SobelAmount");
	m_uniform[WAVE_TOGGLE] = glGetUniformLocation(m_sha.programID, "WaveToggle");
	m_uniform[WAVE_PHASE] = glGetUniformLocation(m_sha.programID, "WavePhase");
	m_uniform[TIME] = glGetUniformLocation(m_sha.programID, "Time");
	m_uniform[RIPPLE_TOGGLE] = glGetUniformLocation(m_sha.programID, "RippleToggle");

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	m_uniform[TEXTURE] = glGetUniformLocation(m_sha.programID, "myTextureSampler");

	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(m_uniform[TEXTURE], 0);
}

/******************************************************************************/
/*!
\brief - Add the texture
\param key - setting the texture map id
\param texture_dir - direction of the texture
*/
/******************************************************************************/
void GLManager::AddTexture(const char* key, const char * texture_dir)
{
	m_texList[key] = new Texture;
	m_texList[key]->loadPNG(texture_dir);
}

/******************************************************************************/
/*!
\brief - Getting the shader
\return m_sha - return the shader
*/
/******************************************************************************/
const Shader & GLManager::GetShader(void) const
{
	return m_sha;
}

/******************************************************************************/
/*!
\brief - enable the openGL with window
\param window - get the handle of the window
*/
/******************************************************************************/
void GLManager::EnableOGLAPI(HWND& window)
{
	//Step 1
	m_hdc = GetDC(window);

	//Step 2
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        32,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        16,
        0, 0, 0, 0, 0, 0, 0
    };

	PixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	if (!SetPixelFormat(m_hdc, PixelFormat, &pfd))
	{
		MessageBox(window, "Error: Cannot Set Pixel Format!", "ERROR!", MB_OK);
	}

	//Step 3
	m_hglrc = wglCreateContext(m_hdc);

	//Step 4
	wglMakeCurrent(m_hdc, m_hglrc);
}

/******************************************************************************/
/*!
\brief - disable the openGL with window
\param window - get the handle of the window
*/
/******************************************************************************/
void GLManager::DisableOGLAPI(HWND& window)
{
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(m_hglrc);

	if (!ReleaseDC(window, m_hdc))
		MessageBox(window, "Error: Cannot Release Device Context", "ERROR!", MB_OK);
}

/******************************************************************************/
/*!
\brief - Resize the screen with x,y
\param x - width
\param y - height
*/
/******************************************************************************/
void GLManager::Resize(int x, int y)
{
    m_width = x;
    m_height = y;
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//Prevent the case height = 0
	if (m_height <= 0) m_height = 1;

	//Save the data
	float temp_width = static_cast<float>(m_width);
	float temp_height = static_cast<float>(m_height);

    //gluOrtho2D(0.0, m_width, 0.0, m_height);
    //glOrtho(-m_width / m_height, m_width / m_height, -1, 1, -1, 1);
	int start_x = 0, start_y = 0;
	//Temporary stuff
    if (!app->GetFullScreen())
    {
        start_x = -8, start_y = -30;
        glViewport(start_x, start_y, GLsizei(temp_width), GLsizei(temp_height));
        b_width = m_width;
        b_height = m_height;
        fullScreen = false;
    }
    else if (app->GetFullScreen() == true) 
    {
        GLfloat aspect = 4.0f / 3.0f;

		int screenWidth = app->GetScreenSizeX();
        int screenHeight = app->GetScreenSizeY();

        int viewWidth = screenWidth;
        int viewHeight = int(float(screenWidth) / aspect);
        if (viewHeight > screenHeight) {
            viewHeight = screenHeight;
            viewWidth = int(float(screenHeight) * aspect);
        }

        int vportX = (screenWidth - viewWidth) / 2;
        int vportY = (screenHeight - viewHeight) / 2;

        glViewport(vportX, vportY, viewWidth, viewHeight);

        b_width = screenWidth;
        b_height = screenHeight;
        fullScreen = true;
        viewportX = vportX;
        mouseCrX = float(m_width) / float(viewWidth);
        mouseCrY = float(m_height) / float(screenHeight);
    }
}
