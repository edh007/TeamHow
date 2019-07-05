/******************************************************************************/
/*!
\file   ParticleManager.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/01/06(yy/mm/dd)

\description
Contains ParticleManager logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "ParticleManager.h"
#include "../../../BaseData/BaseEnigne.h"
#include "../Enemy/Enemy.h"
#include "../Player/SuperPower.h"

/******************************************************************************/
/*!
\brief - ParticleManagerBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* ParticleManagerBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new ParticleManager(Owner, key);
}

/******************************************************************************/
/*!
\brief - ParticleManager constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
ParticleManager::ParticleManager(Object* Owner, LogicType key)
: GameLogic(Owner, key)
{}

/******************************************************************************/
/*!
\brief - Load ParticleManager info
\param data - json parser
*/
/******************************************************************************/
void ParticleManager::Load(const Json::Value& data)
{
    if (!strcmp((data)["ParticleType"].asCString(), "AFTERIMAGE"))
        p_particleSave = P_AFTERIMAGE;

    else if (!strcmp((data)["ParticleType"].asCString(), "BOMB"))
        p_particleSave = P_BOMB;

    else if (!strcmp((data)["ParticleType"].asCString(), "LANTERN"))
    {
        p_particleSave = P_LANTERN;
        if (data.isMember("Range") &&
            data["Range"].isNumeric())
            range = data["Range"].asFloat();
    }
    else if (!strcmp((data)["ParticleType"].asCString(), "SPARK"))
        p_particleSave = P_SPARK;

    else if (!strcmp((data)["ParticleType"].asCString(), "RADAR"))
        p_particleSave = P_RADAR;

    else if (!strcmp((data)["ParticleType"].asCString(), "BLOW"))
        p_particleSave = P_BLOW;
    else if (!strcmp((data)["ParticleType"].asCString(), "LASER"))
        p_particleSave = P_LASER;
	else if (!strcmp((data)["ParticleType"].asCString(), "RUN"))
		p_particleSave = P_RUN;
	else if (!strcmp((data)["ParticleType"].asCString(), "PLAYER"))
		p_particleSave = P_PLAYER;
	else if (!strcmp((data)["ParticleType"].asCString(), "INDICATOR"))
		p_particleSave = P_INDICATOR;
	else if (!strcmp((data)["ParticleType"].asCString(), "NORMAL"))
        p_particleSave = P_NORMAL;
    else if (!strcmp((data)["ParticleType"].asCString(), "CHARGING"))
        p_particleSave = P_CHARGING;
    else if (!strcmp((data)["ParticleType"].asCString(), "CHARGESHOT"))
        p_particleSave = P_CHARGESHOT;
}

