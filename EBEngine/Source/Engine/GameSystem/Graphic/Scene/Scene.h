//#pragma once
/******************************************************************************/
/*!
\file   Scene.h
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2016/07/23(yy/mm/dd)

\description
Contains Scene class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include "../../../Utilities/Math/MathUtils.h"
#include "../GraphicManager/GLManager.h"

class Object;
class Text;
class Sprite;
class Texture;
//class Fow;
class Particle;
struct Unit;
class GLManager;
class GameStateManager;

typedef std::vector<Object*> SpriteList;
enum RenderType { TEXT, SPRITE, PARTICLE, LIGHT };

class Scene {

public:

    Scene(GameStateManager* GSM);
    ~Scene(void);

	void Init(void);
	void Update(float dt);
	void Shutdown(void);

    void AddSprite(Object* sprite);
    void RemoveSprite(const int id);

    void RotateCamera(float angle);
    void SetCameraPos(const vec3& value);
	const vec3& GetCameraPos(void) const;

	void SetColor(const vec4& color);
	const vec4& GetColor(void) const;

	bool showMouse;
    float b_width;
    float b_height;
private:

	void MouseCamera(bool show = true);

	//Camera Functions
	void Camera(Object* sprite, float dt);
	void Camera(Object* particle, Unit unit);
	
	void DrawSprites(Object* sprite);
	void DrawTexts(Object* drawtext);
	void DrawParticles(Object* particle, float dt);
	//void DrawFOW(Object* fow);

	mat44 MVP;
	vec2 m_phase;
	//Camera Variables
	vec3 cameraPos;
	vec3 cameraUp;
	float cam_angle;
	mat44 Projection;
	mat44 cameraView;
	mat44 Model;
	mat44 Animation;
	SpriteList m_spriteList;

	GameStateManager* m_GSM;
	GLManager* m_pGLM;

	vec4 m_color;
    float m_width;
    float m_height;
    bool resizeToggle = true;

};

#endif // _SCENE_H_