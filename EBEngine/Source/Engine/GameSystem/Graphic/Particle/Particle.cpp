/******************************************************************************/
/*!
\file   Particle.cpp
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2016/07/24(yy/mm/dd)
\description
Contains Particle class
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Particle.h"
#include "../../../Utilities/Math/MathUtils.h"
#include "../../../Utilities/Time.h"
#include "../../../Utilities/Random.h"
#include "../../../ObjectManager/Object/Object.h"
#include "../../Physics/Transform/Transform.h"
#include "../../../Component/ComponentFactory/ComponentFactory.h"

/******************************************************************************/
/*!
\brief - ParticleBuilder constructor
\param Owner - Owner of this Component
\param key - ComponentType
\return new Particle Component
*/
/******************************************************************************/
Component* ParticleBuilder::BuildComponent(Object* Owner, ComponentType key) const {
	return new Particle(Owner, key);
};

/******************************************************************************/
/*!
\brief - Particle constructor
\param Owner - Owner of this Component
\param key - ComponentType
*/
/******************************************************************************/
Particle::Particle(Object* Owner, ComponentType key) :
    Component(Owner, key), EmissionRate(360), p_speed(1.f), active(true), count(0), countCheck(0), Time(0), EndScale(0),
    scaleMinusValue(0), particleRenderType(ADDITIVE), SpinCheck(true), ForcedQuit(false), laser_length(200), Player_Angle(0)
{
	// Preset transform
	if (!m_Owner->HasComponent(CT_TRANSFORM))
		m_Owner->AddComponent(ComponentFactory::CreateComponent(m_Owner, CT_TRANSFORM));

    this->init();
}

/******************************************************************************/
/*!
\brief - Particle Destructor
*/
/******************************************************************************/
Particle::~Particle(void)
{
    particles.clear();
}

/******************************************************************************/
/*!
\brief - Initialize Particle info
*/
/******************************************************************************/
void Particle::init()
{
}

/******************************************************************************/
/*!
\brief - Update Particle info
\param dt - delta time
*/
/******************************************************************************/
void Particle::Update(GLfloat dt)
{
	// Set new dt here
	float new_dt = m_Owner->GetdtOffset() * dt;

    if (active == true)
    {
        if(particleType == P_LASER)
            //Laser(new_dt);
			Normal(new_dt);
        else if (particleType == P_BLOW || particleType == P_NORMAL)
            Blow(new_dt);
        else if (particleType != P_BLOW)
            Normal(new_dt);

            
    }
    else
    {
        for (GLuint i = 0; i < EmissionRate; ++i)
            particles[i].Life = 0;
        SetUnitsPosition(vec2(1000.f, 1000.f));
    }

}

/******************************************************************************/
/*!
\brief - setting whole particle units with input
\param position - setting whole particle units in this position
*/
/******************************************************************************/
void Particle::SetUnitsPosition(vec2 position)
{
    for (GLuint i = 0; i < EmissionRate; ++i)
    {
        particles[i].Position.x = position.x;
        particles[i].Position.y = position.y;
    }
}

/******************************************************************************/
/*!
\brief - force quitting the particle update
*/
/******************************************************************************/
void Particle::ForceQuitting(void)
{
	for (GLuint i = 0; i < EmissionRate; ++i)
	{
		particles[i].Life = 0.f;
		particles[i].Position.x = 2000.f;
		particles[i].Color.w = 0;
	}
	ForcedQuit = true;
}

