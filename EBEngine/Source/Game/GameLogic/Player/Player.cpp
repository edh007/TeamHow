/******************************************************************************/
/*!
\file   Player.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/09/26(yy/mm/dd)

\description
Contains Player logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Player.h"
#include "../Enemy/Enemy.h"
#include "../../../BaseData/BaseEnigne.h"
#include "../Enemy/Damage.h"

/******************************************************************************/
/*!
\brief - PlayerBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* PlayerBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Player(Owner, key);
}

/******************************************************************************/
/*!
\brief - Player constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Player::Player(Object* Owner, LogicType key)
: GameLogic(Owner, key), m_blink(.05f), m_respone(3.f), m_shakeToggle(false),
m_footstack(0), m_life(1), m_slow(1.f), m_accel(.33f), death(nullptr),
m_damaged(false), m_colorToggle(true), m_frameChecker(false), m_now(nullptr),
m_condition(STOP), sound_term(0), m_playToggle(false), comeback(0), m_fsOffset(0)
{}

/******************************************************************************/
/*!
\brief - Load Player info
\param data - json parser
*/
/******************************************************************************/
void Player::Load(const Json::Value& data)
{
	if (data.isMember("Life") &&
		data["Life"].isInt())
		m_life = data["Life"].asInt();

	if (data.isMember("Speed") &&
		data["Speed"].isNumeric())
		m_speed = data["Speed"].asFloat();

	if (data.isMember("Accel") &&
		data["Accel"].isNumeric())
		m_accel = data["Accel"].asFloat();
}

/******************************************************************************/
/*!
\brief - Initialize Player info
*/
/******************************************************************************/
void Player::Init(void)
{
	// Set player's info to global info
	m_GSM->GetGameData()->player = m_Owner;
	m_GSM->GetGameData()->player_id = m_Owner->GetID();
	m_GSM->GetGameData()->player_searchDist = 500.f;
	m_GSM->GetGameData()->player_chopper = false;

	// Set audio assets
	m_OBM->GetGameSound()->AddAudio("footstep", "footstep");
	footstep = m_OBM->GetGameSound()->GetAudio("footstep");
	footstep->SetVolume(m_GSM->GetGameData()->volume);

	m_OBM->GetGameSound()->AddAudio("death", "death");
	death = m_OBM->GetGameSound()->GetAudio("death");
	death->SetVolume(m_GSM->GetGameData()->volume);

	// Set body info
	m_body = m_Owner->GetComponent<RigidBody>(CT_RIGIDBODY);
	m_position = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();

	m_body->SetScale(m_body->GetScale() * .5f);
	m_body->SetScaleToggle(false);

	// Set foot animation(separate object)
	m_foot = new Object(AT_FOOT, m_OBM);
	m_foot->AddComponent(ComponentFactory::CreateComponent(m_foot, CT_SPRITE));
	m_foot->GetComponent<Sprite>(CT_SPRITE)->SetFrame(10);
	m_foot->GetComponent<Sprite>(CT_SPRITE)->SetTexture(m_OBM->GetTexture("Player_Walk"));
	m_foot->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(50, 75));
	m_OBM->AddObject(m_foot);

	m_now = new Object(AT_HUD, m_OBM);
	m_now->AddComponent(ComponentFactory::CreateComponent(m_now, CT_TEXT));
	m_now->GetComponent<Text>(CT_TEXT)->SetFontSize(50);
	m_now->GetComponent<Text>(CT_TEXT)->SetText("NOW!!!");
	m_now->GetComponent<Transform>(CT_TRANSFORM)->SetScale(vec3(1,1,0));
	m_OBM->AddObject(m_now);
	
	tc[0] = tc[1] = tc[2] = false;
	m_color = Random::GetInstance().GetRandomVec3(0.f, 1.f);
	m_color.w = 1.f;

	// Init player's global info
	m_GSM->GetGameData()->footstack = 0.f;
	m_GSM->GetGameData()->killedEnemies = 0;
	m_GSM->GetGameData()->player_Active = true;
    m_GSM->GetGameData()->sprPnchParticleTog = false;
    m_GSM->GetGameData()->pnchTog = false;
	m_GSM->GetGameData()->dtPower = 0.f;
	m_GSM->GetGameData()->player_lastCondition = STOP;
	m_GSM->GetGameData()->sneakKill = 0;
	m_GSM->GetGameData()->dashKill = 0;
	m_GSM->GetGameData()->sneakTime = 0.f;
	m_GSM->GetGameData()->dashTime = 0.f;
	m_GSM->GetGameData()->player_point = 0;

    m_GSM->GetGameData()->realViewSight = 350.f;
    m_GSM->GetGameData()->fogToggle = true;
}

