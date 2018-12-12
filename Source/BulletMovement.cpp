//------------------------------------------------------------------------------
//
// File Name:	BulletMovement.h
// Author(s):	Jacob Holyfield
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BulletMovement.h"
#include "Physics.h"
#include "GameObject.h"

Behaviors::BulletMovement::BulletMovement() : Component("BulletMovement")
{
	forceDirection = Vector2D(0, 1);
	speed = 20.0;
}

Behaviors::BulletMovement::BulletMovement(Vector2D Direction, float Speed) : Component("BulletMovement")
{
	forceDirection = Direction;
	speed = Speed;
}

Component * Behaviors::BulletMovement::Clone() const
{
	return new BulletMovement(forceDirection, speed);
}

void Behaviors::BulletMovement::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	static_cast<Physics*>(GetOwner()->GetComponent("Physics"))->SetVelocity(forceDirection * speed);
}

void Behaviors::BulletMovement::SetSpeed(float Speed)
{
	speed = Speed;
}

void Behaviors::BulletMovement::SetDirection(Vector2D Direction)
{
	forceDirection = Direction;
}
