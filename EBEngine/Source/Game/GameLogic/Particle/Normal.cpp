/******************************************************************************/
/*!
\file   Normal.cpp
\author Dongho Lee
\par    email: edongho007@gmail.com
\date   2016/11/26(yy/mm/dd)

\description
Contains Normal logic class, builder class, and bodies of member functions.

All content (C) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Normal.h"
#include "../../../BaseData/BaseEnigne.h"

/******************************************************************************/
/*!
\brief - NormalBuilder constructor
\param Owner - Owner of this logic
\param key - LogicType
\return new_logic
*/
/******************************************************************************/
GameLogic* NormalBuilder::BuildLogic( Object* Owner, LogicType key) const
{
	return new Normal(Owner, key);
}

/******************************************************************************/
/*!
\brief - Normal constructor
\param Owner - Owner of this logic
\param key - LogicType
*/
/******************************************************************************/
Normal::Normal(Object* Owner, LogicType key)
: GameLogic(Owner, key)
{}

/******************************************************************************/
/*!
\brief - Load Normal info
\param data - json parser
*/
/******************************************************************************/
void Normal::Load(const Json::Value& data)
{
	Particle* particle = m_Owner->GetComponent<Particle>(CT_PARTICLE);

    //Particle Variable
    if (data.isMember("AngleInit") &&
        data["AngleInit"].isInt())
       particle->AngleInit = data["AngleInit"].asInt();
    if (data.isMember("AngleVariable") &&
        data["AngleVariable"].isInt())
       particle->AngleVariable = data["AngleVariable"].asInt();
    if (data.isMember("SpeedInitValue") &&
        data["SpeedInitValue"].isInt())
       particle->SpeedInitValue = data["SpeedInitValue"].asInt();
    if (data.isMember("SpeedVariable") &&
        data["SpeedVariable"].isInt())
       particle->SpeedVariable = data["SpeedVariable"].asInt();
    if (data.isMember("EmissionRate") &&
        data["EmissionRate"].isInt())
       particle->EmissionRate = data["EmissionRate"].asInt();

    if (data.isMember("ScaleX") &&
        data["ScaleX"].isNumeric())
       particle->ScaleValue.x = data["ScaleX"].asFloat();
    if (data.isMember("ScaleY") &&
        data["ScaleY"].isNumeric())
       particle->ScaleValue.y = data["ScaleY"].asFloat();
    if (data.isMember("EndScaleX") &&
        data["EndScaleX"].isNumeric())
       particle->EndScale.x = data["EndScaleX"].asFloat();
    if (data.isMember("EndScaleY") &&
        data["EndScaleY"].isNumeric())
       particle->EndScale.y = data["EndScaleY"].asFloat();

    if (data.isMember("EmitAreaX") &&
        data["EmitAreaX"].isNumeric())
       particle->EmitArea.x = data["EmitAreaX"].asFloat();
    if (data.isMember("EmitAreaY") &&
        data["EmitAreaY"].isNumeric())
       particle->EmitArea.y = data["EmitAreaY"].asFloat();

    if (data.isMember("LifeInit") &&
        data["LifeInit"].isNumeric())
       particle->LifeInit = data["LifeInit"].asFloat();
    if (data.isMember("LifeVariable") &&
        data["LifeVariable"].isNumeric())
       particle->LifeVariable = data["LifeVariable"].asFloat();

    if (data.isMember("ColorInitRed") &&
        data["ColorInitRed"].isNumeric())
       particle->ColorInit.x = data["ColorInitRed"].asFloat();
    if (data.isMember("ColorInitGreen") &&
        data["ColorInitGreen"].isNumeric())
       particle->ColorInit.y = data["ColorInitGreen"].asFloat();
    if (data.isMember("ColorInitBlue") &&
        data["ColorInitBlue"].isNumeric())
       particle->ColorInit.z = data["ColorInitBlue"].asFloat();
    if (data.isMember("ColorInitAlpha") &&
        data["ColorInitAlpha"].isNumeric())
       particle->ColorInit.w = data["ColorInitAlpha"].asFloat();
    if (data.isMember("ColorEndRed") &&
        data["ColorEndRed"].isNumeric())
       particle->ColorEnd.x = data["ColorEndRed"].asFloat();
    if (data.isMember("ColorEndGreen") &&
        data["ColorEndGreen"].isNumeric())
       particle->ColorEnd.y = data["ColorEndGreen"].asFloat();
    if (data.isMember("ColorEndBlue") &&
        data["ColorEndBlue"].isNumeric())
       particle->ColorEnd.z = data["ColorEndBlue"].asFloat();
    if (data.isMember("ColorEndAlpha") &&
        data["ColorEndAlpha"].isNumeric())
       particle->ColorEnd.w = data["ColorEndAlpha"].asFloat();
    if (data.isMember("GravityX") &&
        data["GravityX"].isNumeric())
       particle->Gravity.x = data["GravityX"].asFloat();
    if (data.isMember("GravityY") &&
        data["GravityY"].isNumeric())
       particle->Gravity.y = data["GravityY"].asFloat();
    if (data.isMember("Count") &&
        data["Count"].isInt())
       particle->count = data["Count"].asInt();
    if (data.isMember("Active") &&
        data["Active"].isBool())
       particle->active = data["Active"].asBool();

}

/******************************************************************************/
/*!
\brief - Initialize Normal info
*/
/******************************************************************************/
void Normal::Init(void)
{
	Particle* particle = m_Owner->GetComponent<Particle>(CT_PARTICLE);

   particle->ScaleValue.z = 0;
    m_Owner->GetComponent<Transform>(CT_TRANSFORM)->SetScale(particle->ScaleValue);
   particle->p_position = m_Owner->GetComponent<Transform>(CT_TRANSFORM)->GetPosition();
//   particle->p_type = NORMAL;

    // Create this->EmissionRate default particle instances
    for (GLuint i = 0; i <particle->EmissionRate; ++i)
       particle->particles.push_back(Unit());

}

/******************************************************************************/
/*!
\brief - Update Normal info
\param dt - delta time
*/
/******************************************************************************/
void Normal::Update(float /*dt*/)
{

}

/******************************************************************************/
/*!
\brief - Shutdown Normal info
*/
/******************************************************************************/
void Normal::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Unload Normal info
*/
/******************************************************************************/
void Normal::Unload(void)
{

}