/******************************************************************************/
/*!
\brief - Update Player info
\param dt - delta time
*/
/******************************************************************************/
void Player::Update(float dt)
{
	if (m_GSM->GetGameData()->player_Active)
	{
		m_GSM->GetGameData()->player_frame
			= m_Owner->GetComponent<Sprite>(CT_SPRITE)->currentFrame;

		if (!m_GSM->GetGameData()->immortal)
			DamagedEffect(dt);

		FootStack(dt);
		Controller(dt);

		// If cheat activate,
		// then set color red
		if (m_GSM->GetGameData()->immortal)
			m_color = vec4(1.f, 0.f, 0.f, 1.f);

		m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetColor(m_color);
	}

	m_color = m_Owner->GetComponent<Sprite>(CT_SPRITE)->GetColor();
	m_foot->GetComponent<Sprite>(CT_SPRITE)->SetColor(m_color);
}

/******************************************************************************/
/*!
\brief - Shutdown Player info
*/
/******************************************************************************/
void Player::Shutdown(void)
{
	std::vector<Object*> foot;
	m_OBM->GetObjects(AT_FOOT, foot);
	if (foot.size()) {
		int foot_id = foot[0]->GetID();
		m_OBM->RemoveObject(foot_id);
	}
}

/******************************************************************************/
/*!
\brief - Unload Punch info
*/
/******************************************************************************/
void Player::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Control player
\param dt - delta time
*/
/******************************************************************************/
void Player::Controller(float dt)
{
	// Renew player's z order and sound position
	// Move camera woth player's position
	vec3 player_pos = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
	vec3 camera_pos = m_GSM->GetGameData()->cameraPos;

	m_OBM->GetGameSound()->SetListenerPosition(camera_pos);
	footstep->SetPosition(camera_pos);
	death->SetPosition(camera_pos);

	m_OBM->GetGameScene()->SetCameraPos(vec3(player_pos.x, player_pos.y,
		m_OBM->GetGameScene()->GetCameraPos().z));

	m_condition = STOP;
	float final_speed = m_speed;
	bool foot_animation = false;

	float degree;

	// Set the Xbox Input Toggle
	bool xInput = XboxInput::Instance()->IsConnected();

	// Run
	// Speed to be init in player's velocity

	// Cannot move while player charging gauge....
	if (!m_GSM->GetGameData()->dtPower)
	{
		// Save camera y position
		m_GSM->GetGameData()->camera_y
			= m_GSM->GetGameData()->cameraPos.y;

		if (InputManager::GetInstance().KeyPressed(KEY_D) ||
			(xInput && XboxInput::Instance()->leftStickX > 0.5f))
		{
			velocity.x += final_speed * m_slow;
			foot_animation = true;
			m_condition = RUN;
		}

		if (InputManager::GetInstance().KeyPressed(KEY_A) ||
			(xInput && XboxInput::Instance()->leftStickX < -0.5f))
		{
			velocity.x -= final_speed * m_slow;
			foot_animation = true;
			m_condition = RUN;
		}

		if (InputManager::GetInstance().KeyPressed(KEY_W) ||
			(xInput && XboxInput::Instance()->leftStickY > 0.5f))
		{
			velocity.y += final_speed * m_slow;
			foot_animation = true;
			m_condition = RUN;
		}

		if (InputManager::GetInstance().KeyPressed(KEY_S) ||
			(xInput && XboxInput::Instance()->leftStickY < -0.5f))
		{
			velocity.y -= final_speed * m_slow;
			foot_animation = true;
			m_condition = RUN;
		}

		if (InputManager::GetInstance().KeyPressed(KEY_SHIFT) ||
			(xInput && XboxInput::Instance()->GetButtonPressed(XboxInput::Instance()->LEFT_SHOULDER)))
		{
			velocity *= m_accel;
			m_condition = SNEAK;
		}
	}

	// Implement player's speed
	m_Owner->GetComponent<RigidBody>(CT_RIGIDBODY)->SetVelocity(velocity);

	// Init vel
	velocity = vec3();

	// Get degree in advance
	degree = Math::Degree_pt(player_pos,
		InputManager::GetInstance().GetOrthoPosition());

	if (xInput)
	{
		vec3 xbox(XboxInput::Instance()->leftStickX, XboxInput::Instance()->leftStickY, 0);
		if (xbox.Length() > 0.5f)
			degree = Math::RadToDeg(atan2(xbox.y, xbox.x));

		xbox = vec3(XboxInput::Instance()->rightStickX, XboxInput::Instance()->rightStickY, 0);
		if (xbox.Length() > 0.5f)
			degree = Math::RadToDeg(atan2(xbox.y, xbox.x));
	}

	// Rotate player by mouse position
	m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetRotation(
		degree);

	// Set foot animation
	vec3 scale = m_foot->GetComponent<Transform>(CT_TRANSFORM)->GetScale();

	// set foot's position and degree
	static float offset;
	if (m_GSM->GetGameData()->frameRange) {
		degree += 30.f;
		offset = 0.f;
	}

	else
		offset = .5f;

	vec3 foot_pos = Math::Rotation(player_pos + vec3(scale.x)* offset,
		m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetRotation(), player_pos);
	foot_pos.z = player_pos.z - .1f;

	m_foot->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(foot_pos);
	m_foot->GetComponent<Transform>(CT_TRANSFORM)->SetRotation(degree);

	if (foot_animation) {
		if (m_condition == RUN)
			m_foot->GetComponent<Sprite>(CT_SPRITE)->SetFrameSpd(20.f);
		else
			m_foot->GetComponent<Sprite>(CT_SPRITE)->SetFrameSpd(4.f);
	}

	else
		m_foot->GetComponent<Sprite>(CT_SPRITE)->SetSpecificFrame(1);

	m_foot->GetComponent<Sprite>(CT_SPRITE)->SetAnimation(foot_animation);

	// const value
	static const float punchGauge = 3.f;
	static bool punchToggle = true;

	// Cbheck right mouse click
	if (InputManager::GetInstance().GetPressedStatus() == UP
		&& (!InputManager::GetInstance().KeyPressed(MOUSE_RIGHT) ||
		(!(xInput && XboxInput::Instance()->GetButtonPressed(XboxInput::Instance()->RIGHT_SHOULDER))))) {
		if (!m_GSM->GetGameData()->clicked)
			m_GSM->GetGameData()->dtPower = 0.f;
		m_GSM->GetGameData()->clicked = false;
		//std::cout << "here\n";
	}

	if (InputManager::GetInstance().KeyPressed(MOUSE_RIGHT)
		|| (xInput && XboxInput::Instance()->GetButtonPressed(XboxInput::Instance()->RIGHT_SHOULDER)))
		m_GSM->GetGameData()->clicked = true;

	// If pressed enough,
	if (m_GSM->GetGameData()->dtPower >= punchGauge)
	{
		vec4 nowPos = camera_pos -
			vec3(100, -m_GSM->GetGameData()->resolution.y * .111f, 0.f);
		nowPos.z = 10.f;

		m_now->GetComponent<Text>(CT_TEXT)->SetColor(m_color);
		m_now->GetComponent<Transform>(CT_TRANSFORM)->SetPosition(nowPos);

		if (!m_GSM->GetGameData()->clicked)
		{
			m_GSM->GetGameData()->sprPnchParticleTog = true;
			m_playToggle = true;
			m_GSM->GetGameData()->cameraPos.y
				= m_GSM->GetGameData()->camera_y;
		}
	}

    else if (!m_damaged && !m_GSM->GetGameData()->dtPower) {
        m_GSM->GetGameData()->sprPnchParticleTog = false;
        m_color = vec4(1, 1, 1, 1);
		m_now->GetComponent<Text>(CT_TEXT)->SetColor(vec4());
    }

    if (!m_GSM->GetGameData()->player_frame) {
        if (!m_GSM->GetGameData()->dtPower
			&& (InputManager::GetInstance().KeyTriggered(MOUSE_LEFT) ||
            (xInput && XboxInput::Instance()->GetButtonTrigger(XboxInput::Instance()->XBOX_A))))
        {
            m_GSM->GetGameData()->pnchTog = true;
            m_playToggle = true;
        }

        else if (m_GSM->GetGameData()->clicked 
			&& !m_GSM->GetGameData()->searchToggle
			&& !m_GSM->GetGameData()->tmToggle
			&& m_GSM->GetGameData()->enoughPoint) {
            m_GSM->GetGameData()->pnchTog = false;
            m_GSM->GetGameData()->dtPower += dt;
            SuperPunchEffect(dt);
        }

		else 
			m_GSM->GetGameData()->pnchTog = false;
    }

	// Set punch animation
	m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetAnimation(m_playToggle);
	if (m_Owner->GetComponent<Sprite>(CT_SPRITE)->GetCurrentFrame() == 1 && !m_frameChecker) 
			m_frameChecker = true;

	else if (m_frameChecker && !m_Owner->GetComponent<Sprite>(CT_SPRITE)->GetCurrentFrame()) {
		m_playToggle = m_frameChecker = false;
		m_Owner->GetComponent<Sprite>(CT_SPRITE)->SetSpecificFrame(0);
	}

	// Save player's last condition
	if (m_GSM->GetGameData()->player_condition != m_condition)
		m_GSM->GetGameData()->player_lastCondition = m_GSM->GetGameData()->player_condition;
	
	m_GSM->GetGameData()->player_condition = m_condition;
	m_GSM->GetGameData()->player_pos = player_pos;

	// Count time
	if (m_condition == SNEAK)
		m_GSM->GetGameData()->sneakTime += dt;

	else if (m_condition == RUN)
		m_GSM->GetGameData()->dashTime += dt;
}

