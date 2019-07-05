/******************************************************************************/
/*!
\file   Enemy.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/09/12(yy/mm/dd)

\description
Contains Enemy class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "../../../BaseData/BaseEnigne.h"
#include "Enemy.h"
#include "Damage.h"
#include "../Trap/Web.h"
#include "../Player/Slow.h"
#include "../Items/Bullet.h"
#include "../Player/Player.h"
#include "../Particle/ParticleManager.h"
#include <algorithm>
#include <functional>

/******************************************************************************/
/*!
\brief - Compare tow node's start value
\param lhs - 1st node
\param rhs - 2nd node
\return boolean
*/
/******************************************************************************/
bool byStart(Node* lhs, Node* rhs) {
	return lhs->fromStartf < rhs->fromStartf;
}

/******************************************************************************/
/*!
\brief - Compare tow node's end value
\param lhs - 1st node
\param rhs - 2nd node
\return boolean
*/
/******************************************************************************/
bool byEnd(Node* lhs, Node* rhs) {
	return lhs->toEndf < rhs->toEndf;
}

/******************************************************************************/
/*!
\brief - EnemyBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* EnemyBuilder::BuildLogic(Object* Owner, LogicType key) const
{
	return new Enemy(Owner, key);
}

/******************************************************************************/
/*!
\brief - Enemy constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Enemy::Enemy(Object* owner, LogicType key)
	: GameLogic(owner, key),
	player_id(0), m_player(nullptr), plr_pos(vec3()), m_index(0), increase(true), m_detectDis(150.f), rotateOffset(15.f), notice(nullptr),
	m_speed(150.f), m_rotate(0.f), m_body(0),m_explose(false), m_condition(USUAL), m_color(vec4(1, 1, 1, 1)), defenderToggle(true),
	fov(nullptr), m_enemyType(NORMAL_ENEMY), m_shootTime(1.f), dt_Stack(1.f), enm_pos(vec3()), m_visible(false), lost_pos(vec3()),
	m_diff(15.f), m_patrol(true), m_activePF(false), tempToggle(false), m_patrolType(LINEAR), new_force(vec3()), tempDist(0.f),
	fovScl(vec3()), effect(0), m_footstep(5.f), m_acting(false), m_disFromPlayer(0.f), m_alive(true), m_lookAround(5.f), m_fixed(false)
{}

/******************************************************************************/
/*!
\brief - Load Enemy info
\param data - json parser
*/
/******************************************************************************/
void Enemy::Load(const Json::Value& data)
{
	// Set speed
	if (data.isMember("Speed") &&
		data["Speed"].isNumeric())
		m_speed = data["Speed"].asFloat();

	// Set fixed
	if (data.isMember("Fixed") &&
		data["Fixed"].isBool())
		m_fixed = data["Fixed"].asBool();

	// Set distance
	if (data.isMember("EnemyType") &&
		data["EnemyType"].isString())
	{
		if (!strcmp(data["EnemyType"].asCString(), "NORMAL")) {
			m_enemyType = NORMAL_ENEMY;
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Enemy_Normal"));
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetFrame(10);
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetFrameSpd(25);
		}
		
		else if (!strcmp(data["EnemyType"].asCString(), "WEB")) {
			m_enemyType = WEB_SHOOTER;
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Enemy_WebShooter"));
		}
		
		else if (!strcmp(data["EnemyType"].asCString(), "BULLET")) {
			m_enemyType = BULLET_SHOOTER;
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Enemy_BulletShooter"));
		}
		
		else if (!strcmp(data["EnemyType"].asCString(), "ANTI")) {
			m_enemyType = ANTI_TIMER;
			m_speed = 10.f;
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Enemy_Anti"));
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetFrame(10);
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetFrameSpd(25);
		}

		else if (!strcmp(data["EnemyType"].asCString(), "DEFENDER")) {
			m_enemyType = DEFENDER;
			m_Owner->GetLogic<Damage>(DAMAGE)->SetLife(1);
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Enemy_Defender"));
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetFrame(10);
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetFrameSpd(25);
		}

		else if (!strcmp(data["EnemyType"].asCString(), "BOMBER"))
		{
			m_enemyType = BOMBER;
            m_Owner->AddLogic(LogicFactory::CreateLogic(m_Owner, PARTICLEMANAGER));
            m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->SetParticleType(P_BOMB);
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Enemy_Bomber"));
		}
	}

	// Patrol type
	if (data.isMember("PatrolType") &&
		data["PatrolType"].isString())
	{
		if (!strcmp("LINEAR", data["PatrolType"].asCString()))
			m_patrolType = LINEAR;
		else if (!strcmp("SHUTTLE", data["PatrolType"].asCString()))
			m_patrolType = SHUTTLE;

		// Set these info only for this case
		if (data.isMember("Point") &&
			data["Point"].isArray() &&
			data["Point"][0].isArray() &&
			data["Point"][0][0].isNumeric())
		{
			m_cpList.clear();
			for (unsigned i = 0; i < data["Point"].size(); ++i)
				AddCheckPoint(vec3(
					data["Point"][i][0].asFloat(),
					data["Point"][i][1].asFloat(),
					data["Point"][i][2].asFloat()));
		}

		// Set these info only for this case
		if (data.isMember("Diff") &&
			data["Diff"].isNumeric())
			m_diff = data["Diff"].asFloat();
	}
}

