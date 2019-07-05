/******************************************************************************/
/*!
\file   Punch.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/02/22(yy/mm/dd)

\description
Contains Punch logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Punch.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/Damage.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - PunchBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* PunchBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Punch(Owner, key);
}

/******************************************************************************/
/*!
\brief - Punch constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Punch::Punch(Object* Owner, LogicType key)
: GameLogic(Owner, key), m_sound(nullptr), soundTime(0.f),
soundToggle(true), hitTime(0.f), hitToggle(true)
{}

/******************************************************************************/
/*!
\brief - Load Punch info
\param data - json parser
*/
/******************************************************************************/
void Punch::Load(const Json::Value& /*data*/)
{

}

/******************************************************************************/
/*!
\brief - Initialize Punch info
*/
/******************************************************************************/
void Punch::Init(void)
{
	m_body = m_Owner->GetComponent<RigidBody>(CT_RIGIDBODY);
	
	// Set Sound
	m_OBM->GetGameSound()->AddAudio("punch", "punch");
	m_sound = m_OBM->GetGameSound()->GetAudio("punch");
	m_sound->SetVolume(m_GSM->GetGameData()->volume);

	// Set hit effect
	for (int i = 0; i < 4; ++i) {
		std::string tmp("hit");
		tmp += std::to_string(i+1);
		m_OBM->GetGameSound()->AddAudio(tmp.c_str(), tmp.c_str());
		m_hit[i] = m_OBM->GetGameSound()->GetAudio(tmp.c_str());
		m_hit[i]->SetVolume(m_GSM->GetGameData()->volume);
	}
}

