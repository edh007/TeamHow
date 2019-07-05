/******************************************************************************/
/*!
\file   Particle.h
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2016/07/24(yy/mm/dd)

\description
Contains Sprite class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <vector>
#include <algorithm>

#include "../GraphicManager/GLManager.h"
#include "../../../Component/Component.h"
#include "../../../Component/ComponentBuilder.h"
class Texture;

//! Particle builder class
class ParticleBuilder : public ComponentBuilder
{
public:
	ParticleBuilder() {};
	virtual ~ParticleBuilder() {};
	virtual Component* BuildComponent(Object* Owner, ComponentType key) const;

};

// Represents a single particle and its state
struct Unit {
    vec2 Position, Velocity;
    vec4 Color;
    GLfloat Life;
    GLfloat countCheck;
    int Angle;
    vec2 Scale;
	bool Active;
    Unit() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f), countCheck(0.0f), Angle(0), Scale(0), Active(true) { }
};

enum ParticleRenderType { ADDITIVE, NORMALPARTICLE };
enum ParticleType { P_AFTERIMAGE, P_BOMB, P_LANTERN, P_RADAR, P_SPARK, P_NORMAL, P_BLOW, P_LASER, P_RUN, P_PLAYER, P_INDICATOR, P_CHARGING, P_CHARGESHOT };

// ParticleGenerator acts as a container for rendering a large number of 
// particles by repeatedly spawning and updating particles and killing 
// them after a given amount of time.
class Particle : public Component
{
public:
    // Constructor
    //Particle(Shader shader, GLuint amount);
    Particle(Object* Owner = 0, ComponentType key = CT_PARTICLE);
    virtual ~Particle(void);
    // Update all particles
    void Update(GLfloat dt);
    void SetUnitsPosition(vec2 position);

    // Render all particles
    std::vector<Unit> particles;

	void SetColor(const vec4& color);
	vec4 GetColor(void) const;

	void SetTexture(Texture* texture);
	Texture* GetTexture(void) const;

    void ChangeResolution(int cr);
	Texture* m_texture;

    //Particle Variable
	vec2 EmitArea;
    GLuint EmissionRate;
    GLfloat LifeInit;
    GLfloat LifeVariable;
    int AngleInit;
    int AngleVariable;
    vec2 Gravity;
    int SpeedInitValue;
    int SpeedVariable;
    vec4 ColorInit;
    vec4 ColorEnd;
    vec3 ScaleValue;
    int countCheck;
    vec4 ColorChange;
    vec3 EndScale;
    vec3 scaleMinusValue;
	vec4 m_color;
    vec2 p_speed;
    vec3 p_position;
    bool active;
    int count;
    float Time;

    bool SpinCheck;
    ParticleRenderType particleRenderType;
    ParticleType particleType;
    bool ForcedQuit;
    void Restore();
    void SetParticleVariables(ParticleType p_type);
	void ForceQuitting(void);

	int laser_length;
	int Player_Angle;
private:
    // Initializes buffer and vertex attributes
    void init();
    void Normal(float dt);
    void Blow(float dt);
    void Laser(float dt);
    //vec3 beforePosition;
};


#endif // _SCENE_H_