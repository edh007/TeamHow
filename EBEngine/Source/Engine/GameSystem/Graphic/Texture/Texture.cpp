/******************************************************************************/
/*!
\file   Texture.cpp
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2016/07/24(yy/mm/dd)

\description
Contains Texture class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

/*
LodePNG Examples

Copyright (c) 2005-2012 Lode Vandevenne

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

//Compile command for Linux:
//g++ lodepng.cpp example_opengl.cpp -lSDL -lGL -O3

/*
LodePNG OpenGL example. Decodes a PNG and shows it in OpenGL. PNG filename
should be given as a command line parameter.

It's written for the most basic old OpenGL version, and a correction for non
power of two textures had to be added.

Only very few lines on the sample are about loading the PNG. Most of the
sample lines show a way to render a texture in 2D in OpenGL.

No fancy 3D graphics are shown, it only shows the image statically. The sample
shows LodePNG can be used to load PNG images as textures in OpenGL.
*/
//#pragma warning (disable:4996)

#include "LodePNG\lodepng.h"
#include "Texture.h"
#include <vector>
#include <iostream>

/******************************************************************************/
/*!
\brief - Texture default constructor
*/
/******************************************************************************/
Texture::Texture(void)
{
    m_textureID = 0;
}

/******************************************************************************/
/*!
\brief - Texture default constructor
*/
/******************************************************************************/
Texture::~Texture(void)
{}

/******************************************************************************/
/*!
\brief - getting the id of texture
\return m_textureID - get id as texture id
*/
/******************************************************************************/
GLuint Texture::GetID(void) const
{
    return m_textureID;
}

/******************************************************************************/
/*!
\brief - setting the id of texture
\param id - set id as texture id
*/
/******************************************************************************/
void Texture::SetID(GLuint id)
{
    m_textureID = id;
}


//Load PNG file from disk using a State, normally needed for more advanced usage.
/******************************************************************************/
/*!
\brief - load the png file
\param filename - address of image files
*/
/******************************************************************************/
void Texture::loadPNG(const char* filename)
{
    std::vector<unsigned char> image; //the raw pixels
    //unsigned width, height;

    //decode
    unsigned error = lodepng::decode(image, width, height, filename);

    //if there's an error, display it
    if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    else std::cout << "Load : " << filename << " SUCCESS!"<<std::endl;

    //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

}



#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

/******************************************************************************/
/*!
\brief - load the dds file
\param imagepath - address of image files
\return m_textureID - get the id
*/
/******************************************************************************/
GLuint Texture::loadDDS(const char * imagepath){

    unsigned char header[124];

    FILE *fp;

    /* try to open the file */
    fopen_s(&fp, imagepath, "rb");
    //fp = fopen(imagepath, "rb");
    if (fp == nullptr) {
        printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar();
        return 0;
    }
    else
        std::cout << "Load : " << imagepath << " SUCCESS!" << std::endl;

    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

    /* get the surface desc */
    fread(&header, 124, 1, fp);

    unsigned int t_height = *(unsigned int*)&(header[8]);
    unsigned int t_width = *(unsigned int*)&(header[12]);
    unsigned int linearSize = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC = *(unsigned int*)&(header[80]);


    unsigned char * buffer;
    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    /* close the file pointer */
    fclose(fp);

    unsigned int components;
    components = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch (fourCC)
    {
    case FOURCC_DXT1:
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case FOURCC_DXT3:
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case FOURCC_DXT5:
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        free(buffer);
        return 0;
    }

    // Create one OpenGL texture
    glGenTextures(1, &m_textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for (unsigned int level = 0; level < mipMapCount && (t_width || t_height); ++level)
    {
        unsigned int size = ((t_width + 3) / 4)*((t_height + 3) / 4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, t_width, t_height,
            0, size, buffer + offset);

        offset += size;
        t_width /= 2;
        t_height /= 2;

        // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
        if (t_width < 1) t_width = 1;
        if (t_height < 1) t_height = 1;

    }

    free(buffer);

    return m_textureID;
}