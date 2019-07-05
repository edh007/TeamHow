/******************************************************************************/
/*!
\file   Texture.h
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2016/07/24(yy/mm/dd)

\description
Contains Sprite class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../GraphicManager/GLManager.h"

class Texture {

public:
    Texture(void);
    ~Texture(void);
    GLuint GetID(void) const;
    void loadPNG(const char* filename);
    void SetID(GLuint id);

    GLuint loadDDS(const char * imagepath);

	unsigned width, height;
private:
    GLuint m_textureID;
};


#endif // _SCENE_H_