/******************************************************************************/
/*!
\file   JsonParser.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/07/30(yy/mm/dd)

\description
Contains JsonParser's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _JSONPARSER_H_
#define _JSONPARSER_H_

#include "json/json.h"
#include "../../../BaseData/ArcheTypes/ArcheType.h"

class Object;
class GLManager;
class SoundManager;
class ObjectManager;

//! Json Parser class
class JsonParser{

public:
	JsonParser();
	~JsonParser();

	//void AddTexture(GLManager* GLM, const char * key, const char * texture_dir);
	//void AddSound(SoundManager* SM, const char * key, const char * SoundDir);

	//! Save and load file containing information
	void Save(const char* dir, const Json::Value& contents);
	void Load(char* dir);

	//! Asset data managing functions
	int  CheckLoadedSounds(void);
	void InitAssetData(GLManager* GLM, SoundManager* SM);
	void InitLoadedData(ObjectManager* OBM);
	const Json::Value& GetLoadedData(void) const;

	Object* LoadArcheType(ObjectManager* OBM, ArcheType at_type);

	// Todo
	// Delete this functions later
	void write_sample(void);

private:

	//! Inner helper functions
	//void LoadEmitter(Json::Value& data, Emitter* particle);
	
	// Stage attributes setting functions
	void LoadStage(ObjectManager* OBM);
	void LoadObjects(ObjectManager* OBM);

	// Object setting functions
	Object* SetObject(Json::Value::iterator& it, Object* Obj);
	void LoadComponents(Json::Value::iterator& it, Object* Obj);
	void LoadLogics(Json::Value::iterator& it, Object* Obj);

	// Component setting functions
	void LoadTransform(Json::Value& it, Object* Obj);
	void LoadRigidBody(Json::Value& it, Object* Obj);
	void LoadSprite(Json::Value& it, Object* Obj);
	void LoadText(Json::Value& it, Object* Obj);
	void LoadParticle(Json::Value& it, Object* Obj);
    void LoadLight(Json::Value& it, Object* Obj);

	std::string str;
	Json::Value m_data;
};

#endif