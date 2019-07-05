/******************************************************************************/
/*!
\file   NodeSettor.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2017/02/06(yy/mm/dd)

\description
Contains NodeSettor logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "NodeSettor.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - NodeSettorBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* NodeSettorBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new NodeSettor(Owner, key);
}

/******************************************************************************/
/*!
\brief - NodeSettor constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
NodeSettor::NodeSettor(Object* Owner, LogicType key)
: GameLogic(Owner, key), m_size(0)
{}

/******************************************************************************/
/*!
\brief - Load NodeSettor info
\param data - json parser
*/
/******************************************************************************/
void NodeSettor::Load(const Json::Value& data)
{
	// Set these info only for this case
	if (data.isMember("Node") &&
		data["Node"].isArray() &&
		data["Node"][0].isArray() &&
		data["Node"][0][0].isArray() &&
		data["Node"][0][1].isArray() &&
		data["Node"][0][0][0].isInt() && 
		data["Node"][0][1][0].isNumeric())
	{
		for (unsigned i = 0; i < data["Node"].size(); ++i)
			m_OBM->GetGameWorld()->AddNode(m_OBM,
				
				Index(data["Node"][i][0][0].asInt(),
				data["Node"][i][0][1].asInt()),

				vec3(data["Node"][i][1][0].asFloat(),
				data["Node"][i][1][1].asFloat()));
	}
}

/******************************************************************************/
/*!
\brief - Initialize NodeSettor info
*/
/******************************************************************************/
void NodeSettor::Init(void)
{
	std::vector<Object*> nodes;
	m_OBM->GetObjects(AT_NODE, nodes);
	for (auto it : nodes)
		it->GetComponent<Sprite>(CT_SPRITE)->SetColor(vec4(1,1,1,0.f));

	m_size = nodes.size();
}

/******************************************************************************/
/*!
\brief - Update NodeSettor info
\param dt - delta time
*/
/******************************************************************************/
void NodeSettor::Update(float /*dt*/)
{

}

/******************************************************************************/
/*!
\brief - Shutdown NodeSettor info
*/
/******************************************************************************/
void NodeSettor::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload NodeSettor info
*/
/******************************************************************************/
void NodeSettor::Unload(void)
{

}

/******************************************************************************/
/*!
\brief - Get Size
\return m_size
*/
/******************************************************************************/
int NodeSettor::GetSize(void) const
{
	return m_size;
}