/******************************************************************************/
/*!
\brief - Initialize Enemy info
*/
/******************************************************************************/
void Enemy::Init(void)
{
	GetPlayerInfo();
	InitBodySize();
	MakeFov();
	InitCheckPoints();
	CollectWalls();

	notice = new Object(AT_HUD, m_OBM);
	notice->AddComponent(ComponentFactory::CreateComponent(notice, CT_SPRITE));
	notice->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4());
	notice->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(25,25));
	notice->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("QuestionMark"));
	m_OBM->AddObject(notice);
	mark_id = notice->GetID();

	std::string soundNum("enemyFoot");
	soundNum += std::to_string(m_OwnerID);

	m_OBM->GetGameSound()->AddAudio(soundNum.c_str(), "footstep");
	m_foot = m_OBM->GetGameSound()->GetAudio(soundNum.c_str());
	m_foot->SetVolume(m_GSM->GetGameData()->volume);

	soundNum.assign("enemyEffect");
	soundNum += std::to_string(m_OwnerID);

	if (m_enemyType == BULLET_SHOOTER)
	{
		m_OBM->GetGameSound()->AddAudio(soundNum.c_str(), "gunShot");
		m_effect = m_OBM->GetGameSound()->GetAudio(soundNum.c_str());
	}
	else if (m_enemyType == WEB_SHOOTER)
	{
		m_OBM->GetGameSound()->AddAudio(soundNum.c_str(), "whip");
		m_effect = m_OBM->GetGameSound()->GetAudio(soundNum.c_str());
	}

	else if (m_enemyType == BOMBER) {
		m_OBM->GetGameSound()->AddAudio("bomb", "explosion");
		m_effect = m_OBM->GetAudio("bomb");
	}
}

/******************************************************************************/
/*!
\brief - Update Enemy info
\param dt - delta time
*/
/******************************************************************************/
void Enemy::Update(float dt)
{
	// Update the behaivor
	Alive(dt);
	UpdateFOV();
	UpdateMark();
	Dead(dt);

	m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(m_color);
}

/******************************************************************************/
/*!
\brief - Shutdown Enemy info
*/
/******************************************************************************/
void Enemy::Shutdown(void)
{
	m_cpList.clear();
	if (effect)	{
		delete effect;
		effect = 0;
	}
}

/******************************************************************************/
/*!
\brief - Unload Enemy info
*/
/******************************************************************************/
void Enemy::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Preset player's information
*/
/******************************************************************************/
void Enemy::GetPlayerInfo(void)
{
	m_player = m_GSM->GetGameData()->player;
	player_id = m_GSM->GetGameData()->player_id;
}

/******************************************************************************/
/*!
\brief - Preset enemy's rigid body size
*/
/******************************************************************************/
void Enemy::InitBodySize(void)
{
	// Set the body info
	m_body = m_Owner->GetComponent<RigidBody>(CT_RIGIDBODY);

	m_body->SetShape(BALL);
	m_body->SetScaleToggle(false);
	m_body->SetScale(m_body->GetScale() *.65f);
	
	if (m_enemyType == DEFENDER)
		m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetScale(
			m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetScale() * 1.5f);

	// Set the preset rotation
	originalDeg = m_rotate =
		m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetRotation();
	float temp_degree = Math::DegToRad(m_rotate);
	vec3 temp = vec3(cosf(temp_degree), sinf(temp_degree)).Normalize();
	m_Owner->GetComponent<RigidBody>(CT_RIGIDBODY)->SetDirectionVector(
		temp);
}

/******************************************************************************/
/*!
\brief - Preset enemy's field of view
*/
/******************************************************************************/
void Enemy::MakeFov(void)
{
	if (!fov)	{
		fovScl = vec3(200, 200);
		fov = new Object(AT_FOV, m_OBM);
		fov->AddComponent(ComponentFactory::CreateComponent(fov, CT_SPRITE));
		fov->GetComponent<Transform>(CT_TRANSFORM)->SetScale(fovScl);
		fov->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1.f, 1.f, 1.f, .25f));
		fov->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Fov"));
		fov_id = fov->GetID();
		m_OBM->AddObject(fov);
	}
}

/******************************************************************************/
/*!
\brief - Preset wall objects
*/
/******************************************************************************/
void Enemy::CollectWalls(void)
{
	// Get walls' rigidbody
	std::vector<Object*> wall_objs;
	m_OBM->GetObjects(AT_WALL, wall_objs);
	for (auto it : wall_objs)
		walls.push_back(it->GetComponent<RigidBody>(CT_RIGIDBODY));
}

