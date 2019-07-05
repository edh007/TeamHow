/******************************************************************************/
/*!
\file   Enemy.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/09/12(yy/mm/dd)

\description
Contains Enemy class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"
#include <map>
#include <vector>

enum EnemyType { NORMAL_ENEMY, BULLET_SHOOTER, WEB_SHOOTER, BOMBER, ANTI_TIMER, DEFENDER};
enum Condition { USUAL, RECOG, DETECT, PUNCHED, SUSPICIOUS, LOST, RETURN};
enum PatrolType { LINEAR, SHUTTLE }; 
typedef std::map<unsigned, vec3> CheckPoints;

class EnemyBuilder : public LogicBuilder
{

public:
	EnemyBuilder() {};
	virtual ~EnemyBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Audio;
class Particle;
class RigidBody;
class Enemy : public GameLogic
{
public:
	Enemy(Object* owner, LogicType key);
	virtual ~Enemy(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	bool GetActingToggle(void) const;
	void ActiveBehavior(bool active);
	bool GetAliveToggle(void) const;

	float GetDistanceformPlayer(void) const;

	float GetSpeed(void) const;
	void SetSpeed(float speed);

	void SetEnemyType(EnemyType type);
	EnemyType GetEnemyType(void) const;

	bool GetVisible(void) const;
	Object* GetFOV(void);

	void SetCondition(Condition condition);
	Condition GetCondition(void) const;

	void SetPatrolType(PatrolType type);
	PatrolType GetPatrolType(void) const;

	void RemoveCheckPoint(int index);
	void AddCheckPoint(vec3 position);
	const vec3& GetCheckPoint(int index);
	void ClearCheckPoints(void);

	void ActivePatrol(bool patrol);
	bool GetPatrolToggle(void) const;

protected:

	// Init info
	void GetPlayerInfo(void);
	void InitBodySize(void);
	void MakeFov(void);
	void CollectWalls(void);
	void InitCheckPoints(void);

	// Update enemy UIs
	void UpdateFOV(void);
	void UpdateMark(void);

	// Act function
	void Alive(float dt);
	void Dead(float dt);
	void Attack(float dt);
	void ShootBullet(void);
	void ShootWeb(void);
	void Chase(void);
	void Explose(void);

	// Patrol
	void PathFinding(void);
	void TrackPath(void);
	void Patrol();

	// Set enemy condition
	void EnemyCondition(float dt);
	
	//Recognize function
	void Usual(float dt);
	void Recognize(void);
	void Detect(void);
	void Suspicious(float dt);
	void Return(void);

	// Player(target) info
	Object *m_player;
	int player_id;
	int fov_id, mark_id;
	vec3 plr_pos, lost_pos;

	// Enemy info
	vec4 m_color;
	float originalDeg, rotateOffset, defenderToggle;
	bool m_visible, m_acting, m_alive, m_patrol, m_toggle;
	EnemyType m_enemyType;
	PatrolType m_patrolType;
	RigidBody* m_body;
	Object	*effect, *fov, *notice;
	float m_footstep;
	float m_rotate, m_detectDis, m_attacDis;
	vec3 fovScl, enm_pos;
	Condition m_condition;

	Audio* m_foot, *m_effect;

	bool m_fixed;

	// Explose info
	bool m_explose;

	// bullet info
	float m_speed;
	float dt_Stack;
	float m_shootTime;
	float m_lookAround;
	float m_disFromPlayer;

	unsigned tempIndex;
	bool tempToggle;
	bool m_activePF;

	// Shared info
	float tempDist;

	// Linear info
	float m_diff;
	vec3 new_force, m_destination;

	// Checkpoint storage
	bool increase;		// Shuttle toggle
	unsigned m_index;	// list index
	CheckPoints m_cpList, m_storeList;

	// Wall vector
	std::vector<RigidBody*> walls;
};

#endif // _ENEMY_H_

