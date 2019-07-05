/******************************************************************************/
/*!
\file   JsonParser.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/07/30(yy/mm/dd)
\description
Contains JsonParser's class and member function
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include <mutex>
#include <atomic>
#include <thread>
#include <fstream>
#include <iostream>
#include "../../ObjectManager/Object/Object.h"
#include "../../ObjectManager/ObjectManager.h"

#include "../../Component/ComponentFactory/ComponentFactory.h"

#include "../../GameSystem/Physics/Transform/Transform.h"
#include "../../GameSystem/Physics/RigidBody/RigidBody.h"

#include "../../GameSystem/Sound/Sound.h"
#include "../../GameSystem/Sound/Audio/Audio.h"
#include "../../GameSystem/Sound/SoundManager/SoundManager.h"

#include "../../GameSystem/Graphic/Text/Text.h"
#include "../../GameSystem/Graphic/Sprite/Sprite.h"
#include "../../GameSystem/Graphic/Scene/Scene.h"
#include "../../GameSystem/Graphic/Particle/Particle.h"

#include "../../GameSystem/Logic/GameLogic/GameLogic.h"
#include "../../GameSystem/Logic/LogicFactory/LogicFactory.h"

#include "../../StateManager/GameStateManager/GameStateManager.h"

/******************************************************************************/
/*!
\brief - JsonParser Constructor
*/
/******************************************************************************/
JsonParser::JsonParser()
{}

/******************************************************************************/
/*!
\brief - JsonParser Destructor
*/
/******************************************************************************/
JsonParser::~JsonParser()
{}

/******************************************************************************/
/*!
\brief - Get loaded data
\return m_data
*/
/******************************************************************************/
const Json::Value& JsonParser::GetLoadedData(void) const
{
	return m_data;
}

/******************************************************************************/
/*!
\brief - Save data as json file
\param dir - directory to save json file
\param contents - json vaule
*/
/******************************************************************************/
void JsonParser::Save(const char* dir, const Json::Value& contents)
{
	std::ofstream save_dir;
	save_dir.open(dir);

	Json::StyledWriter writter;
	save_dir << writter.write(contents);
}

/******************************************************************************/
/*!
\brief - Load data from json file
\param dir - directory to load json file
*/
/******************************************************************************/
void JsonParser::Load(char* dir)
{
	// Load json data to input file stream
	std::ifstream load_dir(dir, std::ifstream::binary);

	// Move to json data
	load_dir >> m_data;

	// Convert to string
	Json::StyledWriter writer;
	str = writer.write(m_data);

	// Parser checker
	Json::Reader reader;
	bool parsingRet = reader.parse(str, m_data);
	if (!parsingRet)
		std::cout << "Failed to parse Json : " << reader.getFormattedErrorMessages();
}

/******************************************************************************/
/*!
\brief - Init asset data to use in engine
\param GLM - Pointer to gl manager
\param SM - Pointer to sound manager
*/
/******************************************************************************/
void JsonParser::InitAssetData(GLManager* GLM, SoundManager* SM)
{
	std::mutex m_mutex;

	// Load textures
	if (m_data.isMember("Texture"))
	{
		for (auto it = m_data["Texture"].begin();
			it != m_data["Texture"].end(); ++it)
		{
			if ((*it).isMember("key") &&
				(*it)["key"].isString() &&
				(*it).isMember("directory") &&
				(*it)["directory"].isString()) {
				GLM->AddTexture(
					(*it)["key"].asCString(),
					(*it)["directory"].asCString());
			}
		}
	}

	// Alarm Error
	else
		std::cerr << "Cannot load texture files!\n";

	 // Load Sound
	if (m_data.isMember("Sound"))
	{

		for (auto it = m_data["Sound"].begin();
			it != m_data["Sound"].end(); ++it)
		{
			if ((*it).isMember("key") &&
				(*it)["key"].isString() &&
				(*it).isMember("directory") &&
				(*it)["directory"].isString()) {
				SM->AddSound((*it)["key"].asCString(),
					(*it)["directory"].asCString());
			}
		}
	}

	// Alarm Error
	else
		std::cerr << "Cannot load sound files!\n";
}