/******************************************************************************/
/*!
\brief - Preset check points
*/
/******************************************************************************/
void Enemy::InitCheckPoints(void)
{
	if (m_cpList.size()) {

		// Store nodes into the cpList in advance
		for (size_t i = 0; i < m_cpList.size(); ++i) {
			int index = int(i);
			m_storeList.insert(CheckPoints::value_type(
				index, m_cpList[index]));
		}

		// Set 1st destination
		m_destination = m_cpList[0];
	}

	else {
		m_patrol = false;
		m_destination = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
	}
}

/******************************************************************************/
/*!
\brief - Action when player's alive
\param dt
*/
/******************************************************************************/
void Enemy::Alive(float dt)
{
	float newDt = m_Owner->GetdtOffset() * dt;

	if (m_alive) {

		// Update the primitives
		enm_pos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
		plr_pos = m_GSM->GetGameData()->player_pos;
		m_disFromPlayer = Math::Distance_pt(plr_pos, enm_pos);
		m_foot->SetPosition(enm_pos);

		// Check either if the enemy recognize 
		// player or not
		if (m_OBM->HasObject(player_id)) {
			
			if (m_GSM->GetGameData()->immortal
				&& m_body->IsCollidedWith(player_id)) {
				m_condition = PUNCHED;
				
				//if (m_enemyType == DEFENDER) {
				m_body->SetSpeed(0.f);
				m_Owner->GetLogic<Damage>(DAMAGE)->SetLife(-1);
				//}
			}

			else
				EnemyCondition(newDt);
		}

		else {
			m_body->ClearVelocity();
			m_foot->Stop();
		}
	}
}

/******************************************************************************/
/*!
\brief - Action when player's dead
\param dt
*/
/******************************************************************************/
void Enemy::Dead(float dt)
{
	// Death condition
	if (m_condition == PUNCHED)	{
		
		// Double check if there is no fov
		// Remove filed of view
		if (m_enemyType == DEFENDER) {

			if (m_Owner->GetLogic<Damage>(DAMAGE)->GetLife() < 0) {
				if (m_OBM->HasObject(fov_id))
					m_OBM->RemoveObject(fov_id);

				// Remove markF
				if (m_OBM->HasObject(mark_id))
					m_OBM->RemoveObject(mark_id);
			}

			else if (m_Owner->GetLogic<Damage>(DAMAGE)->GetLife() == 1
				&& defenderToggle) {
				m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetTexture(
					m_OBM->GetTexture("Enemy_Normal"));
				m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetScale(
					m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetScale() * .75F);
				defenderToggle = false;
			}
		}

		else {
			if (m_OBM->HasObject(fov_id))
				m_OBM->RemoveObject(fov_id);

			// Remove markF
			if (m_OBM->HasObject(mark_id))
				m_OBM->RemoveObject(mark_id);
		}

		if (m_enemyType == BOMBER) 
			Explose();

		else {
			// Refresh body info
			if (m_body->GetSpeed() <= 0.f)
			{
				// If the type is defender...
				if (m_enemyType == DEFENDER
					&& m_Owner->HasLogic(DAMAGE)) {

					// And there are enough lives to alive,
					// maintain
					if (m_Owner->GetLogic<Damage>(DAMAGE)->GetLife() > 0.f) {
						m_condition = DETECT;
						m_Owner->GetLogic<Damage>(DAMAGE)->SetLife(
							m_Owner->GetLogic<Damage>(DAMAGE)->GetLife() - 1);
						m_alive = true;
						m_body->ActivateResponse(false);
					}

					// If not, remove
					else {
						m_body->ActivateCollider(false);
						m_body->ActivateResponse(false);
						m_alive = false;
					}
				}

				// If not, remove
				else {
					m_body->ActivateCollider(false);
					m_body->ActivateResponse(false);
					m_alive = false;
				}

				// Make enemy to be vanished
				if (!m_alive) {
					m_color.w -= dt;
					if (m_color.w < 0.f)
						m_color.w = 0.f;
				}
			}
		}

		if ((m_enemyType == NORMAL_ENEMY || m_enemyType == DEFENDER	|| m_enemyType == ANTI_TIMER)
			&& m_Owner->GetComponent<Sprite>(CT_SPRITE)->GetAnimation()) {
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetAnimation(false);
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->currentFrame = 0;
		}

		// Stop playing footstep sound 
		m_foot->Stop();

		if (!m_color.w)
			RemoveOwner(true);
	}
}

/******************************************************************************/
/*!
\brief - Update enemy's fov 
*/
/******************************************************************************/
void Enemy::UpdateFOV(void)
{
	// Set fov's info
	if (m_OBM->HasObject(fov_id))	{
		vec3 fovPos = Math::Rotation(enm_pos + vec3(.4f * fovScl.x, 0.f), m_rotate, enm_pos);
		fovPos.z = 2.f;

		// Check if the enemy is dead or not
		if (m_alive && m_GSM->GetGameData()->searchToggle)
		{
			fovPos.z = 10.f;
			float footstep = m_GSM->GetGameData()->footstack;
			// Check level of foot steps' noise
			// Set sign's color(Alarm); from white to yellow
			if (m_condition == RECOG && m_cpList.size())
				fov->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 1, 0, .5f));

			// Set red that shows player is detected; red
			else if (m_condition == DETECT) {
				footstep = 6.f;
				fov->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 0, 0, .5f));
			}

			else 
				fov->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 1, 1, .5f));
		}

		else
			fov->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4());

		fov->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(fovPos);
		fov->GetComponent<Transform>(CT_TRANSFORM)->SetRotation(m_rotate);
	}
}

