/******************************************************************************/
/*!
\file   Door.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2016/11/08(yy/mm/dd)

\description
Contains Door logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _DOOR_H_
#define _DOOR_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class DoorBuilder : public LogicBuilder
{

public:
	DoorBuilder() {};
	virtual ~DoorBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Object;
class Sprite;
class Transform;
class Text;

class Door : public GameLogic
{
public:

	Door(Object* Owner, LogicType key);
	virtual ~Door(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);
	bool EndCondition;

private:
	std::vector<Object*> player;
	int player_id;
	std::vector<Object*> talisman;
	int talisman_id;
	bool showingTablet;
	float dtStack;

	Sprite* m_sprite;
	Object* m_object;
	Transform* m_trs;
	std::string saveTexture;

    Object* m_Skip;
    Transform* m_SkipTrs;
    Text* m_SkipText;
};

#endif // _DOOR_H_
