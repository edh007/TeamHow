/******************************************************************************/
/*!
\file   Scene.cpp
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2016/07/23(yy/mm/dd)

\description
Contains Scene class member and functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Scene.h"
#include "../../../ObjectManager/Object/Object.h"
#include "../../Physics/RigidBody/RigidBody.h"
#include "../../Physics/Transform/Transform.h"
#include "../Text/Text.h"
#include "../Sprite/Sprite.h"
#include "../Texture/Texture.h"
#include "../Particle/Particle.h"
#include "../../../InputManager/InputManager.h"
#include "../../../StateManager/GameStateManager/GameStateManager.h"

/******************************************************************************/
/*!
\brief - scene default constructor
*/
/******************************************************************************/
Scene::Scene(GameStateManager* GSM)
	:m_GSM(GSM), m_pGLM(GSM->GetGLManager()),
	cameraPos(vec3(0, 0, 100)), showMouse(false),
	cameraUp(vec3(0, 1, 0)), cam_angle(0.f)
{}

/******************************************************************************/
/*!
\brief - scene default destructor
*/
/******************************************************************************/
Scene::~Scene(void)
{
}

/******************************************************************************/
/*!
\brief - check the z value for sorting
*/
/******************************************************************************/
bool CheckZvalue(Object* l, Object* r)
{
    return l->GetComponent<Transform>(CT_TRANSFORM)->GetPosition().z 
		< r->GetComponent<Transform>(CT_TRANSFORM)->GetPosition().z;
}

/******************************************************************************/
/*!
\brief - add new sprite in the sprite list
*/
/******************************************************************************/
void Scene::AddSprite(Object* sprite)
{
	// Delete if there is same logic
	for (auto it = m_spriteList.begin(); it != m_spriteList.end(); ++it)
	{
		// If there is same owner and same type logic,
		// remove existing one
		if (sprite->GetID() == (*it)->GetID())
		{
			m_spriteList.erase(it);
			break;
		}
	}

    m_spriteList.push_back(sprite);
    std::sort(m_spriteList.begin(), m_spriteList.end(), CheckZvalue);
}

/******************************************************************************/
/*!
\brief - clear the sprite list in the Scene
*/
/******************************************************************************/
void Scene::RemoveSprite(const int id)
{
    for (auto it = m_spriteList.begin(); it != m_spriteList.end(); ++it)
    {
        if ((*it)->GetID() == id)
        {
            m_spriteList.erase(it);
            break;
        }
    }
}

/******************************************************************************/
/*!
\brief - initialize the scene class
*/
/******************************************************************************/
void Scene::Init(void)
{
    //if (m_GSM->GetResolution().width != 1024)
    //{
    //    m_GSM->SetResolution(m_GSM->GetResolution());
    //}
    //else
    //    m_GSM->SetResolution(SCR_1024X768);

    //b_width = 1024;
    //b_height = 768;
}