/******************************************************************************/
/*!
\brief - Update enemy's notice mark
*/
/******************************************************************************/
void Enemy::UpdateMark(void)
{
	if (m_OBM->HasObject(mark_id)) {

		if (m_GSM->GetGameData()->searchToggle)
		{
			if (m_GSM->GetGameData()->footstack >= 3.f) {
				notice->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("QuestionMark"));

				if (m_GSM->GetGameData()->footstack >= 5.f)
					notice->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("ExclamationMark"));

				notice->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 1, 1, 1));
				vec3 noticePos = enm_pos;
				noticePos.y += 10.f;
				noticePos.z = 11.f;
				notice->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(noticePos);
			}

			else
				notice->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4());
		}
		
		else
			notice->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4());
	}
}

/******************************************************************************/
/*!
\brief - Enemy's action by enemy type
\param dt
*/
/******************************************************************************/
void Enemy::Attack(float dt)
{
	// This only activates when enemy detects 
	// player and patrol toggle is false
	switch (m_enemyType) {

		// No difference between these types
		case ANTI_TIMER:
		case DEFENDER:
		case NORMAL_ENEMY:
			if (!m_fixed) {
				Chase();
				m_acting = true;
			}
			break;

		case BULLET_SHOOTER:
				m_shootTime = .3f;
				m_acting = true;
				dt_Stack += dt;
				m_body->ClearVelocity();
				m_foot->Stop();

				// Shoot whenever he ready
				if (dt_Stack > m_shootTime)
				{
					ShootBullet();
					dt_Stack = 0;
				}
			
			break;

		case WEB_SHOOTER:
				m_acting = true;
				dt_Stack += dt;
				m_body->ClearVelocity();
				m_foot->Stop();

				// Shoot whenever he ready
				if (dt_Stack > m_shootTime)
				{
					ShootWeb();
					dt_Stack = 0;
				}
			
			break;

		case BOMBER:
			Explose();
			break;

		default:
			break;
	}
}

/******************************************************************************/
/*!
\brief - Shoot Bullet
*/
/******************************************************************************/
void Enemy::ShootBullet(void)
{
	// Make new bullet
	float bulletDeg = m_rotate + 90.f;

	Object* bullet = new Object(AT_BULLET, m_OBM);
	bullet->AddComponent(ComponentFactory::CreateComponent(bullet, CT_RIGIDBODY));
	bullet->AddComponent(ComponentFactory::CreateComponent(bullet, CT_SPRITE));

	bullet->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec2(5, 15));
	bullet->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(enm_pos);
	bullet->GetComponent<Transform>(CT_TRANSFORM)->SetRotation(bulletDeg);

	bullet->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_GSM->GetGLManager()->GetTexture("Bullet"));
	bullet->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1, 1, 0, 1));

	RigidBody* body = bullet->GetComponent<RigidBody>(CT_RIGIDBODY);
	body->SetSpeed(m_speed);
	body->SetShape(BALL);
	body->ActivateResponse(false);
	body->SetDirectionVector((plr_pos - enm_pos).Normalize());

	bullet->AddLogic(LogicFactory::CreateLogic(bullet, DAMAGE));
	bullet->AddLogic(LogicFactory::CreateLogic(bullet, BULLET));
	bullet->AddLogic(LogicFactory::CreateLogic(bullet, SLOW));
	bullet->GetLogic<Bullet>(BULLET)->SetId(m_Owner->GetID());
	m_OBM->AddObject(bullet);

	// Bullet effect
	m_effect->Play();
	m_effect->SetPosition(m_GSM->GetGameData()->cameraPos);
}

