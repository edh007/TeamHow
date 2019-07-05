/******************************************************************************/
/*!
\file   BaseEngine.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains header files(BaseEngine) to provide users base engine

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _STAGE_BASE_HEADER_
#define _STAGE_BASE_HEADER_

#include "../Engine/App/Application.h"
#include "../Engine/ObjectManager/Object/Object.h"

// Component Header
#include "../Engine/Component/ComponentFactory/ComponentFactory.h"

// Graphic Header
#include "../Engine/GameSystem/Graphic/Text/Text.h"
#include "../Engine/GameSystem/Graphic/Sprite/Sprite.h"
#include "../Engine/GameSystem/Graphic/Scene/Scene.h"
#include "../Engine/GameSystem/Graphic/Particle/Particle.h"

// Physics Header
#include "../Engine/GameSystem/Physics/World/World.h"
#include "../Engine/GameSystem/Physics/Node/Node.h"
#include "../Engine/GameSystem/Physics/Transform/Transform.h"
#include "../Engine/GameSystem/Physics/RigidBody/RigidBody.h"

// Sound Header
#include "../Engine/GameSystem/Sound/Sound.h"
#include "../Engine/GameSystem/Sound/Audio/Audio.h"

// Logic Header
#include "../Engine/GameSystem/Logic/Logic.h"
#include "../Engine/GameSystem/Logic/LogicFactory/LogicFactory.h"

// Util Header
#include "../Engine/Utilities/Time.h"
#include "../Engine/Utilities/Random.h"
#include "../Engine/Utilities/Debug/Debug.h"
#include "../Engine/Utilities/INI/iniReader.h"
#include "../Engine/Utilities/INI/iniWritter.h"
#include "../Engine/InputManager/InputManager.h"
#include "../Engine/InputManager/XboxInput.h"
#include "../Engine/ObjectManager/ObjectManager.h"
#include "../Engine/StateManager/GameStateManager/GameStateManager.h"

#endif //_STAGE_BASE_HEADER_