//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ColliderCircle.h"
#include "ColliderPoint.h"
#include "ColliderRectangle.h"
#include "GameObject.h"
#include "Transform.h"
#include "Intersection2D.h"
#include <DebugDraw.h>
#include <Graphics.h>


ColliderCircle::ColliderCircle(float _radius) : Collider(ColliderType::ColliderTypeCircle)
{
	radius = _radius;
}

Component * ColliderCircle::Clone() const
{
	return new ColliderCircle(*this);
}

void ColliderCircle::Draw()
{
	DebugDraw::GetInstance().AddCircle(transform->GetTranslation(), radius, Graphics::GetInstance().GetCurrentCamera(), Color(0,1,0,1));
}

float ColliderCircle::GetRadius() const
{
	return radius;
}

void ColliderCircle::SetRadius(float _radius)
{
	radius = _radius;
}

bool ColliderCircle::IsCollidingWith(const Collider & other) const
{
	//if the other collider is a point they just didn't collide (they missed just barely)
	if (other.GetType() == ColliderType::ColliderTypePoint) {
		Transform* pointTransform = static_cast<Transform*>(other.GetOwner()->GetComponent("Transform"));
		return PointCircleIntersection(pointTransform->GetTranslation(), Circle(transform->GetTranslation(), radius));
	}

	//if the other collider is a rectangle then test if they collided
	if (other.GetType() == ColliderType::ColliderTypeRectangle) {
		const ColliderRectangle& rect = static_cast<const ColliderRectangle&>(other);
		Transform* rectTransform = static_cast<Transform*>(other.GetOwner()->GetComponent("Transform"));
		return RectangleCircleIntersection(BoundingRectangle(rectTransform->GetTranslation(), rect.GetExtents()), Circle(transform->GetTranslation(), radius));
	}

	//if the other collider is circle then check if they collided
	if (other.GetType() == ColliderType::ColliderTypeCircle) {
		const ColliderCircle& circ = static_cast<const ColliderCircle&>(other);
		Transform* circTransform = static_cast<Transform*>(other.GetOwner()->GetComponent("Transform"));
		return CircleCircleIntersection(Circle(transform->GetTranslation(), radius), Circle(circTransform->GetTranslation(), circ.GetRadius()));
	}

	//other wise they didn't collide
	return false;
}