/******************************************************************************/
/*!
\brief - Shoot Web
*/
/******************************************************************************/
void Enemy::ShootWeb(void)
{
	Object* new_web = new Object(AT_WEB, m_OBM);
	new_web->AddComponent(ComponentFactory::CreateComponent(new_web, CT_RIGIDBODY));
	new_web->AddComponent(ComponentFactory::CreateComponent(new_web, CT_SPRITE));

	new_web->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3());
	new_web->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(enm_pos);
	new_web->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_GSM->GetGLManager()->GetTexture("Web"));

	vec3 diff = (plr_pos - enm_pos);
	float len = diff.Length();

	RigidBody* body = new_web->GetComponent<RigidBody>(CT_RIGIDBODY);
	body->SetSpeed(len * .5f);
	body->SetShape(BALL);
	body->ActivateResponse(false);
	body->SetDirectionVector(diff.Normalize());

	new_web->AddLogic(LogicFactory::CreateLogic(new_web, DAMAGE));
	new_web->AddLogic(LogicFactory::CreateLogic(new_web, WEB));
	new_web->AddLogic(LogicFactory::CreateLogic(new_web, SLOW));

	new_web->GetLogic<Web>(WEB)->SetRoot(true);
	new_web->GetLogic<Web>(WEB)->SetDenominator(len);
	new_web->GetLogic<Damage>(DAMAGE)->SetMaintain(true);
	new_web->GetLogic<Damage>(DAMAGE)->SetSlow(0.25f);
	new_web->GetLogic<Damage>(DAMAGE)->SetDamage(0);

	m_OBM->AddObject(new_web);
	m_effect->Play();
	m_effect->SetPosition(m_GSM->GetGameData()->cameraPos);
}

/******************************************************************************/
/*!
\brief - Explose
*/
/******************************************************************************/
void Enemy::Explose(void)
{
	if (m_condition == PUNCHED
		|| (!m_explose 
		&& m_condition == DETECT))
	{
		m_effect->SetPosition(m_GSM->GetGameData()->cameraPos);
		m_effect->Play();
		
		m_acting = true;
		m_Owner->GetLogic<ParticleManager>(PARTICLEMANAGER)->SetActive(true);
		
		// Init collision box's scale and collision
		m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4());
		m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(300, 300, 0));
		m_body->SetScale(vec3(300, 300, 0));
		
		// Remove logic patrol logic
		// cuz this is not in need anymore
		m_patrol = false;

		m_body->ClearVelocity();
		m_foot->Stop();
		m_body->SetShape(BALL);		// Change the collider shape
		m_explose = true;			// Explosion to work

		m_body->ActivateResponse(false);
		m_alive = false;
		m_color.w = 0.f;

		// Set die anyway
		m_condition = PUNCHED;

		// If there is a wall between player and bomber,
		// no collision check
		m_body->ActivateCollider(m_visible);
	}

	// Follow the player
	else
		m_acting = false;
}

/******************************************************************************/
/*!
\brief - Enemy condition tree
\param dt
*/
/******************************************************************************/
void Enemy::EnemyCondition(float dt)
{
	switch (m_condition) {
		case USUAL:{
			//std::cout << "USUAL" << std::endl;

			//Could either recognize or detect
			Recognize();
			Detect();
			
			// This is usual patrol
			// if enemy maintained his condition
			if (m_condition == USUAL)
				Usual(dt);
			break; 
		}

		case RECOG: {
			//std::cout << "RECOG" << std::endl;
			
			PathFinding();	// Do patrol
			Detect();		// Check detect

			// *Detected process
			// If enemy detect the player,
			// stop patroling
			if (m_condition == DETECT)
				// The case when enemy was not on path-fiding...
				m_patrol = false;
			break;
		}
		case DETECT:{
			//std::cout << "DETECT" << std::endl;

			// Maintain the direction to the player
			m_rotate = Math::Degree_pt(enm_pos, plr_pos);
			
			// If enemy lost player
			// while thery are detected him...
			if (m_disFromPlayer > m_detectDis) {
				m_condition = SUSPICIOUS;
				m_acting = false;
			}

			else 
				m_acting = true;

			// If enemy detected player,
			// attack the player
			if (m_acting)
				Attack(dt);

			break; 
		}
		//case PUNCHED: {
		//	std::cout << "PUNCHED" << std::endl;
		//	break; 
		//}
		case SUSPICIOUS: {
			//std::cout << "SUSPICIOUS" << std::endl;

			// Maintain the direction to the player
			m_rotate = Math::Degree_pt(enm_pos, plr_pos);
			Suspicious(dt);
			Detect();

			// *Detected process
			// If enemy detect the player,
			// stop patroling
			if (m_condition == DETECT)
				m_acting = true;

			break;
		}
		//case LOST: {
		//	std::cout << "LOST" << std::endl;
		//	break;
		//}
		case RETURN: {
			//std::cout << "RETURN" << std::endl;
			Return();
			Detect();
			break;
		}
	}

	m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetRotation(m_rotate);
}

/******************************************************************************/
/*!
\brief - Enemy's usual behavior
\param dt
*/
/******************************************************************************/
void Enemy::Usual(float dt)
{
	// Usual patrol...

	// If this has multiple nodes
	if (m_cpList.size() > 1 && m_patrol)
		Patrol();

	// This is the case has only 1 check point
	else {
		m_rotate += rotateOffset * dt;

		// Change the direction
		if (m_rotate > originalDeg + 45.f) {
			rotateOffset = -15.f;
			m_rotate = originalDeg + 45.f;
		}

		else if (m_rotate < originalDeg - 45.f) {
			rotateOffset = 15.f;
			m_rotate = originalDeg - 45.f;
		}

		m_body->ClearVelocity();
		m_foot->Stop();
	}
}

