/******************************************************************************/
/*!
\file   Shader.cpp
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2016/07/23(yy/mm/dd)

\description
Contains shader class member and functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _SHADER_H_
#define _SHADER_H_

class Shader {
public:
    Shader();
    ~Shader();
    GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

    GLuint programID;
};

#endif _SHADER_H_