/******************************************************************************/
/*!
\brief - Initialize ParticleManager info
*/
/******************************************************************************/
void ParticleManager::Init(void)
{
    //Need to Polish
    //Check Do not Create once again
    m_particleOwner = new Object(AT_NONE, m_OBM);
    m_particleOwner->AddComponent(ComponentFactory::CreateComponent(m_particleOwner, CT_TRANSFORM));
    m_particleOwner->AddComponent(ComponentFactory::CreateComponent(m_particleOwner, CT_PARTICLE));
    m_particle = m_particleOwner->GetComponent<Particle>(CT_PARTICLE);
    m_particle->particleType = p_particleSave;
    m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->SetScale(m_particle->ScaleValue);
    m_particle->SetParticleVariables(p_particleSave);

    if (p_particleSave == P_AFTERIMAGE)
    {
        m_particleOwner->AddComponent(ComponentFactory::CreateComponent(m_particleOwner, CT_RIGIDBODY));

        m_particle->SetTexture(m_GSM->GetGLManager()->GetTexture("Mark"));

        sptPos = m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
        m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(sptPos.x, sptPos.y, sptPos.z + 10));
        //Each Unit's initialize position.
        m_particle->p_position = m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();

        m_particleOwner->GetComponent<RigidBody>(CT_RIGIDBODY)->ActivateResponse(false);
        m_particleOwner->GetComponent<RigidBody>(CT_RIGIDBODY)->SetShape(BOX);
        m_particleOwner->AddLogic(LogicFactory::CreateLogic(m_particleOwner, SLOW));
    }
    else if (p_particleSave == P_BOMB)
    {
        m_particle = m_particleOwner->GetComponent<Particle>(CT_PARTICLE);

        //m_particle->GetComponent<Transform>(CT_TRANSFORM)->GetPosition(); Emitter's Position, uses for physics
        m_particle->SetTexture(m_OBM->GetTexture("Smoke"));
        //Each Unit's initialize position.
        m_particle->p_position = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();

        m_particleOwner->AddLogic(LogicFactory::CreateLogic(m_particleOwner, SLOW));
    }
    else if (p_particleSave == P_LANTERN)
    {
        m_particleOwner->AddComponent(ComponentFactory::CreateComponent(m_particleOwner, CT_RIGIDBODY));

        sptPos = m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();

        m_particle->SetTexture(m_GSM->GetGLManager()->GetTexture("particle"));

        m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(sptPos);
        if (m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->GetRotation() == 90)
            m_particle->p_position = vec3(sptPos.x, sptPos.y + 20.f, sptPos.z + 10);
        else
            m_particle->p_position = vec3(sptPos.x + 20.f, sptPos.y, sptPos.z + 10);
        m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->SetScale(m_particle->ScaleValue);

        m_particle->SpeedVariable = 20,
        m_particle->LifeInit = 1,
        m_particle->LifeVariable = 0.9f,
        m_particle->count = 5,
        m_particle->Gravity.x = 20,

        m_particle->SpeedInitValue = int((range / (m_particle->LifeInit + m_particle->LifeVariable)) * 5.f - m_particle->SpeedVariable - m_particle->Gravity.x);
        workingTime = (m_particle->LifeInit) * m_particle->count;

        m_particleOwner->GetComponent<RigidBody>(CT_RIGIDBODY)->ActivateResponse(false);
        m_particleOwner->GetComponent<RigidBody>(CT_RIGIDBODY)->SetShape(BOX);
        SetAttackRangeOFF();
        m_particleOwner->AddLogic(LogicFactory::CreateLogic(m_particleOwner, SLOW));
        m_particleOwner->AddLogic(LogicFactory::CreateLogic(m_particleOwner, DAMAGE));
    }
    else if (p_particleSave == P_SPARK)
    {
        //m_particle->GetComponent<Transform>(CT_TRANSFORM)->GetPosition(); Emitter's Position, uses for physics
        m_particle->SetTexture(m_GSM->GetGLManager()->GetTexture("particle"));

        sptPos = m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
        m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(sptPos.x, sptPos.y, sptPos.z + 10));
        //Each Unit's initialize position.
        m_particle->p_position = m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
    }
    else if (p_particleSave == P_BLOW)
    {
        //m_particle->GetComponent<Transform>(CT_TRANSFORM)->GetPosition(); Emitter's Position, uses for physics
        m_particle->SetTexture(m_GSM->GetGLManager()->GetTexture("particle"));

        sptPos = m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
        m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(sptPos.x, sptPos.y, sptPos.z + 10));

        //Each Unit's initialize position.
        m_particle->p_position = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();

    }
    else if (p_particleSave == P_RADAR)
    {
        //m_particle->GetComponent<Transform>(CT_TRANSFORM)->GetPosition(); Emitter's Position, uses for physics
        m_particle->SetTexture(m_GSM->GetGLManager()->GetTexture("Line_Circle"));

        //Each Unit's initialize position.
        m_particle->p_position = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();

        m_particleOwner->AddLogic(LogicFactory::CreateLogic(m_particleOwner, SLOW));
        
    }
    else if (p_particleSave == P_LASER)
    {
        //m_particle->GetComponent<Transform>(CT_TRANSFORM)->GetPosition(); Emitter's Position, uses for physics
        m_particle->SetTexture(m_GSM->GetGLManager()->GetTexture("Stars"));

        //Each Unit's initialize position.
        m_particle->p_position = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();

        m_particleOwner->AddLogic(LogicFactory::CreateLogic(m_particleOwner, SLOW));

    }
	else if (p_particleSave == P_RUN)
	{
		//m_particle->GetComponent<Transform>(CT_TRANSFORM)->GetPosition(); Emitter's Position, uses for physics
		m_particle->SetTexture(m_GSM->GetGLManager()->GetTexture("Smoke"));

		//Each Unit's initialize position.
		//m_particle->p_position = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();

		m_particleOwner->AddLogic(LogicFactory::CreateLogic(m_particleOwner, SLOW));
	}

	else if (p_particleSave == P_PLAYER)
	{
		//m_particle->GetComponent<Transform>(CT_TRANSFORM)->GetPosition(); Emitter's Position, uses for physics
		m_particle->SetTexture(m_GSM->GetGLManager()->GetTexture("Player_Particle"));

		//Each Unit's initialize position.
		//m_particle->p_position = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();

		m_particleOwner->AddLogic(LogicFactory::CreateLogic(m_particleOwner, SLOW));
	}

	else if (p_particleSave == P_INDICATOR)
	{
		//m_particle->GetComponent<Transform>(CT_TRANSFORM)->GetPosition(); Emitter's Position, uses for physics
		m_particle->SetTexture(m_GSM->GetGLManager()->GetTexture("Line_Circle"));

		//Each Unit's initialize position.
		m_particle->p_position = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();

		m_particleOwner->AddLogic(LogicFactory::CreateLogic(m_particleOwner, SLOW));

	}

    else if (p_particleSave == P_NORMAL)
    {
		//m_particle->GetComponent<Transform>(CT_TRANSFORM)->GetPosition(); Emitter's Position, uses for physics
		m_particle->SetTexture(m_GSM->GetGLManager()->GetTexture("particle"));

        //Each Unit's initialize position.
    	m_particle->p_position = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();

    }
    else if (p_particleSave == P_CHARGING)
    {
        //m_particle->GetComponent<Transform>(CT_TRANSFORM)->GetPosition(); Emitter's Position, uses for physics
        m_particle->SetTexture(m_GSM->GetGLManager()->GetTexture("particle"));

        sptPos = m_GSM->GetGameData()->player->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
        m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(sptPos.x, sptPos.y, sptPos.z + 10));

        //Each Unit's initialize position.
        m_particle->p_position = sptPos;

    }
    else if (p_particleSave == P_CHARGESHOT)
    {
        //m_particle->GetComponent<Transform>(CT_TRANSFORM)->GetPosition(); Emitter's Position, uses for physics
        m_particle->SetTexture(m_GSM->GetGLManager()->GetTexture("Stars"));

        sptPos = m_GSM->GetGameData()->player->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
        m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(sptPos.x, sptPos.y, sptPos.z + 10));

        //Each Unit's initialize position.
        m_particle->p_position = sptPos;
    }

    m_OBM->AddObject(m_particleOwner);
}