/******************************************************************************/
/*!
\brief - Enemy's recognizing
\param dt
*/
/******************************************************************************/
void Enemy::Recognize(void)
{
	// If the player's position if close enough
	// set condition recog
	if (m_disFromPlayer < m_GSM->GetGameData()->realViewSight
		&& m_footstep <= m_GSM->GetGameData()->footstack) {
		m_condition = RECOG;
		m_patrol = true;
	}
}

/******************************************************************************/
/*!
\brief - Enemy's detecting behavior
\param dt
*/
/******************************************************************************/
void Enemy::Detect(void)
{
	// Check fov and distance from player
	float enm_degree = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetRotation();

	float right = enm_degree - 45.f, left = enm_degree + 45.f;
	float degree = Math::Degree_pt(enm_pos, plr_pos);

	// Polish degree
	if (right >= 360.f)
		right -= 360.f;
	else if (right < 0.f)
		right += 360.f;
	if (left >= 360.f)
		left -= 360.f;
	else if (left < 0.f)
		left += 360.f;

	// If the distance is close enough and 
	// player is just inside the fov, 
	// do detect
	if (m_disFromPlayer < m_detectDis) {

		m_visible = true;

		// Compare barriers' edges and 
		// vector from player's position and enemy's position
		for (auto it : walls)
		{
			if (!m_OBM->GetGameWorld()->CollisionIntersect(it, plr_pos, enm_pos))
				m_visible = false;
		}

		if (m_visible)
		{
			// If player is in visible area
			// then will be detected
			if ((left <= 45.f || right >= 315.f) &&
				(degree > right || degree < left)) {
				m_condition = DETECT;
			}

			else if ((right > 0.f && left < 360.f) &&
				(degree <= left && degree >= right)) {
				m_condition = DETECT;
			}
		}
	}
}

/******************************************************************************/
/*!
\brief - Enemy's suspicious behavior
\param dt
*/
/******************************************************************************/
void Enemy::Suspicious(float dt)
{
	// It just stop
	// Stay where he is and wait for a seconds(5s)
	m_lookAround -= dt;
	m_body->ClearVelocity();
	m_patrol = false;
	m_acting = false;
	m_foot->Stop();
	m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetAnimation(false);
	m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetSpecificFrame(0);

	// Active patrol again
	if (m_lookAround <= 0.f) {
		if (m_fixed)
			m_condition = USUAL;
		
		else
			m_condition = RETURN;
		
		m_lookAround = 5.f;
		m_patrol = true;
		increase = false;
		PathFinding();
	}
}

/******************************************************************************/
/*!
\brief - Enemy's returning
*/
/******************************************************************************/
void Enemy::Return(void)
{
	// Get the distance from enemy to player
	tempDist = Math::Distance_pt(m_destination, enm_pos);

	// If the next step is original place 
	// and enemy get close enough to destination
	if (tempDist < m_diff
		&& m_index == 0) {

		m_condition = USUAL;
		m_activePF = false;		// Lock toggle
		increase = tempToggle;	// Load toggle
		m_index = tempIndex;	// Load index
		m_cpList.clear();

		if (m_storeList.size()) {
			for (size_t i = 0; i < m_storeList.size(); ++i)
			{
				int index = int(i);
				m_cpList.insert(CheckPoints::value_type(
					index, m_storeList[index]));
			}
			m_storeList.clear();
			m_patrol = true;
		}
	}

	// Unless, keep patroling
	else 
		Patrol();
}