/******************************************************************************/
/*!
\brief - Count how many sounds to be loaded.
This is to init fmod properly.
\return quantity
*/
/******************************************************************************/
int JsonParser::CheckLoadedSounds(void)
{
	int quantity = 0;
	if (m_data.isMember("Sound"))
	{
		for (auto it = m_data["Sound"].begin();
			it != m_data["Sound"].end(); ++it)
		{
			if ((*it).isMember("key") &&
				(*it)["key"].isString() &&
				(*it).isMember("directory") &&
				(*it)["directory"].isString())
				++quantity;
		}
	}

	return quantity;
}

/******************************************************************************/
/*!
\brief - Init Loaded Data on game stage
\parma OBM
*/
/******************************************************************************/
void JsonParser::InitLoadedData(ObjectManager* OBM)
{
	// Load stage and objects
	LoadStage(OBM);
	LoadObjects(OBM);
}

/******************************************************************************/
/*!
\brief - Init scene info from json file
\parma scene
*/
/******************************************************************************/
void JsonParser::LoadStage(ObjectManager* OBM)
{
	Scene* scene = OBM->GetGameScene();

	// Check if there is proper stage info
	if (m_data["Stage"].isArray())
	{
		// Set backgroud's color
		if ((*m_data["Stage"].begin()).isMember("Background") &&
			(*m_data["Stage"].begin())["Background"].isArray() &&
			(*m_data["Stage"].begin())["Background"].size() == 4 &&
			(*m_data["Stage"].begin())["Background"][0].isNumeric())
			scene->SetColor(vec4(
			(*m_data["Stage"].begin())["Background"][0].asFloat(),
				(*m_data["Stage"].begin())["Background"][1].asFloat(),
				(*m_data["Stage"].begin())["Background"][2].asFloat(),
				(*m_data["Stage"].begin())["Background"][3].asFloat()));

		// Set bgm
		if ((*m_data["Stage"].begin()).isMember("BGM") &&
			(*m_data["Stage"].begin())["BGM"].isString())
		{
			OBM->GetGameSound()->AddAudio(
				"BGM", (*m_data["Stage"].begin())["BGM"].asCString());
			OBM->GetGameSound()->GetAudio("BGM")->SetVolume(.1f);
		}

		// Set camera's position
		if ((*m_data["Stage"].begin()).isMember("Camera") &&
			(*m_data["Stage"].begin())["Camera"].isArray() &&
			(*m_data["Stage"].begin())["Camera"].size() == 4 &&
			(*m_data["Stage"].begin())["Camera"][0].isNumeric())
		{
			scene->SetCameraPos(vec3(
				(*m_data["Stage"].begin())["Camera"][0].asFloat(),
				(*m_data["Stage"].begin())["Camera"][1].asFloat(),
				(*m_data["Stage"].begin())["Camera"][2].asFloat()));

			scene->RotateCamera((*m_data["Stage"].begin())["Camera"][3].asFloat());
		}
	}
}

/******************************************************************************/
/*!
\brief - Init component info from json file
\parma it - iterator from json value
\param sprite - pointer to object to set
*/
/******************************************************************************/
Object* JsonParser::SetObject(Json::Value::iterator & it, Object* Obj)
{
	// Set obj's components
	if ((*it).isMember("Component"))
		LoadComponents(it, Obj);

	// Set obj's logics
	if ((*it).isMember("Logic"))
		LoadLogics(it, Obj);

	// Set obj's dt offset
	if ((*it).isMember("dt"))
		Obj->SetdtOffset((*it)["dt"].asFloat());

	return Obj;
}