/******************************************************************************/
/*!
\brief - update laser with this function
\param dt - delta time
*/
/******************************************************************************/
void Particle::Laser(float dt)
{
    // Loop Through All The Particles
    for (GLuint i = 0; i < EmissionRate; ++i)
    {
        Unit &p = particles[i];

        if (p.Life > 0.f) {
            ColorChange = (ColorInit - ColorEnd) * dt;

            // Reduce Particles Life By 'Dt'
            p.Life -= dt;
            p.Color -= ColorChange;

            p.Position.x += p.Velocity.x * (dt);
            p.Position.y += p.Velocity.y * (dt);
            p.Position.x += (Gravity.x / 5.f) * dt;
            p.Position.y += (Gravity.y / 5.f) * dt;

            if (ScaleValue.x < EndScale.x)
            {
                scaleMinusValue = (EndScale - ScaleValue) * dt;
                if (p.Scale.x < EndScale.x)
                    p.Scale = vec2(p.Scale.x + scaleMinusValue.x, p.Scale.y + scaleMinusValue.y);
                else
                    p.Scale = vec2(EndScale.x, EndScale.y);
            }
            else
            {
                scaleMinusValue = (ScaleValue - EndScale) * dt;
                if (p.Scale.x > EndScale.x)
                    p.Scale = vec2(p.Scale.x - scaleMinusValue.x, p.Scale.y - scaleMinusValue.y);
                else
                    p.Scale = vec2(EndScale.x, EndScale.y);
            }


            if (SpinCheck == true)
                p.Angle += 5;
        }

        // If Particle Is Burned Out
        else if (p.Life <= 0.0f && p.Active == true)
        {
            if (ForcedQuit == true)
                p.Active = false;
            else if (count != 0)
            {
                p.countCheck++;
                if (count < p.countCheck)
                    p.Active = false;
            }

            p.Scale = vec2(ScaleValue.x, ScaleValue.y);

            p.Position.x = Random::GetInstance().GetRandomFloat(p_position.x - EmitArea.x, p_position.x + EmitArea.x);
            p.Position.y = Random::GetInstance().GetRandomFloat(p_position.y - EmitArea.y, p_position.y + EmitArea.y);

			p.Position.x += (laser_length/2 + 25);

            // Give It New Life
            p.Life = Random::GetInstance().GetRandomFloat(LifeInit - LifeVariable, LifeInit + LifeVariable);
            p.Angle = Random::GetInstance().GetRandomInt(AngleInit - AngleVariable, AngleInit + AngleVariable);

            float x = cos(Math::DegToRad(float(p.Angle)));
            float y = sin(Math::DegToRad(float(p.Angle)));

            int speed = Random::GetInstance().GetRandomInt(SpeedInitValue - SpeedVariable, SpeedInitValue + SpeedVariable);
            p.Velocity.x = (speed * x) / 5.f;
            p.Velocity.y = (speed * y) / 5.f;

            p.Color = ColorInit;

            Time = 1.f;

            if (SpinCheck == true)
                p.Angle = Random::GetInstance().GetRandomInt(0, 180);

        }

        if (p.Active == false)
        {
            p.Life = 0;
            p.Position = 0;
            p.Velocity = 0;
            p.countCheck = 0;
        }
    }

    if (count == 0)
        countCheck = 0;
}

/******************************************************************************/
/*!
\brief - update blow with this function
\param dt - delta time
*/
/******************************************************************************/
void Particle::Blow(float dt)
{
    // Loop Through All The Particles
    for (GLuint i = 0; i < EmissionRate; ++i)
    {
        Unit &p = particles[i];

        if (p.Life > 0.f) 
        {
            ColorChange = (ColorInit - ColorEnd) * dt;

            // Reduce Particles Life By 'Dt'
            p.Life -= dt;
            p.Color -= ColorChange;

            p.Position.x += p.Velocity.x * (dt);
            p.Position.y += p.Velocity.y * (dt);
            p.Position.x += (Gravity.x / 5.f) * dt;
            p.Position.y += (Gravity.y / 5.f) * dt;

            if (ScaleValue.x < EndScale.x)
            {
                scaleMinusValue = (EndScale - ScaleValue) * dt;
                if (p.Scale.x < EndScale.x)
                    p.Scale = vec2(p.Scale.x + scaleMinusValue.x, p.Scale.y + scaleMinusValue.y);
                else
                    p.Scale = vec2(EndScale.x, EndScale.y);
            }
            else
            {
                scaleMinusValue = (ScaleValue - EndScale) * dt;
                if (p.Scale.x > EndScale.x)
                    p.Scale = vec2(p.Scale.x - scaleMinusValue.x, p.Scale.y - scaleMinusValue.y);
                else
                    p.Scale = vec2(EndScale.x, EndScale.y);
            }

        }

        // If Particle Is Burned Out
        else if (p.Life <= 0.0f && p.Active == true)
        {
            if (ForcedQuit == true)
                p.Active = false;
            else if (count != 0)
            {
                p.countCheck++;
                if (count < p.countCheck)
                    p.Active = false;
            }

            p.Scale = vec2(ScaleValue.x, ScaleValue.y);

            p.Position.x = Random::GetInstance().GetRandomFloat(p_position.x - EmitArea.x, p_position.x + EmitArea.x);
            p.Position.y = Random::GetInstance().GetRandomFloat(p_position.y - EmitArea.y, p_position.y + EmitArea.y);

            // Give It New Life
            p.Life = Random::GetInstance().GetRandomFloat(LifeInit - LifeVariable, LifeInit + LifeVariable);
            p.Angle = Random::GetInstance().GetRandomInt(AngleInit - AngleVariable, AngleInit + AngleVariable);

            if (i < 40)
                p.Angle += 0;
            else if (i < 80)
                p.Angle += 60;
            else if (i < 120)
                p.Angle += 120;
            else if (i < 160)
                p.Angle += 180;
            else if (i < 200)
                p.Angle += 240;
            else if (i < 240)
                p.Angle += 300;

            float x = cos(Math::DegToRad(float(p.Angle)));
            float y = sin(Math::DegToRad(float(p.Angle)));

            int speed = Random::GetInstance().GetRandomInt(SpeedInitValue - SpeedVariable, SpeedInitValue + SpeedVariable);
            p.Velocity.x = (speed * x) / 5.f;
            p.Velocity.y = (speed * y) / 5.f;

            p.Color = ColorInit;

            Time = 1.f;
        }

        if (p.Active == false)
        {
            p.Life = 0;
            p.Position = 0;
            p.Velocity = 0;
            p.countCheck = 0;
        }
    }

    if (count == 0)
        countCheck = 0;
}

