/******************************************************************************/
/*!
\file   NodeSettor.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/02/06(yy/mm/dd)

\description
Contains NodeSettor logic class, builder class, and headers of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _NODESETTOR_H_
#define _NODESETTOR_H_

#include "../../../Engine/GameSystem/Logic/LogicBuilder.h"
#include "../../../Engine/Utilities/Math/MathUtils.h"

class NodeSettorBuilder : public LogicBuilder
{

public:
	NodeSettorBuilder() {};
	virtual ~NodeSettorBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const;

};

//! Class node settor
class NodeSettor : public GameLogic
{
public:

	NodeSettor(Object* Owner, LogicType key);
	virtual ~NodeSettor(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
	virtual void Unload(void);

	int GetSize(void) const;

private:

	int m_size;
};

#endif // _NODESETTOR_H_
