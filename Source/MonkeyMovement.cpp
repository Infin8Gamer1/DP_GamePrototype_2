//------------------------------------------------------------------------------
//
// File Name:	MonkeyMovement.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "MonkeyMovement.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "Animation.h"
#include "Collider.h"
#include <Graphics.h>
#include <Input.h>

Behaviors::MonkeyMovement::MonkeyMovement() : Component("MonkeyMovement")
{
	// Components
	transform = nullptr;
	physics = nullptr;
	animation = nullptr;
}

Component * Behaviors::MonkeyMovement::Clone() const
{
	return new MonkeyMovement();
}

void Behaviors::MonkeyMapCollisionHandler(GameObject & object, const MapCollision& collision)
{
	if (collision.bottom) {
		static_cast<MonkeyMovement*>(object.GetComponent("MonkeyMovement"))->onGround = true;
	}
	else if (collision.left) {
		static_cast<MonkeyMovement*>(object.GetComponent("MonkeyMovement"))->onWallLeft = true;
	}
	else if (collision.right) {
		static_cast<MonkeyMovement*>(object.GetComponent("MonkeyMovement"))->onWallRight = true;
	}
}

void Behaviors::MonkeyCollisionHandler(GameObject & object, GameObject & other)
{
	if (other.GetName() == "Collectable") {
		other.Destroy();
		static_cast<MonkeyMovement*>(object.GetComponent("MonkeyMovement"))->CoinsCollected += 1;
	}

	if (other.GetName() == "Hazard" || other.GetName() == "Enemy") {
		static_cast<MonkeyMovement*>(object.GetComponent("MonkeyMovement"))->Health -= 1;
	}
}

void Behaviors::MonkeyMovement::Initialize()
{
	onGround = false;
	CoinsCollected = 0;
	Health = 1;

	//get Components
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
	animation = static_cast<Animation*>(GetOwner()->GetComponent("Animation"));
	//set the collision handler for the monkey
	static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetMapCollisionHandler(MonkeyMapCollisionHandler);
	static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(MonkeyCollisionHandler);
}

void Behaviors::MonkeyMovement::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	//call movement code
	MoveVertical();
	MoveHorizontal();

	//do animations
	if (onGround) {
		if (animation->IsDone()) {
			if (physics->GetVelocity().x >= 0) {
				animation->Play(0, 8, 0.1f, false);
			}
			if (physics->GetVelocity().x < 0) {
				animation->Play(7, 8, 0.1f, false, true);
			}

		}
	} else {
		animation->Play(9, 1, 0.05f, false);
	}
}

int Behaviors::MonkeyMovement::GetCoinsCollected()
{
	return CoinsCollected;
}

int Behaviors::MonkeyMovement::GetHealth()
{
	return Health;
}

void Behaviors::MonkeyMovement::MoveHorizontal() const
{
	//left
	if (Input::GetInstance().IsKeyDown('A')) {
		physics->AddForce(Vector2D(-1, 0) * strafeForce);
	}
	//right
	if (Input::GetInstance().IsKeyDown('D')) {
		physics->AddForce(Vector2D(1, 0) * strafeForce);
	}
}

void Behaviors::MonkeyMovement::MoveVertical()
{
	//jump
	if (Input::GetInstance().CheckReleased(' ') && onGround) {
		physics->SetVelocity(Vector2D(physics->GetVelocity().x, jumpForce));
		onGround = false;
		//onWallLeft = false;
		//onWallRight = false;
	}

	if (Input::GetInstance().CheckReleased(' ') && onWallLeft && !onGround && !onWallRight && WallJump) {
		physics->SetVelocity(Vector2D(physics->GetVelocity().x + jumpForce / 2, jumpForce/2));
		//onGround = false;
		onWallLeft = false;
		//onWallRight = false;
	} 
	
	if (Input::GetInstance().CheckReleased(' ') && onWallRight && !onGround && !onWallLeft && WallJump) {
		physics->SetVelocity(Vector2D(physics->GetVelocity().x - jumpForce / 2, jumpForce/2));
		//onGround = false;
		onWallLeft = false;
		//onWallRight = false;
	}

	if (physics->GetVelocity().y < 0) {
		onGround = false;
	}
	if (physics->GetVelocity().x < 0) {
		onWallLeft = false;
	}
	if (physics->GetVelocity().x > 0) {
		onWallRight = false;
	}
}


