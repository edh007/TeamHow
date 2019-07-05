/******************************************************************************/
/*!
\file   ParticleManager.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/01/06(yy/mm/dd)

\description
Contains ParticleManager logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _PARTICLEMANAGER_H_
#define _PARTICLEMANAGER_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"
#include "../../../Engine/GameSystem/Graphic/Particle/Particle.h"
#include "../Trap/BasicTrap.h"

class ParticleManagerBuilder : public LogicBuilder
{

public:
	ParticleManagerBuilder() {};
	virtual ~ParticleManagerBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class RigidBody;
class Transform;

class ParticleManager : public GameLogic
{
public:

	ParticleManager(Object* Owner, LogicType key);
	virtual ~ParticleManager(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

    // Lantern
    float GetRange();
    void SetAttackRangeON(float dt);
    void SetAttackRangeOFF();
    float GetWorkingTime();

    // Bomb
    void Restore(void);

    // AfterImage
    void SetParticlePos(vec3 pos);
    RigidBody* GetBody();
    vec3 GetEmitterPos();
    void SetEmitterPos(vec3 pos);
    void SetParticleQuit(bool check);
    void SetActive(bool check);
    
    void SetParticleType(ParticleType p_type);
    float GetSpeedInitValue();
private:
    Particle* m_particle;
    Object* m_particleOwner;
    ParticleType p_particleSave;
    float range;

    std::vector<Object*> enemy;
    int enemy_id;
    vec3 middle;
    float workingTime;
    vec3 sptPos;
    bool m_active;
};

#endif // _PARTICLEMANAGER_H_