/******************************************************************************/
/*!
\brief - Update ParticleManager info
\param dt - delta time
*/
/******************************************************************************/
void ParticleManager::Update(float /*dt*/)
{
    if (p_particleSave == P_AFTERIMAGE)
    {
    }
    else if (p_particleSave == P_BOMB)
    {
        if (m_particle->active && m_particle->ForcedQuit == true)
        {
            Restore();
        }
    }
    else if (p_particleSave == P_LANTERN)
    {
    }
    else if (p_particleSave == P_SPARK)
    {
    }
	else if (p_particleSave == P_PLAYER)
	{
		vec3 pos = m_GSM->GetGameData()->player_pos;
		m_particle->GetOwner()->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(pos.x, pos.y, 0.f));
		m_particle->p_position = vec3(pos.x, pos.y, 0.f);

		if (m_OBM->HasObject(m_GSM->GetGameData()->player_id))
		{
			m_particle->Player_Angle = static_cast<int>(m_GSM->GetGameData()->player->GetComponent<Transform>(CT_TRANSFORM)->GetRotation());
			if (m_GSM->GetGameData()->tmToggle == true)
				m_particle->Restore();
			else
				m_particle->ForceQuitting();
		}
		else
			m_particle->ForceQuitting();
	}
	else if (p_particleSave == P_RUN)
	{
		bool xInput = XboxInput::Instance()->IsConnected();
		vec3 pos = m_GSM->GetGameData()->player_pos; //m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
		//m_particle->p_position = vec3(pos.x, pos.y, pos.z);

		if (InputManager::GetInstance().KeyPressed(KEY_W) ||
			(xInput && XboxInput::Instance()->leftStickY > 0.5f))
		{
			m_particle->p_position = vec3(pos.x, pos.y- 50.f, pos.z);
			m_particle->Restore();
		}
		else if (InputManager::GetInstance().KeyPressed(KEY_A) ||
			(xInput && XboxInput::Instance()->leftStickX < -0.5f))
		{
			m_particle->p_position = vec3(pos.x+50.f, pos.y, pos.z);
			m_particle->Restore();
		}
		else if (InputManager::GetInstance().KeyPressed(KEY_S) ||
			(xInput && XboxInput::Instance()->leftStickY < -0.5f))
		{
			m_particle->p_position = vec3(pos.x, pos.y + 50.f, pos.z);
			m_particle->Restore();
		}
		else if (InputManager::GetInstance().KeyPressed(KEY_D) ||
			(xInput && XboxInput::Instance()->leftStickX > 0.5f))
		{
			m_particle->p_position = vec3(pos.x - 50.f, pos.y, pos.z);
			m_particle->Restore();
		}

		if (InputManager::GetInstance().KeyPressed(KEY_SHIFT) ||
            (xInput && XboxInput::Instance()->GetButtonPressed(XboxInput::Instance()->LEFT_SHOULDER)))
			m_particle->ForceQuitting();
	}
    else if (p_particleSave == P_BLOW)
    {
		//bool xInput = XboxInput::Instance()->IsConnected();

        // punch part
        vec3 pos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
        vec3 m_scale = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetScale();
        pos = Math::Rotation(pos + vec3(m_scale.x)* .5f,
            m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetRotation(), pos);

        //vec3 pos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
        m_particle->p_position = vec3(pos.x, pos.y, 10.f);
        
        if (m_GSM->GetGameData()->pnchTog == true)
            if (m_GSM->GetGameData()->player->GetComponent<Sprite>(CT_SPRITE)->currentFrame == 4)
            //if (InputManager::GetInstance().KeyTriggered(MOUSE_LEFT) ||
            //    (xInput && XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->XBOX_A)))
            m_particle->Restore();
        //else
        //    m_particle->ForceQuitting();
    }
    else if (p_particleSave == P_RADAR)
    {
		vec3 pos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
		m_particle->GetOwner()->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(pos.x, pos.y, 9.f));
		m_particle->p_position = vec3(pos.x, pos.y, 10.f);

		//if (InputManager::GetInstance().KeyTriggered(KEY_Q))
		if (m_GSM->GetGameData()->searchToggle && m_Owner->GetLogic<Enemy>(ENEMY)->GetAliveToggle())
			m_particle->Restore();
		else
			m_particle->ForceQuitting();
    }
	else if (p_particleSave == P_INDICATOR)
	{
		vec3 pos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
		m_particle->GetOwner()->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(pos.x, pos.y, 9.f));
		m_particle->p_position = vec3(pos.x, pos.y, 10.f);
	}
    else if (p_particleSave == P_LASER)
    {
        vec3 pos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
        vec3 scl = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetScale();
        if(scl.x > scl.y)
            m_particle->p_position = vec3(pos.x, pos.y, 9.f);
        else
            m_particle->p_position = vec3(pos.x, pos.y, 9.f);
    }
    else if (p_particleSave == P_NORMAL)
    {
        vec3 pos;
        vec3 m_scale;
        // punch part
        m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
        m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetScale();
        pos = Math::Rotation(pos + vec3(m_scale.x)* .5f,
            m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetRotation(), pos);

        //vec3 pos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
        m_particle->p_position = vec3(pos.x, pos.y, 10.f);

        bool xInput = XboxInput::Instance()->IsConnected();
        if (InputManager::GetInstance().KeyTriggered(MOUSE_LEFT) ||
            (xInput && XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->XBOX_A)))
            m_particle->Restore();
        else if (m_GSM->GetGameData()->sprPnchParticleTog == true)
            m_particle->Restore();
    }
    else if (p_particleSave == P_CHARGING)
    {
        //bool xInput = XboxInput::Instance()->IsConnected();

        // punch part
        if (m_OBM->HasObject(m_GSM->GetGameData()->player_id))
        {
            vec3 pos = m_GSM->GetGameData()->player->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
            vec3 m_scale = m_GSM->GetGameData()->player->GetComponent<Transform>(CT_TRANSFORM)->GetScale();
            pos = Math::Rotation(pos + vec3(m_scale.x)* .5f,
                m_GSM->GetGameData()->player->GetComponent<Transform>(CT_TRANSFORM)->GetRotation(), pos);

            //vec3 pos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
            m_particle->p_position = vec3(pos.x, pos.y, 10.f);

            if (!m_GSM->GetGameData()->searchToggle
				&& !m_GSM->GetGameData()->tmToggle
				&& m_GSM->GetGameData()->enoughPoint
				&& m_GSM->GetGameData()->dtPower
				&& m_GSM->GetGameData()->clicked)
                m_particle->Restore();
        }
    }
    else if (p_particleSave == P_CHARGESHOT)
    {
        vec3 pos;
        vec3 m_scale;
        if (m_OBM->HasObject(m_GSM->GetGameData()->player_id))
        {
            // punch part
            pos = m_GSM->GetGameData()->player->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
            m_scale = m_GSM->GetGameData()->player->GetComponent<Transform>(CT_TRANSFORM)->GetScale();
            pos = Math::Rotation(pos + vec3(m_scale.x)* .5f,
                m_GSM->GetGameData()->player->GetComponent<Transform>(CT_TRANSFORM)->GetRotation(), pos);

            //vec3 pos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
            m_particle->p_position = vec3(pos.x, pos.y, 10.f);

            if (m_GSM->GetGameData()->sprPnchParticleTog == true)
                m_particle->Restore();
        }
    }
}