/******************************************************************************/
/*!
\brief - Set player's speed
\param speed
*/
/******************************************************************************/
void Player::SetSpeed(float speed)
{
	m_speed = speed;
}

/******************************************************************************/
/*!
\brief - Get player's speed
\return m_speed
*/
/******************************************************************************/
float Player::GetSpeed(void) const
{
	return m_speed;
}

/******************************************************************************/
/*!
\brief - Get player's m_slow toggle
\return m_slow
*/
/******************************************************************************/
float Player::GetSlow(void) const
{
	return m_slow;
}

/******************************************************************************/
/*!
\brief - Get player's life
\return m_life
*/
/******************************************************************************/
int Player::GetLife(void) const
{
	return m_life;
}

/******************************************************************************/
/*!
\brief - Set player's life
\param life
*/
/******************************************************************************/
void Player::SetLife(int life)
{
	m_life = life;
}

/******************************************************************************/
/*!
\brief - Player's damage effect
\param dt
*/
/******************************************************************************/
void Player::DamagedEffect(float dt)
{
	if (m_body->IsCollided())
	{
		std::vector<Object*> damageList;
		m_OBM->GetObjects(DAMAGE, damageList);

		m_slow = 1.f;
		for (auto it = damageList.begin(); it != damageList.end(); ++it)
		{
			// If there was a collision,
			// check it
			if (m_body->IsCollidedWith((*it)->GetID()))
			{
				Damage* damage = (*it)->GetLogic<Damage>(DAMAGE);

				if (damage->GetActiveToggle())
				{
					// If there is a slow offset, then make player slow
					m_slow = damage->GetSlow();

					// Decrease the life of character
					m_life -= damage->GetDamage();

					// If object is permanent, skip 
					if (!damage->GetPermanent())
					{
						// If not, reduce its life
						damage->SetLife(damage->GetLife() - 1);

						// And if the result is 0,
						// then delete it.
						if (!damage->GetLife())
							m_OBM->RemoveObject(damage->GetOwnerID());
					}

					// Active visual damage effect
					m_damaged = true;
					m_timer.StartTime();

					// If player's life is 0,
					// kill her
					if (!m_life) {
						m_GSM->GetGameData()->player_death++;
						death->Play();
						RemoveOwner(true);
					}
				}
			}
		}
	}

	// Damage effect
	if (m_damaged)
	{
		dt_Stack += dt;

		// Change the toggle per blink secs
		if (dt_Stack > m_blink)
		{
			dt_Stack = 0.f;
			m_colorToggle = !m_colorToggle;
		}

		// Yellow
		if (m_colorToggle)
			m_color = vec4(1, 1, 0, 1);

		// Red
		else
			m_color = vec4(1, 0, 0, 1);

		// Make normally again
		if (m_timer.GetElapsedTime() > m_respone)
		{
			m_color = vec4(1, 1, 1, 1);
			m_colorToggle = true;
			m_damaged = false;
		}
	}
}