/******************************************************************************/
/*!
\brief - Path Finding function
*/
/******************************************************************************/
void Enemy::PathFinding(void)
{
	// Patrol depends on a toggle
	// and cp list has smoe nodes
	if (m_patrol /*&& !m_acting */ && !m_fixed)
	{
		// Check if there is a player
		if (m_OBM->HasObject(player_id))
		{
			// Partorl the defined route
			TrackPath();

			// Or the enemy got to know that there is a player,
			// check path-finding and returning toggle are valid
			if (!m_activePF
				&& m_OBM->GetGameWorld()->GetNodeSize()) {

				m_activePF = true;		// Set pf toggles
				tempToggle = increase;	// Save current increase toggle
				tempIndex = m_index;	// Save current index
				m_index = 0;			// Reset index

				// Clear all nodes' info
				m_OBM->GetGameWorld()->RefreshNodes();

				std::vector<Node*> start_candidates;
				std::vector<Node*> end_candidates;

				vec3 destination;
				if (m_condition == RECOG)
					destination = plr_pos;

				else if (m_condition == SUSPICIOUS)
					destination = m_storeList.begin()->second;

				for (auto node : m_OBM->GetGameWorld()->GetNodeList()) {
					bool add[2] = { true, true };

					// Check if there is an obstacles between enemy and node
					// and if the node is can be reached directly
					for (auto it : walls) {

						// Check enemy's pos and node
						if (add[0] &&
							!m_OBM->GetGameWorld()->CollisionIntersect(it, enm_pos, node->GetPosition()))
							add[0] = false;

						// Check player's pos and node
						if (add[1] &&
							!m_OBM->GetGameWorld()->CollisionIntersect(it, destination, node->GetPosition()))
							add[1] = false;

						if (!add[0] && !add[1])
							break;
					}
					// If there is no wall between 2 objects,
					// just add as an candidate
					if (add[0]) {
						// Calculate dist
						node->fromStartf = Math::Distance_pt(enm_pos, node->GetPosition());
						start_candidates.push_back(node);
					}

					if (add[1]) {
						// Calculate dist
						node->toEndf = Math::Distance_pt(destination, node->GetPosition());
						end_candidates.push_back(node);
					}
				}

				// Check if there are node to go
				if (start_candidates.size() && end_candidates.size()) {

					// Sort the list
					std::sort(start_candidates.begin(), start_candidates.end(), byStart);
					std::sort(end_candidates.begin(), end_candidates.end(), byEnd);

					// Now get the route
					m_OBM->GetGameWorld()->GetRoute(
						*start_candidates.begin(),
						*end_candidates.begin());

					// Follow along new cpList
					// Set path to track
					m_cpList.clear();
					m_cpList.insert(CheckPoints::value_type(0, enm_pos));

					for (size_t i = 0; i < m_OBM->GetGameWorld()->GetPFList().size(); ++i) {
						m_cpList.insert(
							CheckPoints::value_type(int(i + 1),
								m_OBM->GetGameWorld()->GetPFList().at(i)->GetPosition()));
					}

					// Set starting point
					if (m_cpList.size())
						m_destination = m_cpList.begin()->second;

					// If there is not, move to suspicious
					else {
						m_condition = SUSPICIOUS;
						m_patrol = false;
					}
				}

				// If there is not, move to suspicious
				else {
					m_condition = SUSPICIOUS;
					m_patrol = false;
				}
				//}

				//// Patrol one more node
				//else if (m_condition == LOST) {

				//	// Set the pre toggles and abstract destination
				//	bool skip = true;
				//	vec3 tempDestination = m_OBM->GetGameWorld()->
				//		GetClosestNode(plr_pos)->GetPosition();

				//	// Set the destination
				//	for (auto it : walls) {
				//		if (m_OBM->GetGameWorld()->CollisionIntersect(it, enm_pos, plr_pos)) {
				//			m_destination = tempDestination;
				//			skip = false;
				//			break;
				//		}
				//	}

				//	if (!skip)
				//		m_condition = SUSPICIOUS;
				//}
			}
		}

		else
		{
			// No player,
			// stop patroling and do not move
			m_patrol = false;
			m_body->ClearVelocity();
			m_foot->Stop();
		}
	}
}

/******************************************************************************/
/*!
\brief - Patrol status
*/
/******************************************************************************/
void Enemy::Patrol(void)
{
	// Get the distance from enemy to player
	tempDist = Math::Distance_pt(m_destination, enm_pos);

	// If owner's position is not close enough to the destination,
	// keep track on it
	if (tempDist > m_diff)
		Chase();

	// Unless, increase the index
	else {
		// Drop by each check point
		if (increase) {
			// Next index
			if (m_index < m_cpList.size() - 1)
				++m_index;

			else {
				// Start again
				if (m_patrolType == LINEAR)
					m_index = 0;

				// SHUTTLE case
				else {
					--m_index;			// Previous place
					increase = false;	// No more index increasing
				}
			}
		}

		// This is shuttle case
		// when sprite gets track back
		else {
			// Next index
			if (m_index > 0)
				--m_index;

			else {
				++m_index;			// Next place
				increase = true;	// No more index decreasing
			}
		}

		// Loop for every check point track
		m_destination = m_cpList[m_index];
	}
}

/******************************************************************************/
/*!
\brief - Track path by nodes
*/
/******************************************************************************/
void Enemy::TrackPath(void)
{
	// If this has multiple nodes
	if (m_cpList.size() > 1) {

		// Get the distance from enemy to player
		tempDist = Math::Distance_pt(m_destination, enm_pos);

		// During the path fiding session,
		// enemy lost where player is,
		if (m_activePF) {
			// *Returning process
			// If enemy finished searching the player,
			// go back to where he was
			if (m_index == (m_cpList.size() - 1)
				&& tempDist < m_diff) 
				m_condition = SUSPICIOUS;

				//// *Lost process
				//// This is process when enemy
				//// lost the player...
				//else if (m_condition == LOST) {
				//	m_condition = SUSPICIOUS;
				//	m_patrol = true;
				//	m_acting = false;
				//}
		}

		Patrol();
	}
}

