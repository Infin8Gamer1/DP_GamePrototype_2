//------------------------------------------------------------------------------
//
// File Name:	PlayerShip.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "PlayerShip.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "Space.h"
#include "BulletMovement.h"
#include <Graphics.h>
#include <Input.h>
#include "SoundManager.h"
#include <Engine.h>

Behaviors::PlayerShip::PlayerShip(float _forwardThrust, float _maximumSpeed, float _rotationSpeed, float _bulletSpeed) : Component("PlayerShip")
{
	// Movement properties
	forwardThrust = _forwardThrust;
	maximumSpeed = _maximumSpeed;
	rotationSpeed = _rotationSpeed;
	bulletSpeed = _bulletSpeed;

	// Bullet archetype
	bulletArchetype = nullptr;

	// Components
	transform = nullptr;
	physics = nullptr;

	//other
	soundEvent = nullptr;
}

Component * Behaviors::PlayerShip::Clone() const
{
	return new PlayerShip(forwardThrust, maximumSpeed, rotationSpeed, bulletSpeed);
}

void Behaviors::PlayerShip::Initialize()
{
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));

	bulletArchetype = GetOwner()->GetSpace()->GetObjectManager().GetArchetypeByName("Bullet");

	soundEvent = Engine::GetInstance().GetModule<SoundManager>()->PlayEvent("Test Tones");
	soundEvent->setPaused(true);
	soundEvent->setVolume(0.5f);
	soundEvent->setParameterValue("Wave Type", 0);
	soundEvent->setParameterValue("LowMidHigh", 0);
}

void Behaviors::PlayerShip::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	Move();
	Rotate();

	if (Input::GetInstance().CheckReleased(' ')) {
		Shoot();
	}
}

void Behaviors::PlayerShip::Move() const
{
	//const float speed = 15.0f;
	if (Input::GetInstance().IsKeyDown('W')) {
		Vector2D MousePos = Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition());

		Vector2D force = MousePos - transform->GetTranslation();

		force = force.Normalized();

		physics->AddForce(force * forwardThrust);

		soundEvent->setPaused(false);
	} else {
		soundEvent->setPaused(true);
	}

	
}

void Behaviors::PlayerShip::Rotate() const
{
	Vector2D MousePos = Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition());

	transform->LookAt(MousePos);
}

void Behaviors::PlayerShip::Shoot() const
{
	GameObject* newBullet = new GameObject(*bulletArchetype);

	Vector2D MousePos = Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition());

	Vector2D force = MousePos - transform->GetTranslation();

	force = force.Normalized();

	static_cast<BulletMovement*>(newBullet->GetComponent("BulletMovement"))->SetDirection(force);
	static_cast<BulletMovement*>(newBullet->GetComponent("BulletMovement"))->SetSpeed(bulletSpeed);

	static_cast<Transform*>(newBullet->GetComponent("Transform"))->SetTranslation(transform->GetTranslation());
	static_cast<Transform*>(newBullet->GetComponent("Transform"))->SetRotation(transform->GetRotation());

	GetOwner()->GetSpace()->GetObjectManager().AddObject(*newBullet);
}