/******************************************************************************/
/*!
\brief - Init object info from json file
\parma OBM
*/
/******************************************************************************/
void JsonParser::LoadObjects(ObjectManager* OBM)
{
	// Check if there is proper object info
	if (m_data["Object"].isArray())
	{
		// Loop for all objects in the stage
		for (auto it = m_data["Object"].begin();
			it != m_data["Object"].end();
			++it)
		{
			// Check type and id
			if ((*it).isMember("ArcheType") &&
				(*it)["ArcheType"].isString())
			{
				// Get archetype
				ArcheType at = ArcheTypeConverter(
					(*it)["ArcheType"].asCString());

				// If there is pre-loaded archetype,
				// then put this as a parameter
				if (OBM->HasArcheType(at)) {
					OBM->AddObject(
						SetObject(it, OBM->GetArhceType(at)));
				}

				// Unless, make new onject
				else
					OBM->AddObject(
						SetObject(it, new Object(
							at, OBM)));
			}
		}
	}
}

/******************************************************************************/
/*!
\brief - Init component info from json file
\parma it - iterator from json value
\param sprite - pointer to object to set
*/
/******************************************************************************/
void JsonParser::LoadComponents(Json::Value::iterator& it, Object* Obj)
{
	// Get component iterator
	for (auto component = (*it)["Component"].begin();
		component != (*it)["Component"].end(); ++component)
	{
		// Check specific component type
		if ((*component).isMember("key"))
		{
			// Get component type
			ComponentType type = ComponentTypeConverter((*component)["key"].asCString());

			// Make new component
			Obj->AddComponent(ComponentFactory::CreateComponent(Obj, type));

			// Check if there is value
			if ((*component).isMember("values"))
			{
				switch (type)
				{
				case CT_TRANSFORM:
					LoadTransform((*component)["values"], Obj);
					break;
				case CT_RIGIDBODY:
					LoadRigidBody((*component)["values"], Obj);
					break;
				case CT_SPRITE:
					LoadSprite((*component)["values"], Obj);
					break;
				case CT_TEXT:
					LoadText((*component)["values"], Obj);
					break;
				case CT_PARTICLE:
					LoadParticle((*component)["values"], Obj);
					break;
				default:
					std::cerr << "Error: Cannot make new component" << (*component)["key"].asString() << std::endl;
					break;
				}
			}
		}
	}
}

/******************************************************************************/
/*!
\brief - Init logic to object
\parma it - iterator from json value
\param Object - pointer to Object to set
*/
/******************************************************************************/
void JsonParser::LoadLogics(Json::Value::iterator& it, Object* object)
{
	for (auto logic = (*it)["Logic"].begin();
		logic != (*it)["Logic"].end(); ++logic)
	{
		if ((*logic).isMember("key"))
		{
			GameLogic* newLogic = LogicFactory::CreateLogic(
				object, LogicTypeConverter((*logic)["key"].asCString()));

			if (newLogic)
			{
				if ((*logic).isMember("values"))
				{
					newLogic->Load((*logic)["values"]);
					object->AddLogic(newLogic);
				}
			}
			else std::cerr << "Error: Cannot make new logic" << (*logic)["key"].asString() << std::endl;
		}
	}
}

/******************************************************************************/
/*!
\brief - Init object's transform info from json file
\parma it - iterator from json value
\param Obj - pointer to object to set
*/
/******************************************************************************/
void JsonParser::LoadTransform(Json::Value& it, Object * Obj)
{
	// Get pointer to transform
	Transform* transform = Obj->GetComponent<Transform>(CT_TRANSFORM);

	// Set position
	if (it.isMember("Position") &&
		it["Position"].isArray() &&
		it["Position"].size() == 3 &&
		it["Position"][0].isNumeric())
	{
		transform->SetPosition(vec3(
			it["Position"][0].asFloat(),
			it["Position"][1].asFloat(),
			it["Position"][2].asFloat()));
	}

	// Set scale
	if (it.isMember("Scale") &&
		it["Scale"].isArray() &&
		it["Scale"].size() == 3 &&
		it["Scale"][0].isNumeric())
	{
		transform->SetScale(vec3(
			it["Scale"][0].asFloat(),
			it["Scale"][1].asFloat(),
			it["Scale"][2].asFloat()));
	}

	// Set rotation
	if (it.isMember("Rotation") &&
		it["Rotation"].isNumeric())
		transform->SetRotation(it["Rotation"].asFloat());
}