/******************************************************************************/
/*!
\brief - Update Punch info
\param dt - delta time
*/
/******************************************************************************/
void Punch::Update(float dt)
{
	static float punchGauge = 3.f;

	if (m_OBM->HasObject(m_GSM->GetGameData()->player_id)
		&& m_GSM->GetGameData()->player_Active)
	{
		vec3 player_pos = m_GSM->GetGameData()->cameraPos;

		// If the sound is playing.
		if (soundToggle == false) {
			if (!m_sound->IsPlaying())
			{
				soundToggle = true;
				m_sound->Stop();
			}
		}

		if (hitToggle == false) {
			hitTime += dt;
			if (hitTime > 0.5f) {
				hitToggle = true;
				hitTime = 0;
				for (int i = 0; i < 4; ++i)
					m_hit[i]->Stop();
			}
		}

		// Check X box input
		bool xInput = XboxInput::Instance()->IsConnected()
			&& XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->XBOX_A);

		// set toggle
		if (m_GSM->GetGameData()->player_point >= 100)
			m_GSM->GetGameData()->enoughPoint = true;
		else
			m_GSM->GetGameData()->enoughPoint = false;

		// If super punch condition is activated
		bool superPunch = m_GSM->GetGameData()->dtPower >= punchGauge
			&& m_GSM->GetGameData()->enoughPoint
			&& !m_GSM->GetGameData()->clicked;

		// If punch got collided
		bool normalPunch = m_GSM->GetGameData()->pnchTog;

		// Check frame range of punching animation
		m_GSM->GetGameData()->frameRange 
			= (m_GSM->GetGameData()->player_frame > 2 
			&& m_GSM->GetGameData()->player_frame < 8);

		//std::cout << m_GSM->GetGameData()->player_frame << std::endl;
		//std::cout << superPunch << std::endl;

		if (superPunch || ((normalPunch || xInput)
			&& m_GSM->GetGameData()->frameRange)) {
			m_body->ActivateCollider(true);

			// Play the sound
			if (soundToggle == true) {
				m_sound->SetPosition(player_pos);
				m_sound->Play();
				soundToggle = false;
			}

			// And kill all enemies
			wall.clear();
			m_OBM->GetObjects(AT_WALL, wall);
			std::vector<Object*> enemies;
			m_OBM->GetObjects(AT_ENEMY, enemies);

			bool pointChecker = true;
			for (auto it : enemies) {
				// Punch away the enemy
				int enemy_id = it->GetID();
				Object* enemy = m_OBM->GetGameObject(enemy_id);

				// If there is a wall between enemy and player,
				// then cancel the process
				bool between = true;

				for (auto it_wall : wall) {
					if (between)
						between = m_OBM->GetGameWorld()->CollisionIntersect
						(it_wall->GetComponent<RigidBody>(CT_RIGIDBODY),
							player_pos, enemy->GetComponent<Transform>(CT_TRANSFORM)->GetPosition());
					else
						break;
				}

				// Active super punch
				bool activeSP = superPunch
					&& enemy->GetLogic<Enemy>(ENEMY)->GetDistanceformPlayer() < 300.f;

				if (((m_body->IsCollidedWith(enemy_id) && between)
					|| activeSP)
					&& enemy->HasLogic(ENEMY))	{
					Enemy* enemyLogic = enemy->GetLogic<Enemy>(ENEMY);
					// If enemy just got hit...
					if (enemyLogic->GetCondition() != PUNCHED
						|| activeSP) {
						// Play the sound
						if (hitToggle == true) {
							int offset = Random::GetInstance().GetRandomInt(0, 3);
							m_hit[offset]->SetPosition(m_GSM->GetGameData()->cameraPos);
							m_hit[offset]->Play();
							hitToggle = false;
						}

						if (XboxInput::Instance()->IsConnected())
							XboxInput::Instance()->SetVibration(30000, 0.5f);

						// Update the killed enemy;
						if (!m_GSM->GetGameData()->gamenextCondition
							&& !m_GSM->GetGameData()->gameoverCondition) {

							++m_GSM->GetGameData()->killedEnemies;

							// Super punch settings
							// set point
							//if (pointChecker) {
								if (activeSP && pointChecker) {
									m_GSM->GetGameData()->player_point -= 100;

									if (m_GSM->GetGameData()->player_point < 0)
										m_GSM->GetGameData()->player_point = 0;

									m_GSM->GetGameData()->dtPower = 0.f;
									pointChecker = false;
									//std::cout << "decrease\n";
								}

								else if (pointChecker
									&& !activeSP) {
									m_GSM->GetGameData()->player_point += 50;
									//std::cout << "increase\n";
								}
							//}

							// Sneaking kill
							if (m_GSM->GetGameData()->player_condition == 0
								|| (m_GSM->GetGameData()->player_condition == 2
									&& m_GSM->GetGameData()->player_lastCondition == 0))
								++m_GSM->GetGameData()->sneakKill;

							// Dash kill
							else if (m_GSM->GetGameData()->player_condition == 1
								|| (m_GSM->GetGameData()->player_condition == 2
									&& m_GSM->GetGameData()->player_lastCondition == 1))
								++m_GSM->GetGameData()->dashKill;
						}

						// Stop other enemy's logics
						RigidBody* enemyBody = enemy->GetComponent<RigidBody>(CT_RIGIDBODY);
						enemyBody->SetSpeed(350.f);
						enemyBody->SetFriction(500.f);
						enemyBody->SetDirectionVector(
							enemyBody->GetTransform()->GetPosition() - player_pos);
						enemyBody->ActivateResponse(true);
						enemyLogic->SetCondition(PUNCHED);
						enemyLogic->ActiveBehavior(false);

						// Check if this enemy to be resistant
						if (enemyLogic->GetEnemyType() != DEFENDER
							&& enemyLogic->GetEnemyType() != BOMBER)
						{
							// Delete entirely...
							enemyBody->SetSpeed(350.f);
							enemyBody->SetFriction(500.f);
							enemy->RemoveLogic(DAMAGE);
							enemy->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(.25f, .25f, .25f, 1.f));
							enemyLogic->ActivePatrol(false);
						}
					}
				}

				if (!m_GSM->GetGameData()->clicked)
					m_GSM->GetGameData()->dtPower = 0.f;

			} // for (auto it_wall : wall) {

		} // if (m_GSM->GetGameData()->player_Punch) {

		// Unless...
		else {
			m_body->ActivateCollider(false);
		}

	}// if (m_OBM->HasObject(m_GSM->GetGameData()->player_id))
}

/******************************************************************************/
/*!
\brief - Shutdown Punch info
*/
/******************************************************************************/
void Punch::Shutdown(void)
{
	m_sound->Stop();
}

/******************************************************************************/
/*!
\brief - Unload Punch info
*/
/******************************************************************************/
void Punch::Unload(void)
{

}