/******************************************************************************/
/*!
\brief - Chasing action
*/
/******************************************************************************/
void Enemy::Chase(void)
{
	// If enemy detected the player,
	// enemy will chase the player
	if (m_condition == DETECT) {
		new_force = plr_pos - enm_pos;
	
		if (!m_Owner->GetComponent<Sprite>(CT_SPRITE)->GetCurrentFrame()
			&& m_GSM->GetGameData()->player_Active)
			m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetAnimation(true);
	}

	// Unless, just patrol as usual
	else 
		new_force = m_destination - enm_pos;

	// Set direction to the destination
	float hyp = sqrt(new_force.x*new_force.x + new_force.y*new_force.y);
	new_force = new_force / hyp;
	m_body->SetDirectionVector(
		m_body->GetDirectionVector() + new_force);

	// Set speed
	m_body->SetSpeed(m_speed);

	// Set degree
	m_rotate = m_body->GetDirectionAngle();

	// Play foot sound
	if (!m_foot->IsPlaying())
		m_foot->Play();
}

/******************************************************************************/
/*!
\brief - Get Acting Toggle
\return m_acting
*/
/******************************************************************************/
bool Enemy::GetActingToggle(void) const
{
	return m_acting;
}

/******************************************************************************/
/*!
\brief - Active Behavior
\param active
*/
/******************************************************************************/
void Enemy::ActiveBehavior(bool active)
{
	m_alive = active;
}

/******************************************************************************/
/*!
\brief - Get Alive Toggle
\return m_alive
*/
/******************************************************************************/
bool Enemy::GetAliveToggle(void) const
{
	return m_alive;
}

/******************************************************************************/
/*!
\brief - Get fov from enemy
\return fov
*/
/******************************************************************************/
Object* Enemy::GetFOV(void)
{
	return fov;
}

/******************************************************************************/
/*!
\brief - Set condition
\param condition
*/
/******************************************************************************/
void Enemy::SetCondition(Condition condition)
{
	m_condition = condition;
}

/******************************************************************************/
/*!
\brief - Get enemy's condition
\return m_condition
*/
/******************************************************************************/
Condition Enemy::GetCondition(void) const
{
	return m_condition;
}

/******************************************************************************/
/*!
\brief - Set Patrol Type
\param type
*/
/******************************************************************************/
void Enemy::SetPatrolType(PatrolType type)
{
	m_patrolType = type;
}

/******************************************************************************/
/*!
\brief - Get enemy's patrol type
\return m_patrolType
*/
/******************************************************************************/
PatrolType Enemy::GetPatrolType(void) const
{
	return m_patrolType;
}

/******************************************************************************/
/*!
\brief - Remove Check Point
\param index
*/
/******************************************************************************/
void Enemy::RemoveCheckPoint(int index)
{
	m_cpList.erase(index);
}

/******************************************************************************/
/*!
\brief - Add Check Point
\param position
*/
/******************************************************************************/
void Enemy::AddCheckPoint(vec3 position)
{
	if (!m_cpList.size())	{
		// Init sprite's first position
		m_cpList.insert(
			CheckPoints::value_type(0, position));
	}

	else {
		m_cpList.insert(
			CheckPoints::value_type(m_cpList.size(), position));

		// If there are two check point,
		// second one is the 1st destination
		if (m_cpList.size() == 2)
			m_destination = m_cpList[1];
	}

	// Refresh the destination
	m_index = 0;
}

/******************************************************************************/
/*!
\brief - Get enemy's check point
\param index
\return check point
*/
/******************************************************************************/
const vec3 & Enemy::GetCheckPoint(int index)
{
	return m_cpList.find(index)->second;
}

/******************************************************************************/
/*!
\brief - Clear Check Points
*/
/******************************************************************************/
void Enemy::ClearCheckPoints(void)
{
	m_cpList.clear();
}

/******************************************************************************/
/*!
\brief - Active Patrol
\param patrol
*/
/******************************************************************************/
void Enemy::ActivePatrol(bool patrol)
{
	m_patrol = patrol;
}

/******************************************************************************/
/*!
\brief - Get Patrol Toggle
\return m_patrol
*/
/******************************************************************************/
bool Enemy::GetPatrolToggle(void) const
{
	return m_patrol;
}

/******************************************************************************/
/*!
\brief - Get Distance form Player
\return m_disFromPlayer
*/
/******************************************************************************/
float Enemy::GetDistanceformPlayer(void) const
{
	return m_disFromPlayer;
}

/******************************************************************************/
/*!
\brief - Get Speed
\return m_speed
*/
/******************************************************************************/
float Enemy::GetSpeed(void) const
{
	return m_speed;
}

/******************************************************************************/
/*!
\brief - Set Speed
\param speed
*/
/******************************************************************************/
void Enemy::SetSpeed(float speed)
{
	m_speed = speed;
}

/******************************************************************************/
/*!
\brief - Set enemy type
\param type
*/
/******************************************************************************/
void Enemy::SetEnemyType(EnemyType type)
{
	m_enemyType = type;
}

/******************************************************************************/
/*!
\brief - Get EnemyType
\return m_enemyType
*/
/******************************************************************************/
EnemyType Enemy::GetEnemyType(void) const
{
	return m_enemyType;
}

/******************************************************************************/
/*!
\brief - Get Visible toggle
\return m_visible
*/
/******************************************************************************/
bool Enemy::GetVisible(void) const
{
	return m_visible;
}