/******************************************************************************/
/*!
\brief - Init rigid body info from json file
\parma it - iterator from json value
\param Obj - pointer to object to set
*/
/******************************************************************************/
void JsonParser::LoadRigidBody(Json::Value& it, Object * Obj)
{
	// Get pointer to rigid body
	RigidBody* body = Obj->GetComponent<RigidBody>(CT_RIGIDBODY);

	//! Body collider toggle
	if (it.isMember("Collider") &&
		it["Collider"].isBool())
		body->ActivateCollider(it["Collider"].asBool());

	//! Body move toggle
	if (it.isMember("Move") &&
		it["Move"].isBool())
		body->ActivateMove(it["Move"].asBool());

	//! Body response toggle
	if (it.isMember("Response") &&
		it["Response"].isBool())
		body->ActivateResponse(it["Response"].asBool());

	//! Body accel
	if (it.isMember("Acce") &&
		it["Acce"].isNumeric())
		body->SetAcceleration(it["Acce"].asFloat());

	//! Body scale
	if (it.isMember("BodyScale") &&
		it["BodyScale"].isArray() &&
		it["BodyScale"].size() == 3 &&
		it["BodyScale"][0].isNumeric())
		body->SetScale(vec3(
			it["BodyScale"][0].asFloat(),
				it["BodyScale"][1].asFloat(),
				it["BodyScale"][2].asFloat()));

	//! Body mass
	if (it.isMember("Mass") &&
		it["Mass"].isNumeric())
		body->SetMass(it["Mass"].asFloat());

	//! Body Friction
	if (it.isMember("Friction") &&
		it["Friction"].isNumeric())
		body->SetFriction(it["Friction"].asFloat());

	//! Body speed
	if (it.isMember("Speed") &&
		it["Speed"].isNumeric())
		body->SetSpeed(it["Speed"].asFloat());

	//! Body direction vector
	if (it.isMember("DirectionVector") &&
		it["DirectionVector"].isArray() &&
		it["DirectionVector"].size() == 3 &&
		it["DirectionVector"][0].isNumeric())
		body->SetDirectionVector(vec3(
			it["DirectionVector"][0].asFloat(),
				it["DirectionVector"][1].asFloat(),
				it["DirectionVector"][2].asFloat()));

	//! Body shape	
	if (it.isMember("Shape") &&
		it["Shape"].isString())
	{
		if (!strcmp("BALL", it["Shape"].asCString()))
			body->SetShape(Shape::BALL);

		else if (!strcmp("BOX", it["Shape"].asCString()))
			body->SetShape(Shape::BOX);
	}
}