/******************************************************************************/
/*!
\brief - update the scene with sprites list
\param dt - delta time
*/
/******************************************************************************/
void Scene::Update(float dt)
{
	// Clear the screen
    glClearColor(m_color.x, m_color.y, m_color.z, m_color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::sort(m_spriteList.begin(), m_spriteList.end(), CheckZvalue);
	MouseCamera(showMouse);

	for (auto it = m_spriteList.begin(); it != m_spriteList.end(); ++it)
	{
		if ((*it)->HasComponent(CT_PARTICLE))
			DrawParticles(*it, dt);

		else
		{
			Camera(*it, dt);
			if ((*it)->HasComponent(CT_SPRITE)) {
				DrawSprites(*it);
			}
			else if ((*it)->HasComponent(CT_TEXT)) {
				DrawTexts(*it);
			}
		}
	}

    //if (m_GSM->GetGLManager()->checkResize == true || resizeToggle == true)
    //{
    //    //b_width = m_width;
    //    //b_height = m_height;
    //    resizeToggle = false;
    //    m_GSM->GetGLManager()->checkResize = false;
    //}
}

/******************************************************************************/
/*!
\brief - clear the sprite list in the Scene
*/
/******************************************************************************/
void Scene::Shutdown(void)
{
	m_spriteList.clear();
}

/******************************************************************************/
/*!
\brief - draw the sprites
\param obj - object that has sprite component
*/
/******************************************************************************/
void Scene::DrawSprites(Object* obj)
{
	Sprite* sprite = obj->GetComponent<Sprite>(CT_SPRITE);
	vec4 color = sprite->GetColor();
	glUniform1i(m_pGLM->GetUniform(TYPE), SPRITE);
	glUniform4f(m_pGLM->GetUniform(COLOR), color.x, color.y, color.z, color.w);

    //Refresh the buffer data
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Bind our texture in Texture Unit 0
    glBindTexture(GL_TEXTURE_2D, sprite->GetTexture()->GetID());

    //check sprite has many sprites or not
    if (sprite->GetFrame() > 1 && sprite->GetAnimation())
    {
        float frSpd = (1.f / sprite->m_frameSpeed);
        //after specific time, image will switch to the next one
        if (sprite->m_timer.GetElapsedTime() * sprite->GetOwner()->GetdtOffset() > frSpd)
        {
            sprite->currentFrame++;
            if(sprite->skipFirstAnimation == true && sprite->currentFrame >= sprite->GetFrame())
                sprite->currentFrame = 1;
            else if (sprite->currentFrame >= sprite->GetFrame())
                sprite->currentFrame = 0;
            //set new image
            sprite->m_timer.StartTime();
        }
    }
    sprite->m_frameUV = 1.f / float(sprite->GetFrame());

    if(sprite->current_ani_check == true)
    { 
        sprite->currentFrame = sprite->GetSpecificFrame();
        sprite->current_ani_check = false;
    }

    glUniform1i(m_pGLM->GetUniform(FLIP), sprite->GetFlip());

    //set animation 4x4 matrix for texture UV
	Animation.SetIdentity();
    Animation = Animation * mat44::Scale(vec3((sprite->m_frameUV), 1.f)) * mat44::Translate(vec3(sprite->m_frameUV * sprite->currentFrame * sprite->GetFlip(), 0.f));
	glUniformMatrix4fv(m_pGLM->GetUniform(ANIMATION), 1, GL_FALSE, &Animation.m_member[0][0]);
    
    //glEnable(GL_POINT_SMOOTH);
    //glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Draw the triangle
    if(sprite->GetDrawingCheck() == true)
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisable(GL_BLEND);
    //glDisable(GL_POINT_SMOOTH);
    //glDisable(GL_LINE_SMOOTH);
}

/******************************************************************************/
/*!
\brief - draw the particles
\param obj - object that has particle component
*/
/******************************************************************************/
void Scene::DrawParticles(Object* obj, float dt)
{
	Particle* particle = obj->GetComponent<Particle>(CT_PARTICLE);
	vec4 color = particle->GetColor();
	glUniform1i(m_pGLM->GetUniform(TYPE), PARTICLE);
	glUniform4f(m_pGLM->GetUniform(COLOR), color.x, color.y, color.z, color.w);

    glUniform1f(m_pGLM->GetUniform(SCALE), particle->GetOwner()->GetComponent<Transform>(CT_TRANSFORM)->GetScale().x);

    particle->Update(dt);

	// Render all particles
	// Use additive blending to give it a 'glow' effect
	if(particle->particleRenderType == ParticleRenderType::ADDITIVE)
	    glDepthMask(GL_FALSE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (Unit unit : particle->particles)
	{
		if (unit.Life > 0.0f)
		{
            Camera(obj, unit);
			glUniform2f(m_pGLM->GetUniform(OFFSET), unit.Position.x, unit.Position.y);
			glUniform4f(m_pGLM->GetUniform(COLOR), unit.Color.x, unit.Color.y, unit.Color.z, unit.Color.w);
            
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
			glBindTexture(GL_TEXTURE_2D, particle->GetTexture()->GetID());


			glDrawArrays(GL_TRIANGLES, 0, 6);
			
		}
	}
	if (particle->particleRenderType == ParticleRenderType::ADDITIVE)
	    glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	// Don't forget to reset to default blending mode
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


/******************************************************************************/
/*!
\brief - draw the texts
\param obj - object that has text component
*/
/******************************************************************************/
void Scene::DrawTexts(Object* obj)
{
    Text* text = obj->GetComponent<Text>(CT_TEXT);
    Transform* trs = obj->GetComponent<Transform>(CT_TRANSFORM);

    vec4 color = text->GetColor();

    glUniform1i(m_pGLM->GetUniform(TYPE), TEXT);
    glUniform4f(m_pGLM->GetUniform(COLOR), color.x, color.y, color.z, color.w);
    glEnable(GL_BLEND);
	//glEnable(GL_CULL_FACE);

    // Set init values
    GLfloat new_x = 0;//static_cast<GLfloat>(trs->GetPosition().x);
    GLfloat new_y = 0;//static_cast<GLfloat>(trs->GetPosition().y);
    GLfloat init_x = new_x, lower_y = 0;
    int num_newline = 1;

    // Iterate all character
    std::string::const_iterator c;
    for (c = text->GetText().begin(); c != text->GetText().end(); ++c)
    {
        const char newline = *c;
        if (newline == '\n')
        {
            new_x = init_x;
            lower_y = GLfloat(text->GetFontData().m_fontSize * num_newline);
            ++num_newline;
        }

        else
        {
            Character ch = text->GetFontData().m_chars[*c];
            GLfloat xpos = new_x + ch.Bearing.x * trs->GetScale().x;
            GLfloat ypos = new_y - (ch.Size.y - ch.Bearing.y) * trs->GetScale().y - lower_y;
            GLfloat zpos = trs->GetPosition().z;

            GLfloat w = ch.Size.x * trs->GetScale().x;
            GLfloat h = ch.Size.y * trs->GetScale().y;

            GLfloat vertices[6][5] = {
                { xpos, ypos + h, zpos, 0.0, 0.0 },
                { xpos + w, ypos + h, zpos, 1.0, 0.0 },
                { xpos + w, ypos, zpos, 1.0, 1.0 },
                { xpos + w, ypos, zpos, 1.0, 1.0 },
                { xpos, ypos, zpos, 0.0, 1.0 },
                { xpos, ypos + h, zpos, 0.0, 0.0 }
            };

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            //int t = static_cast<int>(ch.Advance);
            new_x += ((ch.Advance) >> 6) * trs->GetScale().x;
        }

    }
    glDisable(GL_BLEND);
	//glDisable(GL_CULL_FACE);
}

/******************************************************************************/
/*!
\brief - rotate the camera with the input
\param angle - rotate camera with this angle
*/
/******************************************************************************/
void Scene::RotateCamera(float angle)
{
    cameraUp.x = cosf(Math::DegToRad((angle + 90.f)));
    cameraUp.y = sinf(Math::DegToRad((angle + 90.f)));
}

/******************************************************************************/
/*!
\brief - set the cameraPos value
\param value - setting the camera with value's x,y,z
*/
/******************************************************************************/
void Scene::SetCameraPos(const vec3 & value)
{
	cameraPos = value;
}

/******************************************************************************/
/*!
\brief - get the cameraPos value
\return cameraPos - return the position of the camera position
*/
/******************************************************************************/
const vec3 & Scene::GetCameraPos(void) const
{
	return cameraPos;
}

/******************************************************************************/
/*!
\brief - set the background color
\param color - setting the color
*/
/******************************************************************************/
void Scene::SetColor(const vec4 & color)
{
	m_color = color;
}

/******************************************************************************/
/*!
\brief - get the background color
\return m_color - return the background color
*/
/******************************************************************************/
const vec4& Scene::GetColor(void) const
{
	return m_color;
}

/******************************************************************************/
/*!
\brief - calculate the MVP matrix each time in the update func
\param obj - calculate this object's MVP matrices
\param dt - delta time
*/
/******************************************************************************/
void Scene::Camera(Object* obj, float dt)
{
	glUniform1f(m_pGLM->GetUniform(TIME), Timer::GetInstance().GetElapsedTime());
	Transform* transform = obj->GetComponent<Transform>(CT_TRANSFORM);

    //if (m_GSM->GetCurrentState() == ST_MENU)
    //{
    //    m_GSM->GetResolution();
    //}

  //  if (m_GSM->GetGLManager()->checkResize == true || resizeToggle == true)
  //  {
  //      resizeToggle = true;
  //      if(obj->GetArcheType() == AT_PLAYER)
  //          m_GSM->GetResolution();

  //      vec3 pos = transform->GetPosition();


  //      float new_x = pos.x * b_width;
  //      float new_y = pos.y * b_height;
		//transform->SetPosition(vec3(new_x, new_y, pos.z));

  //      vec3 scale = transform->GetScale();
  //      if (obj->HasComponent(CT_TEXT))
  //      {
  //          unsigned int ft = obj->GetComponent<Text>(CT_TEXT)->GetFontData().m_fontSize;
  //          ft = ft * (unsigned int)(b_width);
  //          obj->GetComponent<Text>(CT_TEXT)->SetFontSize(ft);

  //          new_x = scale.x * b_width;
  //          new_y = scale.y * b_height;
  //      }
  //      else
  //      {           
  //          new_x = scale.x * b_width;
  //          new_y = scale.y * b_height;
  //          transform->SetScale(vec3(new_x, new_y, scale.z));
  //      }

		//if (obj->HasComponent(CT_RIGIDBODY))
		//{
		//	vec3 physicsScale = obj->GetComponent<RigidBody>(CT_RIGIDBODY)->GetScale();
		//	new_x = physicsScale.x * b_width;
		//	new_y = physicsScale.y * b_height;
		//	obj->GetComponent<RigidBody>(CT_RIGIDBODY)->SetScale(vec3(new_x, new_y, scale.z));
		//}
  //  }

    //MODEL : scale*rotation*translation
    Model.SetIdentity();
    vec3 rotate(0.f, 0.f, 1.f);
	Model = Model * mat44::Scale(transform->GetScale()) * mat44::Rotation(Math::DegToRad(transform->GetRotation()), rotate) * mat44::Translate(transform->GetPosition());

    m_width = float(m_GSM->GetResolution().width);
    m_height = float(m_GSM->GetResolution().height);
    Projection = Projection.Ortho((-m_width / 2), (m_width / 2), (-m_height / 2), (m_height / 2), 0.0f, 1000.0f);
    cameraView = cameraView.LookAt(cameraPos, vec3(cameraPos.x, cameraPos.y, 0), cameraUp);
	
    MVP = Projection.Transpose() * cameraView.Transpose() * Model.Transpose();
    MVP = MVP.Transpose();

	//// Send our transformation to the currently bound shader, 
	//// in the "MVP" uniform
	glUniformMatrix4fv(m_pGLM->GetUniform(MATRIX), 1, GL_FALSE, &MVP.m_member[0][0]);

	// Effect settor
	if (obj->HasComponent(CT_SPRITE))
	{
		// Wave effect...
		bool wave = obj->GetComponent<Sprite>(CT_SPRITE)->GetWaveToggle();
		glUniform1i(m_pGLM->GetUniform(WAVE_TOGGLE), wave);
		if (wave) {
			vec2 phase = obj->GetComponent<Sprite>(CT_SPRITE)->GetWavePhase();
			m_phase.x -= phase.x * dt;
			m_phase.y += phase.y * dt;
			if (m_phase.x < -1.f || m_phase.y > 1.f)
				m_phase.x = m_phase.y = 0.f;
		}

		// Blur settor
		bool blur = obj->GetComponent<Sprite>(CT_SPRITE)->GetBlurToggle();
		glUniform1i(m_pGLM->GetUniform(BLUR_TOGGLE), blur);
		if (blur)
			glUniform1f(m_pGLM->GetUniform(BLUR_AMOUNT), obj->GetComponent<Sprite>(CT_SPRITE)->GetBlurAmount());

		// Sobel effect...
		bool sobel = obj->GetComponent<Sprite>(CT_SPRITE)->GetSobelToggle();
		glUniform1i(m_pGLM->GetUniform(SOBEL_TOGGLE), sobel);
		if (sobel)
			glUniform1f(m_pGLM->GetUniform(SOBEL_AMOUNT), obj->GetComponent<Sprite>(CT_SPRITE)->GetSobelAmount());

		// Inverse settor
		glUniform1i(m_pGLM->GetUniform(INVERSE), obj->GetComponent<Sprite>(CT_SPRITE)->GetInverseToggle());
		
		// Ripple effect...
		glUniform1i(m_pGLM->GetUniform(RIPPLE_TOGGLE), obj->GetComponent<Sprite>(CT_SPRITE)->GetRippleToggle());
		
		glUniform2f(m_pGLM->GetUniform(WAVE_PHASE), m_phase.x, m_phase.y);
	}
}

/******************************************************************************/
/*!
\brief - calculate the MVP matrix each time in the update func
\param obj - calculate the particle's MVP matrices
\param dt - delta time
*/
/******************************************************************************/
void Scene::Camera(Object* particle, Unit unit)
{
	Transform* transform = particle->GetComponent<Transform>(CT_TRANSFORM);

    //if (m_GSM->GetGLManager()->checkResize == true)
    //{
    //    particle->GetComponent<Particle>(CT_PARTICLE)->ChangeResolution(m_GSM->GetGLManager()->ChangeResolutionW());

    //    vec3 pos = transform->GetPosition();
    //    vec3 scale = transform->GetScale();
    //    float new_x = float(m_GSM->GetResolution().width) * pos.x / b_width;
    //    float new_y = float(m_GSM->GetResolution().height) * pos.y / b_height;
    //    new_x = float(m_GSM->GetResolution().width) * scale.x / b_width;
    //    new_y = float(m_GSM->GetResolution().height) * scale.y / b_height;
    //    transform->SetScale(vec3(new_x, new_y, scale.z));

    //    if (particle->HasComponent(CT_RIGIDBODY))
    //    {
    //        vec3 physicsScale = particle->GetComponent<RigidBody>(CT_RIGIDBODY)->GetScale();
    //        new_x = float(m_GSM->GetResolution().width) * physicsScale.x / b_width;
    //        new_y = float(m_GSM->GetResolution().height) * physicsScale.y / b_height;
    //        particle->GetComponent<RigidBody>(CT_RIGIDBODY)->SetScale(vec3(new_x, new_y, scale.z));
    //    }
    //}

    //MODEL : scale*rotation*translation
    Model.SetIdentity();
    vec3 rotate(0.f, 0.f, 1.f);
    Model = Model * mat44::Scale(vec3(unit.Scale.x, unit.Scale.y, transform->GetScale().z)) * mat44::Rotation(Math::DegToRad(float(unit.Angle)), rotate) *
        mat44::Translate(vec3(unit.Position.x, unit.Position.y, transform->GetPosition().z));

    /*Model = Model * mat44::Scale(particle->GetScale()) * mat44::Rotation(Math::DegToRad(particle->GetRotation()), rotate) * 
        mat44::Translate(vec3(unit.Position.x, unit.Position.y, particle->GetComponent<Transform>(CT_TRANSFORM)->GetPosition().z));*/

    m_width = float(m_GSM->GetResolution().width);
    m_height = float(m_GSM->GetResolution().height);
    Projection = Projection.Ortho((-m_width / 2), (m_width / 2), (-m_height / 2), (m_height / 2), 0.0f, 1000.0f);
    cameraView = cameraView.LookAt(cameraPos, vec3(cameraPos.x, cameraPos.y, 0), cameraUp);

    MVP = Projection.Transpose() * cameraView.Transpose() * Model.Transpose();
    MVP = MVP.Transpose();

    // Send our transformation to the currently bound shader, 
    // in the "MVP" uniform
    glUniformMatrix4fv(m_pGLM->GetUniform(MATRIX), 1, GL_FALSE, &MVP.m_member[0][0]);
    glUniform2f(m_pGLM->GetUniform(SCREEN), m_width, m_height);

    //For Particle.
    MVP = Projection.Transpose() * Model.Transpose();
    MVP = MVP.Transpose();

    glUniformMatrix4fv(m_pGLM->GetUniform(PROJECT), 1, GL_FALSE, &MVP.m_member[0][0]);
}

/******************************************************************************/
/*!
\brief - get the position of the mouse
\param show - showing the position on console or not
*/
/******************************************************************************/
void Scene::MouseCamera(bool show)
{
    vec3 temp_mouse = InputManager::GetInstance().GetRawMousePosition();
    if (m_pGLM->fullScreen == false)
    {
        temp_mouse.x -= (m_width) / 2;
        temp_mouse.y = -(temp_mouse.y) + (m_height) / 2;
    }
    else
    {
        int vx = m_pGLM->viewportX;
        if (temp_mouse.x < m_pGLM->viewportX)
            temp_mouse.x = float(m_pGLM->viewportX);
        else if (temp_mouse.x > m_pGLM->b_width - vx)
            temp_mouse.x = float(m_pGLM->b_width - vx);

        temp_mouse.x *= m_pGLM->mouseCrX;
        temp_mouse.y *= m_pGLM->mouseCrY;
        vx = int(float(vx) * m_pGLM->mouseCrX);

        temp_mouse.x -= (m_width) / 2 + (vx);
        temp_mouse.y = -(temp_mouse.y) + (m_height) / 2;
    }
    temp_mouse += cameraPos;
    InputManager::GetInstance().SetOrthoMouse(temp_mouse);
	if (show)
		std::cout << "[" << temp_mouse.x << ", " << temp_mouse.y << "]" << std::endl;
}