/******************************************************************************/
/*!
\brief - Get player's damage toggle
\return m_damaged
*/
/******************************************************************************/
bool Player::GetDamage(void) const
{ 
	return m_damaged; 
}

/******************************************************************************/
/*!
\brief - Get player's condition
\return m_condition
*/
/******************************************************************************/
PlayerCondition Player::GetConidition(void) const
{
	return m_condition;
}

/******************************************************************************/
/*!
\brief - Calculate player's footstep noise
\param dt 
*/
/******************************************************************************/
void Player::FootStack(float dt)
{
	// Increase the warning sign
	m_fsOffset = 1.5f;
	
	// If cheat code activated,
	// do not update
	if (m_GSM->GetGameData()->silent) {
		m_footstack = 0.f;
		m_GSM->GetGameData()->footstack = m_footstack;
	}

	// Unless...
	else {

		// If player is not detected by radar,
		// update the footstack
		if (!m_GSM->GetGameData()->radarToggle) {
			if (m_condition == RUN)
			{
				sound_term = 0;
				m_footstack += m_fsOffset * dt;

				if (m_footstack > 6.f)
					m_footstack = 6.f;
			}

			else
			{
				if (m_condition == SNEAK)
				{
					m_fsOffset = 0.f;
					sound_term++;
					if (sound_term > 60)
						sound_term = 0;
				}

				// Decrease the waring sign
				m_footstack -= .5f * dt;
				if (m_footstack < 0.f)
					m_footstack = 0.f;
			}
			m_GSM->GetGameData()->footstack = m_footstack;
		}
	}

	// Play the footstep sound
	if (!footstep->IsPlaying() && !sound_term && m_condition != STOP) {
		footstep->SetVolume(m_GSM->GetGameData()->volume);
		footstep->Play();
	}

	if (m_GSM->GetGameData()->searchToggle)
		m_foot->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4());
	else
		m_foot->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1,1,1,1));
		
}


