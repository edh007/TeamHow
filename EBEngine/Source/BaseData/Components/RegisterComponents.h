/******************************************************************************/
/*!
\file   RegisterLogics.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/12/20(yy/mm/dd)

\description
Contains components' headers and init components builder function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _REGISTER_COMPONENTS_H_
#define _REGISTER_COMPONENTS_H_

#include <thread>
#include "ComponentType.h"
#include "../../Engine/Component/ComponentFactory/ComponentFactory.h"

#include "../../Engine/GameSystem/Physics/Transform/Transform.h"
#include "../../Engine/GameSystem/Physics/RigidBody/RigidBody.h"

#include "../../Engine/GameSystem/Graphic/Text/Text.h"
#include "../../Engine/GameSystem/Graphic/Sprite/Sprite.h"
#include "../../Engine/GameSystem/Graphic/Particle/Particle.h"

/******************************************************************************/
/*!
\brief - Register Components
*/
/******************************************************************************/
inline void RegisterComponents(void)
{
	//std::thread ct_thread[CT_END];
	//ct_thread[CT_TRANSFORM] = std::thread(ComponentFactory::AddBuilder, CT_TRANSFORM, new TransformBuilder);
	//ct_thread[CT_RIGIDBODY] = std::thread(ComponentFactory::AddBuilder, CT_RIGIDBODY, new RigidBodyBuilder);

	//ct_thread[CT_TEXT] = std::thread(ComponentFactory::AddBuilder, CT_TEXT, new TextBuilder);
	//ct_thread[CT_SPRITE] = std::thread(ComponentFactory::AddBuilder, CT_SPRITE, new SpriteBuilder);
	//ct_thread[CT_PARTICLE] = std::thread(ComponentFactory::AddBuilder, CT_PARTICLE, new ParticleBuilder);

	//for (int ct_num = 0; ct_num < CT_END; ++ct_num)
	//	if (ct_thread[ct_num].joinable())
	//		ct_thread[ct_num].join();

	// Basic Component
	ComponentFactory::AddBuilder(CT_TRANSFORM, new TransformBuilder);
	ComponentFactory::AddBuilder(CT_RIGIDBODY, new RigidBodyBuilder);
	ComponentFactory::AddBuilder(CT_TEXT, new TextBuilder);
	ComponentFactory::AddBuilder(CT_SPRITE, new SpriteBuilder);
	ComponentFactory::AddBuilder(CT_PARTICLE, new ParticleBuilder);
}

#endif // _REGISTER_COMPONENTS_H_