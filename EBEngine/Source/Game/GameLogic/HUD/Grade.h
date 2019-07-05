/******************************************************************************/
/*!
\file   Grade.h
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2017/05/07(yy/mm/dd)

\description
Contains Grade logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _GRADE_H_
#define _GRADE_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

enum GradeText { t_Kill, t_Time, t_Death, s_Kill, s_Time, s_Death, 
	t_Score, t_Report, t_Total, s_Conclusion, t_Instruction, r_Time, r_Kill, r_Death, t_End };

class GradeBuilder : public LogicBuilder
{

public:
	GradeBuilder() {};
	virtual ~GradeBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Sprite;
class Text;
class Transform;
class Audio;

class Grade : public GameLogic
{
public:

	Grade(Object* Owner, LogicType key);
	virtual ~Grade(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:
    Sprite* m_sprite;
    Object* m_object;
    Transform* m_trs;

    Text* m_text[GradeText::t_End];
    Object* m_objectTxt[GradeText::t_End];
    Transform* m_trsTxt[GradeText::t_End];

    Audio* m_sound;
    float soundTime;
    bool soundToggle;

    int gradeKill;
    float gradeTime;
    int gradeDeath;

    float waitTime;
};

#endif // _GRADE_H_