/******************************************************************************/
/*!
\brief - update usual normal particles with this function
\param dt - delta time
*/
/******************************************************************************/
void Particle::Normal(float dt)
{
    // Loop Through All The Particles
    for (GLuint i = 0; i < EmissionRate; ++i)
    {
        Unit &p = particles[i];

        if (p.Life > 0.f) {
            ColorChange = (ColorInit - ColorEnd) * dt;

            // Reduce Particles Life By 'Dt'
            p.Life -= dt;
            p.Color -= ColorChange;

            p.Position.x += p.Velocity.x * (dt);
            p.Position.y += p.Velocity.y * (dt);
            p.Position.x += (Gravity.x / 5.f) * dt;
            p.Position.y += (Gravity.y / 5.f) * dt;

            //p.Position.x += p.Velocity.x * (dt);
            //p.Position.y += p.Velocity.y * (dt);
            //p.Position.x += (Gravity.x / 5.f) * dt * dt;
            //p.Position.y += (Gravity.y / 5.f) * dt * dt;

            if (ScaleValue.x < EndScale.x)
            {
                scaleMinusValue = (EndScale - ScaleValue) * dt;
                if (p.Scale.x < EndScale.x)
                    p.Scale = vec2(p.Scale.x + scaleMinusValue.x, p.Scale.y + scaleMinusValue.y);
                else
                    p.Scale = vec2(EndScale.x, EndScale.y);
            }
            else
            {
                scaleMinusValue = (ScaleValue - EndScale) * dt;
                if (p.Scale.x > EndScale.x)
                    p.Scale = vec2(p.Scale.x - scaleMinusValue.x, p.Scale.y - scaleMinusValue.y);
                else
                    p.Scale = vec2(EndScale.x, EndScale.y);
            }


            if(SpinCheck == true)
                p.Angle += 5;
        }

        // If Particle Is Burned Out
        else if (p.Life <= 0.0f && p.Active == true)
        {
            if (ForcedQuit == true)
                p.Active = false;
            else if (count != 0)
            {
                p.countCheck++;
                if (count < p.countCheck)
                    p.Active = false;
            }

            p.Scale = vec2(ScaleValue.x, ScaleValue.y);
            
            p.Position.x = Random::GetInstance().GetRandomFloat(p_position.x - EmitArea.x, p_position.x + EmitArea.x);
            p.Position.y = Random::GetInstance().GetRandomFloat(p_position.y - EmitArea.y, p_position.y + EmitArea.y);

            // Give It New Life
            p.Life = Random::GetInstance().GetRandomFloat(LifeInit - LifeVariable, LifeInit + LifeVariable);
            p.Angle = Random::GetInstance().GetRandomInt(AngleInit - AngleVariable, AngleInit + AngleVariable);

            float x = cos(Math::DegToRad(float(p.Angle)));
            float y = sin(Math::DegToRad(float(p.Angle)));

            int speed = Random::GetInstance().GetRandomInt(SpeedInitValue - SpeedVariable, SpeedInitValue + SpeedVariable);
            p.Velocity.x = (speed * x) / 5.f;
            p.Velocity.y = (speed * y) / 5.f;

            p.Color = ColorInit;

            Time = 1.f;

			if (SpinCheck == true)
				p.Angle = Random::GetInstance().GetRandomInt(0, 180);
			else if (particleType == P_PLAYER)
				p.Angle = Player_Angle;

        }
        
        if (p.Active == false)
        {
            p.Life = 0;
            p.Position = 0;
            p.Velocity = 0;
            p.countCheck = 0;
        }
    }

    if (count == 0)
        countCheck = 0;
}

