/******************************************************************************/
/*!
\file   CutScene.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/06/11(yy/mm/dd)

\description
Contains CutScene logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _CUTSCENE_H_
#define _CUTSCENE_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class CutSceneBuilder : public LogicBuilder
{

public:
	CutSceneBuilder() {};
	virtual ~CutSceneBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

class Audio;
class CutScene : public GameLogic
{
public:

	CutScene(Object* Owner, LogicType key);
	virtual ~CutScene(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

	vec4 m_color;
	bool toggle;
	int m_order;

};

#endif // _CUTSCENE_H_
