/******************************************************************************/
/*!
\file   Turret.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2016/12/04(yy/mm/dd)

\description
Contains Turret logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Turret.h"
#include "../../../BaseData/BaseEnigne.h"
#include "../Particle/ParticleManager.h"
#include "TurretTarget.h"

/******************************************************************************/
/*!
\brief - TurretBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* TurretBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Turret(Owner, key);
}

/******************************************************************************/
/*!
\brief - Turret constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Turret::Turret(Object* Owner, LogicType key)
: GameLogic(Owner, key)
{}

/******************************************************************************/
/*!
\brief - Load Turret info
\param data - json parser
*/
/******************************************************************************/
void Turret::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize Turret info
*/
/******************************************************************************/
void Turret::Init(void)
{
    active = false;
    activeTime = 0;
    collidedTime = 0;

    m_OBM->GetObjects(AT_PLAYER, player);
    if (player.size())
        player_id = player[0]->GetID();
    else
        player_id = 0;

    //shooter = new Sprite(AT_AIM, m_OBM);
    //shooter->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition());
    //shooter->SetScale(vec3(10, 10, 0));

    //shooter->;
    //body = shooter->GetComponent<RigidBody>(CT_RIGIDBODY);
    //body->ActivateResponse(false);
    //body->SetShape(BOX);

    //shooter->AddLogic(LogicFactory::CreateLogic(shooter, SLOW));
    //shooter->AddLogic(LogicFactory::CreateLogic(shooter, AFTERIMAGE));
    //shooter->AddLogic(LogicFactory::CreateLogic(shooter, FIST));
    //shooter->AddLogic(LogicFactory::CreateLogic(shooter, DAMAGE));
    //
    //shooter->SetTexture(m_GSM->GetGLManager()->GetTexture("Shield"));
    //m_OBM->AddObject(shooter);

    //shooter->GetLogic<Damage>(DAMAGE)->SetDamage(0);
    //shooter->GetLogic<Damage>(DAMAGE)->SetMaintain(false, 0.f);
}

/******************************************************************************/
/*!
\brief - Update Turret info
\param dt - delta time
*/
/******************************************************************************/
void Turret::Update(float dt)
{
    if (m_OBM->HasObject(player_id) && m_GSM->GetGameData()->immortal == false)
    {
        body = m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->GetBody();
        vec3 player_pos = player[0]->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
        body->SetDirectionVector(vec3(player_pos - m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->GetEmitterPos()));
        collidedTime += dt;
        m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->SetParticlePos(m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->GetEmitterPos());
        if ((Math::Distance_pt(player_pos, m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition()) < 200.f && active == false && collidedTime > 3.f)
			&& m_Owner->GetLogic<TurretTarget>(TURRETTARGET)->GetActiveAttackToggle() == false )
        {
            active = true;
        }
        else if (active == false)
        {
            body->SetSpeed(0.f);
            m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->SetParticleQuit(true);
            m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->SetEmitterPos(m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition());
        }
        else if (active == true)
        {
            m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->Restore();
            activeTime += dt;
			
            if (activeTime > m_Owner->GetLogic<BasicTrap>(TRAP)->GetRunningTime())
            {
                active = false;
                activeTime = 0.f;
            }

            body->SetSpeed(50.f);

            if (body->IsCollidedWith(player_id))
            {
				m_Owner->GetLogic<TurretTarget>(TURRETTARGET)->SetActiveToggle(true);
				vec3 tmp = m_GSM->GetGameData()->player_pos;
				m_Owner->GetLogic<TurretTarget>(TURRETTARGET)->SetPosition(vec3(tmp.x, tmp.y, tmp.z + 1.f));
                m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->SetParticleQuit(true);
                active = false;
                activeTime = 0.f;
                collidedTime = 0.f;
            }
        }
    }

}

/******************************************************************************/
/*!
\brief - Shutdown Turret info
*/
/******************************************************************************/
void Turret::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload Turret info
*/
/******************************************************************************/
void Turret::Unload(void)
{

}