/******************************************************************************/
/*!
\brief - make particle work again
*/
/******************************************************************************/
void Particle::Restore()
{
    for (GLuint i = 0; i < EmissionRate; ++i)
    {
        Unit &p = particles[i];
        p.Active = true;
        p.countCheck = 0;
    }
    ForcedQuit = false;
}

/******************************************************************************/
/*!
\brief - setting texture
\param texture - setting the particles texture
*/
/******************************************************************************/
void Particle::SetTexture(Texture* texture)
{
	m_texture = texture;
}

/******************************************************************************/
/*!
\brief - getting texture
\return m_texture - getting the particles texture
*/
/******************************************************************************/
Texture* Particle::GetTexture(void) const
{
	return m_texture;
}

/******************************************************************************/
/*!
\brief - setting color
\param color - setting the color
*/
/******************************************************************************/
void Particle::SetColor(const vec4& color)
{
	m_color = color;
}

/******************************************************************************/
/*!
\brief - getting color
\return m_color - getting the color
*/
/******************************************************************************/
vec4 Particle::GetColor(void) const
{
	return m_color;
}

/******************************************************************************/
/*!
\brief - Change the value of the particle
*/
/******************************************************************************/
void Particle::ChangeResolution(int cr)
{
    SpeedInitValue *= cr;
    SpeedVariable *= cr;
    Gravity.x *= cr;
    Gravity.y *= cr;
    ScaleValue.x *= cr;
    ScaleValue.y *= cr;
    EndScale.x *= cr;
    EndScale.y *= cr;
    EmitArea.x *= cr;
    EmitArea.y *= cr;
}

