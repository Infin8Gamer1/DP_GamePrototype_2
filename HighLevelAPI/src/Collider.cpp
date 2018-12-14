//------------------------------------------------------------------------------
//
// File Name:	Collider.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Collider.h"
#include "Transform.h"
#include "Physics.h"
#include "GameObject.h"

Collider::Collider(ColliderType _type) : Component("Collider")
{
	type = _type;
	handler = nullptr;
	mapHandler = nullptr;
}

void Collider::Initialize()
{
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
}

void Collider::CheckCollision(const Collider & other)
{
	if (IsCollidingWith(other)) {
		if (this->handler != nullptr) {
			this->handler(*this->GetOwner(), *other.GetOwner());
		}
		if (other.handler != nullptr) {
			other.handler(*other.GetOwner(), *this->GetOwner());
		}
	}
}

ColliderType Collider::GetType() const
{
	return type;
}

void Collider::SetCollisionHandler(CollisionEventHandler _handler)
{
	handler = _handler;
}

void Collider::SetMapCollisionHandler(MapCollisionEventHandler _mapHandler)
{
	mapHandler = _mapHandler;
}

MapCollisionEventHandler Collider::GetMapCollisionHandler() const
{
	return mapHandler;
}

MapCollision::MapCollision(bool _bottom, bool _top, bool _left, bool _right)
{
	bottom = _bottom;
	top = _top;
	left = _left;
	right = _right;
}