/******************************************************************************/
/*!
\brief - Shutdown ParticleManager info
*/
/******************************************************************************/
void ParticleManager::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload ParticleManager info
*/
/******************************************************************************/
void ParticleManager::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - setting the type of particle
\param p_type - the type of particle
*/
/******************************************************************************/
void ParticleManager::SetParticleType(ParticleType p_type)
{
    p_particleSave = p_type;
    Init();
}

/******************************************************************************/
/*!
\brief - control active
\param value - setting it is active or not
*/
/******************************************************************************/
void ParticleManager::SetActive(bool check)
{
    m_particle->active = check;
}

/******************************************************************************/
/*!
\brief - settor of particle's emitter position
\param vec3 - value of position
*/
/******************************************************************************/
void ParticleManager::SetParticlePos(vec3 pos)
{
    m_particle->p_position = pos;
}

/******************************************************************************/
/*!
\brief - gettor of particle's rigidbody
\return RigidBody - rigid body of emitter
*/
/******************************************************************************/
RigidBody* ParticleManager::GetBody()
{
    return m_particleOwner->GetComponent<RigidBody>(CT_RIGIDBODY);
}

/******************************************************************************/
/*!
\brief - gettor of particle's emitter position
\return vec3 - value of position
*/
/******************************************************************************/
vec3 ParticleManager::GetEmitterPos()
{
    return m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
}