/******************************************************************************/
/*!
\brief - Init sprite info from json file
\parma it - iterator from json value
\param Obj - pointer to object to set
*/
/******************************************************************************/
void JsonParser::LoadSprite(Json::Value & it, Object * Obj)
{
	// Get pointer to sprite
	Sprite* sprite = Obj->GetComponent<Sprite>(CT_SPRITE);

	if (it.isMember("Texture") &&
		it["Texture"].isString())
		sprite->SetTexture(Obj->GetOBM()->GetTexture(it["Texture"].asCString()));

	if (it.isMember("Color") &&
		it["Color"].isArray() &&
		it["Color"].size() == 4 &&
		it["Color"][0].isNumeric())
	{
		sprite->SetColor(vec4(
			it["Color"][0].asFloat(),
			it["Color"][1].asFloat(),
			it["Color"][2].asFloat(),
			it["Color"][3].asFloat()));
	}

	//! Set Animation
	if (it.isMember("AniToggle") &&
		it["AniToggle"].isBool())
	{
		sprite->SetAnimation(
			it["AniToggle"].asBool());
	}

	// Set animation frames
	if (it.isMember("AniFrame") &&
		it["AniFrame"].isNumeric())
		sprite->SetFrame(it["AniFrame"].asInt());

	// Set animation speed
	if (it.isMember("AniSpeed") &&
		it["AniSpeed"].isNumeric())
		sprite->SetFrameSpd(it["AniSpeed"].asFloat());

	// Set animation flip toggle
	if (it.isMember("Flip") &&
		it["Flip"].isBool())
	{
		if (it["Flip"].asBool())
			sprite->SetFlip(-1);

		else
			sprite->SetFlip(1);
	}
}

/******************************************************************************/
/*!
\brief - Init text info from json file
\parma it - iterator from json value
\param Obj - pointer to object to set
*/
/******************************************************************************/
void JsonParser::LoadText(Json::Value& it, Object * Obj)
{
	// Get pointer to sprite
	Text* text = Obj->GetComponent<Text>(CT_TEXT);

	// Set text contents
	if (it.isMember("Text") &&
		it["Text"].isString())
		text->SetText(it["Text"].asCString());

	// Set text color
	if (it.isMember("Color") &&
		it["Color"].isArray() &&
		it["Color"].size() == 4 &&
		it["Color"][0].isNumeric())
	{
		text->SetColor(vec4(
			it["Color"][0].asFloat(),
			it["Color"][1].asFloat(),
			it["Color"][2].asFloat(),
			it["Color"][3].asFloat()));
	}

    if (it.isMember("Fontsize") &&
        it["Fontsize"].isNumeric())
        text->SetFontSize(it["Fontsize"].asInt());
    else
        text->SetFontSize(20);
}

/******************************************************************************/
/*!
\brief - Init particle info from json file
\parma it - iterator from json value
\param Obj - pointer to object to set
*/
/******************************************************************************/
void JsonParser::LoadParticle(Json::Value& it, Object* Obj)
{
	// Get pointer to sprite
	Particle* particle = Obj->GetComponent<Particle>(CT_PARTICLE);

	if (it.isMember("Texture") &&
		it["Texture"].isString())
		particle->SetTexture(Obj->GetOBM()->GetTexture(it["Texture"].asCString()));

	// ELSE Todo ..?
}

/******************************************************************************/
/*!
\brief - Load archetype from json file
\parma OBM 
\param at_type - archetype to load
*/
/******************************************************************************/
Object* JsonParser::LoadArcheType(ObjectManager* OBM, ArcheType at_type)
{
	if (m_data.isMember("ArcheType")) {
		for (auto it = m_data["ArcheType"].begin();	
			it != m_data["ArcheType"].end(); )
		{
			// Set new object
			Object* new_Object = new Object(at_type, OBM);

			// Add this to OBM
			return SetObject(it, new_Object);
		}
	}

	return nullptr;
}

void JsonParser::write_sample(void)
{
	Json::Value root;
	root["id"] = "Luna";
	root["name"] = "Silver";
	root["age"] = 19;
	root["hasCar"] = false;

	Json::Value items;
	items.append("nootbook");
	items.append("ipadmini2");
	items.append("iphone5s");
	root["items"] = items;

	Json::Value friends;
	Json::Value tom;
	tom["name"] = "Tom";
	tom["age"] = 21;
	Json::Value jane;
	jane["name"] = "jane";
	jane["age"] = 23;
	friends.append(tom);
	friends.append(jane);
	root["friends"] = friends;

	Json::StyledWriter writer;
	str = writer.write(root);
	std::cout << str << std::endl << std::endl;

	// This will remove usless new line '\n'
	Save("Resource/Data/Sample2.something", root);
}