/******************************************************************************/
/*!
\brief - Activate super punch's effect
\param dt
*/
/******************************************************************************/
void Player::SuperPunchEffect(float dt)
{
	float dtPower = m_GSM->GetGameData()->dtPower;

	// Lock the size of shaking range
	if (dtPower > 3.f)
		dtPower = 3.f;

	if (m_shakeToggle)
		m_GSM->GetGameData()->cameraPos.y += dt * dtPower * 300.f;
	else
		m_GSM->GetGameData()->cameraPos.y -= dt * dtPower * 300.f;
	
	m_shakeToggle = !m_shakeToggle;
	m_OBM->GetGameScene()->SetCameraPos(m_GSM->GetGameData()->cameraPos);

	// Random title color
	if (tc[0]) {
		m_color.x += dt * dtPower;
		if (m_color.x > 1.f) {
			tc[0] = !tc[0];
			m_color.x = 1.f;
		}
	}

	else {
		m_color.x -= dt * dtPower;
		if (m_color.x < .25f) {
			tc[0] = !tc[0];
			m_color.x = 0.25f;
		}
	}

	if (tc[1]) {
		m_color.y += dt * dtPower;
		if (m_color.y > 1.f) {
			tc[1] = !tc[1];
			m_color.y = 1.f;
		}
	}

	else {
		m_color.y -= dt * dtPower;
		if (m_color.y < .25f) {
			tc[1] = !tc[1];
			m_color.y = .25f;
		}
	}

	if (tc[2]) {
		m_color.z += dt * dtPower;
		if (m_color.z > .25f) {
			tc[2] = !tc[2];
			m_color.z = .25f;
		}
	}

	else {
		m_color.z -= dt * dtPower;
		if (m_color.z < .25f) {
			tc[2] = !tc[2];
			m_color.z = .25f;
		}
	}
}