/******************************************************************************/
/*!
\brief - setting this particle's emitter position
\param pos - value of position
*/
/******************************************************************************/
void ParticleManager::SetEmitterPos(vec3 pos)
{
    m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(pos);
}

/******************************************************************************/
/*!
\brief - setting this particle quit
\param check - true or not
*/
/******************************************************************************/
void ParticleManager::SetParticleQuit(bool check)
{
    m_particle->ForcedQuit = check;
}

/******************************************************************************/
/*!
\brief - restore to work particle again
*/
/******************************************************************************/
void ParticleManager::Restore(void)
{
    if(m_particle->particleType == P_BOMB)
        m_particle->p_position = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
    m_particle->Restore();
}

/******************************************************************************/
/*!
\brief - gettor of range of this particle
\return range - value of range
*/
/******************************************************************************/
float ParticleManager::GetRange()
{
    return range;
}

/******************************************************************************/
/*!
\brief - gettor of SpeedInitValue of this particle
\return SpeedInitValue - SpeedInitValue of range
*/
/******************************************************************************/
float ParticleManager::GetSpeedInitValue()
{
    return float(m_particle->SpeedInitValue);
}

/******************************************************************************/
/*!
\brief - gettor of workingTime of this particle
\return workingTime - value of workingTime
*/
/******************************************************************************/
float ParticleManager::GetWorkingTime()
{
    return workingTime;
}