/******************************************************************************/
/*!
\brief - setting variables value for particle
\param p_type - Get the type of particle to set
*/
/******************************************************************************/
void Particle::SetParticleVariables(ParticleType p_type)
{
    switch (p_type)
    {
    case P_AFTERIMAGE:
        AngleInit = 69,
        AngleVariable = 0,
        SpeedInitValue = 0,
        SpeedVariable = 0,
        LifeInit = 0.3f,
        LifeVariable = 0.2f,
        ColorInit.x = 0.f,
        ColorInit.y = 0.f,
        ColorInit.z = 0.2f,
        ColorInit.w = 0.77f,
        ColorEnd.x = 0.8f,
        ColorEnd.y = 0.2f,
        ColorEnd.z = 0.f,
        ColorEnd.w = 0.99f,
        Gravity.x = 0,
        Gravity.y = 0,
        ScaleValue.x = 60,
        ScaleValue.y = 60,
        EndScale.x = 100,
        EndScale.y = 100,
        EmitArea.x = 0,
        EmitArea.y = 0,
        count = 0;
        ForcedQuit = true;
        EmissionRate = 25;
        SpinCheck = true;
        // Create this->EmissionRate default particle instances
        for (GLuint i = 0; i < EmissionRate; ++i)
            particles.push_back(Unit());
        break;
    case P_LANTERN:
        AngleInit = 0,
        AngleVariable = 0,
        SpeedVariable = 20,
        LifeInit = 1,
        LifeVariable = 0.9f,
        ColorInit.x = 0.8f,
        ColorInit.y = 0.2f,
        ColorInit.z = 0.2f,
        ColorInit.w = 1,
        ColorEnd.x = 0.5f,
        ColorEnd.y = 0.2f,
        ColorEnd.z = 0.5f,
        ColorEnd.w = 1,
        Gravity.x = 20,
        Gravity.y = 0,
        ScaleValue.x = 25,
        ScaleValue.y = 15,
        EndScale.x = 25,
        EndScale.y = 15,
        EmitArea.x = 0,
        EmitArea.y = 6,
        count = 5,
        SpinCheck = false;
        EmissionRate = 200;
        // Create this->EmissionRate default particle instances
        for (GLuint i = 0; i < EmissionRate; ++i)
            particles.push_back(Unit());
        break;
    case P_RADAR:
        AngleInit = 90,
        AngleVariable = 0,
        SpeedInitValue = 0,
        SpeedVariable = 0,
        LifeInit = 1.f,
        LifeVariable = 0.9f,
        ColorInit.x = 1.f,
        ColorInit.y = 0.2f,
        ColorInit.z = 0.2f,
        ColorInit.w = 1,
        ColorEnd.x = 0,
        ColorEnd.y = 0,
        ColorEnd.z = 0,
        ColorEnd.w = 1,
        Gravity.x = 0,
        Gravity.y = 0,
        ScaleValue.x = 10,
        ScaleValue.y = 10,
        EndScale.x = 300,
        EndScale.y = 300,
        EmitArea.x = 0,
        EmitArea.y = 0,
        count = 2;
        ForcedQuit = true;
        EmissionRate = 25;
        // Create this->EmissionRate default particle instances
        for (GLuint i = 0; i < EmissionRate; ++i)
            particles.push_back(Unit());
        break;
    case P_SPARK:
        AngleInit = 69,
        AngleVariable = 32,
        SpeedInitValue = 461,
        SpeedVariable = 197,
        LifeInit = 0.15f,
        LifeVariable = 0.1f,
        ColorInit.x = 1.f,
        ColorInit.y = 0.8f,
        ColorInit.z = 0.2f,
        ColorInit.w = 1,
        ColorEnd.x = 1.f,
        ColorEnd.y = 0.6f,
        ColorEnd.z = 0.4f,
        ColorEnd.w = 1.f,
        Gravity.x = 0,
        Gravity.y = 0,
        ScaleValue.x = 10,
        ScaleValue.y = 10,
        EndScale.x = 5,
        EndScale.y = 5,
        EmitArea.x = 2,
        EmitArea.y = 3,
        count = 1;
        ForcedQuit = true;
        EmissionRate = 25;
        // Create this->EmissionRate default particle instances
        for (GLuint i = 0; i < EmissionRate; ++i)
            particles.push_back(Unit());
        break;
    case P_BLOW:
        AngleInit = 90,
        AngleVariable = 16,
        SpeedInitValue = 761,
        SpeedVariable = 197,
        LifeInit = 0.15f,
        LifeVariable = 0.05f,
        ColorInit.x = 1.f,
        ColorInit.y = 0.8f,
        ColorInit.z = 0.2f,
        ColorInit.w = 1,
        ColorEnd.x = 1.f,
        ColorEnd.y = 0.6f,
        ColorEnd.z = 0.4f,
        ColorEnd.w = 1.f,
        Gravity.x = 0,
        Gravity.y = 0,
        ScaleValue.x = 15,
        ScaleValue.y = 15,
        EndScale.x = 5,
        EndScale.y = 5,
        EmitArea.x = 1,
        EmitArea.y = 1,
        count = 1;
        ForcedQuit = true;
        EmissionRate = 240;
        // Create this->EmissionRate default particle instances
        for (GLuint i = 0; i < EmissionRate; ++i)
            particles.push_back(Unit());
        break;
    case P_BOMB:
        AngleInit = 90,
        AngleVariable = 360,
        SpeedInitValue = 1500,
        SpeedVariable = 0,
        LifeInit = 1.f,
        LifeVariable = 0,
        ColorInit.x = 0.75f,
        ColorInit.y = 0.25f,
        ColorInit.z = 0.11f,
        ColorInit.w = 1,
        ColorEnd.x = 0,
        ColorEnd.y = 0,
        ColorEnd.z = 0,
        ColorEnd.w = 1,
        Gravity.x = 0,
        Gravity.y = 0,
        ScaleValue.x = 35,
        ScaleValue.y = 35,
        EndScale.x = 0,
        EndScale.y = 0,
        EmitArea.x = 10,
        EmitArea.y = 10,
        count = 1;
        ForcedQuit = true;
        active = false;
        EmissionRate = 360;
        // Create this->EmissionRate default particle instances
        for (GLuint i = 0; i < EmissionRate; ++i)
            particles.push_back(Unit());
        break;
    case P_LASER:
        AngleInit = 90,
        AngleVariable = 10,
        SpeedInitValue = 18,
        SpeedVariable = 0,
        LifeInit = 0.3f,
        LifeVariable = 0.2f,
        ColorInit.x = 1.f,
        ColorInit.y = 0.2f,
        ColorInit.z = 0.3f,
        ColorInit.w = 0.6f,
        ColorEnd.x = 0,
        ColorEnd.y = 0,
        ColorEnd.z = 0,
        ColorEnd.w = 0,
        Gravity.x = 0,
        Gravity.y = 0,
        ScaleValue.x = 35,
        ScaleValue.y = 35,
        EndScale.x = 0,
        EndScale.y = 0,
        EmitArea.x = 100,
        EmitArea.y = 20,
        count = 0;
        ForcedQuit = true;
        EmissionRate = 25;
        SpinCheck = true;
        // Create this->EmissionRate default particle instances
        for (GLuint i = 0; i < EmissionRate; ++i)
            particles.push_back(Unit());
        break;

	case P_RUN:
		AngleInit = 90,
		AngleVariable = 0,
		SpeedInitValue = 18,
		SpeedVariable = 0,
		LifeInit = 0.3f,
		LifeVariable = 0.3f,
		ColorInit.x = 0.6f,
		ColorInit.y = 0.4f,
		ColorInit.z = 0.2f,
		ColorInit.w = 0.4f,
		ColorEnd.x = 0.f,
		ColorEnd.y = 0.f,
		ColorEnd.z = 0.f,
		ColorEnd.w = 0.f,
		Gravity.x = 0,
		Gravity.y = 0,
		ScaleValue.x = 10,
		ScaleValue.y = 10,
		EndScale.x = 1,
		EndScale.y = 1,
		EmitArea.x = 20,
		EmitArea.y = 20,
		count = 1;
		ForcedQuit = true;
		EmissionRate = 25;
		SpinCheck = true;
		// Create this->EmissionRate default particle instances
		for (GLuint i = 0; i < EmissionRate; ++i)
			particles.push_back(Unit());
		break;

	case P_PLAYER:
		AngleInit = 90,
		AngleVariable = 0,
		SpeedInitValue = 18,
		SpeedVariable = 0,
		LifeInit = 0.15f,
		LifeVariable = 0.15f,
		ColorInit.x = 1.f,
		ColorInit.y = 1.f,
		ColorInit.z = 1.f,
		ColorInit.w = 1.f,
		ColorEnd.x = 1.f,
		ColorEnd.y = 1.f,
		ColorEnd.z = 1.f,
		ColorEnd.w = 1.f,
		Gravity.x = 0,
		Gravity.y = 0,
		ScaleValue.x = 100,
		ScaleValue.y = 100,
		EndScale.x = 100,
		EndScale.y = 100,
		EmitArea.x = 1,
		EmitArea.y = 1,
		count = 1;
		ForcedQuit = true;
		EmissionRate = 7;
		SpinCheck = false;
		// Create this->EmissionRate default particle instances
		for (GLuint i = 0; i < EmissionRate; ++i)
			particles.push_back(Unit());
		break;

	case P_INDICATOR:
		AngleInit = 90,
		AngleVariable = 0,
		SpeedInitValue = 0,
		SpeedVariable = 0,
		LifeInit = 0.5f,
		LifeVariable = 0.4f,
		ColorInit.x = 0.2f,
		ColorInit.y = 0.2f,
		ColorInit.z = 1.f,
		ColorInit.w = 1,
		ColorEnd.x = 0,
		ColorEnd.y = 0,
		ColorEnd.z = 0,
		ColorEnd.w = 1,
		Gravity.x = 0,
		Gravity.y = 0,
		ScaleValue.x = 60,
		ScaleValue.y = 60,
		EndScale.x = 120,
		EndScale.y = 120,
		EmitArea.x = 0,
		EmitArea.y = 0,
		count = 2;
		ForcedQuit = true;
		EmissionRate = 10;
		// Create this->EmissionRate default particle instances
		for (GLuint i = 0; i < EmissionRate; ++i)
			particles.push_back(Unit());
		break;

	case P_NORMAL:
        AngleInit = 90,
        AngleVariable = 16,
        SpeedInitValue = 1500,
        SpeedVariable = 197,
        LifeInit = 0.45f,
        LifeVariable = 0.05f,
        ColorInit.x = 1.f,
        ColorInit.y = 0.8f,
        ColorInit.z = 0.2f,
        ColorInit.w = 1,
        ColorEnd.x = 1.f,
        ColorEnd.y = 0.6f,
        ColorEnd.z = 0.4f,
        ColorEnd.w = 1.f,
        Gravity.x = 0,
        Gravity.y = 0,
        ScaleValue.x = 30,
        ScaleValue.y = 30,
        EndScale.x = 15,
        EndScale.y = 15,
        EmitArea.x = 1,
        EmitArea.y = 1,
        count = 1;
        ForcedQuit = true;
        EmissionRate = 240;
        //particleRenderType = NORMALPARTICLE;
		// Create this->EmissionRate default particle instances
		for (GLuint i = 0; i < EmissionRate; ++i)
			particles.push_back(Unit());
		break;

    case P_CHARGING:
        AngleInit = 270,
        AngleVariable = 180,
        SpeedInitValue = 530,
        SpeedVariable = 100,
        LifeInit = 0.25f,
        LifeVariable = 0.05f,
        ColorInit.x = 0.2f,
        ColorInit.y = 0.2f,
        ColorInit.z = 1.f,
        ColorInit.w = 1.0f,
        ColorEnd.x = 0.2f,
        ColorEnd.y = 0.4f,
        ColorEnd.z = 1.f,
        ColorEnd.w = 1.f,
        Gravity.x = 0,
        Gravity.y = 0,
        ScaleValue.x = 45,
        ScaleValue.y = 45,
        EndScale.x = 0,
        EndScale.y = 0,
        EmitArea.x = 15,
        EmitArea.y = 10,
        count = 1;
        ForcedQuit = true;
        EmissionRate = 165;
        SpinCheck = true;
        //particleRenderType = ParticleRenderType::NORMALPARTICLE;
        //particleRenderType = NORMALPARTICLE;
        // Create this->EmissionRate default particle instances
        for (GLuint i = 0; i < EmissionRate; ++i)
            particles.push_back(Unit());
        break;

    case P_CHARGESHOT:
        AngleInit = 76,
        AngleVariable = 180,
        SpeedInitValue = 1432,
        SpeedVariable = 20,
        LifeInit = 0.5f,
        LifeVariable = 0.1f,
        ColorInit.x = 0.2f,
        ColorInit.y = 0.4f,
        ColorInit.z = 1.f,
        ColorInit.w = 0.89f,
        ColorEnd.x = 0.0f,
        ColorEnd.y = 0.0f,
        ColorEnd.z = 0.0f,
        ColorEnd.w = 1.f,
        Gravity.x = 0,
        Gravity.y = 0,
        ScaleValue.x = 50,
        ScaleValue.y = 50,
        EndScale.x = 100,
        EndScale.y = 100,
        EmitArea.x = 1,
        EmitArea.y = 1,
        count = 1;
        ForcedQuit = true;
        EmissionRate = 165;
        SpinCheck = true;
        //particleRenderType = ParticleRenderType::NORMALPARTICLE;
        //particleRenderType = NORMALPARTICLE;
        // Create this->EmissionRate default particle instances
        for (GLuint i = 0; i < EmissionRate; ++i)
            particles.push_back(Unit());
        break;

    default:
        std::cout << "ERROR! NOT REGISTERED PARTICLE TYPE" << std::endl;
        break;
    }
}
