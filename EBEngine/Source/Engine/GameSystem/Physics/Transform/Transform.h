/******************************************************************************/
/*!
\file   Transform.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/12/20(yy/mm/dd)

\description
Contains Transform component info

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../../../Component/Component.h"
#include "../../../Utilities/Math/MathUtils.h"
#include "../../../Component/ComponentBuilder.h"

//! Tranform builder class
class TransformBuilder : public ComponentBuilder
{
public:
	TransformBuilder() {};
	virtual ~TransformBuilder() {};
	virtual Component* BuildComponent(Object* Owner, ComponentType key) const;

};

//! Transform class
class Transform : public Component
{
public:

	Transform(Object* Owner = 0, ComponentType key = CT_TRANSFORM);
	virtual ~Transform() {};

	void SetPosition(const vec3& position);
	void SetScale(const vec3& scale);

	vec3 GetPosition(void) const;
	vec3 GetScale(void) const;

	void SetRotation(float degree);
	float GetRotation(void) const;

private:

	float m_rotation;
	vec3 m_position;
	vec3 m_scale;

};

#endif // _TRANSFORM_H_