/******************************************************************************/
/*!
\brief - setting the range of this particle as on
\param dt - delta time
*/
/******************************************************************************/
void ParticleManager::SetAttackRangeON(float dt)
{
    if (m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetRotation() == 90)
    {
        float xValue;
        if (InputManager::GetInstance().KeyPressed(KEY_SHIFT))
            xValue = (m_particle->SpeedInitValue - m_particle->SpeedVariable + m_particle->Gravity.x) / 5.f * dt * m_Owner->GetdtOffset() * 0.1f;
        else
            xValue = (m_particle->SpeedInitValue + m_particle->SpeedVariable + m_particle->Gravity.x) / 5.f * dt * m_Owner->GetdtOffset();
        m_particle->ForcedQuit = false;
        float attackRangeY = (m_particle->EmitArea.y * 2.f) + m_particle->EndScale.y;

        float scaleX = m_particleOwner->GetComponent<RigidBody>(CT_RIGIDBODY)->GetScale().y + xValue;
        if (scaleX < range)
            m_particleOwner->GetComponent<RigidBody>(CT_RIGIDBODY)->SetScale(vec3(attackRangeY, scaleX, 0.f));
        else
            m_particleOwner->GetComponent<RigidBody>(CT_RIGIDBODY)->SetScale(vec3(attackRangeY, range, 0.f));
        m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(sptPos.x, sptPos.y + ((range*0.75f*0.5f) + 20.f), sptPos.z));

        if (m_Owner->GetLogic<BasicTrap>(TRAP)->trapCondition == OPERATION)
            m_particle->Restore();
        std::cout << "Scale : [" << m_particleOwner->GetComponent<RigidBody>(CT_RIGIDBODY)->GetScale().x << ", " << m_particleOwner->GetComponent<RigidBody>(CT_RIGIDBODY)->GetScale().y << " ]" << std::endl;
    }
    else
    {
        float xValue;
        if (InputManager::GetInstance().KeyPressed(KEY_SHIFT))
            xValue = (m_particle->SpeedInitValue - m_particle->SpeedVariable + m_particle->Gravity.x) / 5.f * dt * m_Owner->GetdtOffset() * 0.1f;
        else
            xValue = (m_particle->SpeedInitValue + m_particle->SpeedVariable + m_particle->Gravity.x) / 5.f * dt * m_Owner->GetdtOffset();
        m_particle->ForcedQuit = false;
        float attackRangeY = (m_particle->EmitArea.y * 2.f) + m_particle->EndScale.y;

        float scaleX = m_particleOwner->GetComponent<RigidBody>(CT_RIGIDBODY)->GetScale().x + xValue;
        if (scaleX < range)
            m_particleOwner->GetComponent<RigidBody>(CT_RIGIDBODY)->SetScale(vec3(scaleX, attackRangeY, 0.f));
        else
            m_particleOwner->GetComponent<RigidBody>(CT_RIGIDBODY)->SetScale(vec3(range, attackRangeY, 0.f));
        m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(sptPos.x + ((range*0.75f*0.5f) + 20.f), sptPos.y, sptPos.z));

        if (m_Owner->GetLogic<BasicTrap>(TRAP)->trapCondition == OPERATION)
            m_particle->Restore();
    }
}

/******************************************************************************/
/*!
\brief - setting the range of this particle as off
*/
/******************************************************************************/
void ParticleManager::SetAttackRangeOFF()
{
    if (m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->GetRotation() == 90)
    {
        m_particleOwner->GetComponent<RigidBody>(CT_RIGIDBODY)->SetScale(vec3(0.f, 0.f, 0.f));
        m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(sptPos.x, sptPos.y + 20.f, sptPos.z + 10));
        m_particle->ForcedQuit = true;
    }
    else
    {
        m_particleOwner->GetComponent<RigidBody>(CT_RIGIDBODY)->SetScale(vec3(0.f, 0.f, 0.f));
        m_particleOwner->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(vec3(sptPos.x + 20.f, sptPos.y, sptPos.z + 10));
        m_particle->ForcedQuit = true;
    }
}