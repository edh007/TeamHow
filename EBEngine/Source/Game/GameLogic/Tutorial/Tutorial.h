/******************************************************************************/
/*!
\file   Tutorial.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/03/06(yy/mm/dd)

\description
Contains Tutorial logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"
#include <vector>

class TutorialBuilder : public LogicBuilder
{

public:
	TutorialBuilder() {};
	virtual ~TutorialBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

enum Situation {
	S_WASD, S_KEYQ, S_SPACE, S_LEFT, S_END
};

struct Messages {
	vec3 m_pos;
	std::string m_texts;
	bool imageToggle;
	std::string textureName;
	bool seenOnceToggle;
};

class Sprite;
class Transform;
class Text;

class Tutorial : public GameLogic
{
public:

	Tutorial(Object* Owner, LogicType key);
	virtual ~Tutorial(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	
private:
    int menu_id;
    std::vector<Object*> menuList;
	
	Object* m_Object;
	//Sprite* m_Sprite;
	Transform* m_Trs;
    Text* m_Text;

	Object* m_Image;
	Sprite* m_ImageSprite;
	Transform* m_ImageTrs;

	Object* m_ObjectLT;
	Transform* m_TrsLT;
	Text* m_TextLT;

	Object* m_ImageArrow;
	Sprite* m_ImageArSprite;
	Transform* m_ImageArTrs;

    Object* m_Skip;
    Transform* m_SkipTrs;
    Text* m_SkipText;

	std::vector<Messages*> messageList;

	float dtStack;
	float dtArrow;
	bool arrow;
	bool sprPunch;
	bool seenOnce;
};

#endif // _TUTORIAL_H_
