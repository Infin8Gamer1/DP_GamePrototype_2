//------------------------------------------------------------------------------
//
// File Name:	Enemy.cpp
// Author(s):	David Cohen	
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Enemy.h"

// Systems
#include <GameObject.h>
#include <Space.h>
#include <GameObjectManager.h>
#include <vector>

// Components
#include <Transform.h>
#include "PatrolAI.h"
#include "AStarPath.h"
#include <Collider.h>

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Collision handler for Enemy objects.
	// Params:
	//   object = The first object.
	//   other  = The other object the first object is colliding with.
	void EnemyCollisionHandler(GameObject& object, GameObject& other)
	{
		// Turret projectile collision handler.
		if (other.GetName() == "TurretProjectile")
		{
			Enemy* enemy = static_cast<Enemy*>(object.GetComponent("Enemy"));

			// Decrement the enemy's health and destroy the enemy if it has 0 health remaining.
			if (--enemy->health <= 0)
				object.Destroy();

			other.Destroy();
		}
	}

	// Constructor
	// Params:
	//   projectileDelay = How long the turret should wait between firing.
	Enemy::Enemy(int health) : Component("Enemy"), transform(nullptr), patrolAI(nullptr), aStarPath(nullptr), health(health)
	{
	}

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* Enemy::Clone() const
	{
		return new Enemy(*this);
	}

	// Initialize data for this object.
	void Enemy::Initialize()
	{
		transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
		patrolAI = static_cast<PatrolAI*>(GetOwner()->GetComponent("PatrolAI"));
		patrolAI->SetLoopMode(PatrolAI::LoopMode::STOP);
		aStarPath = static_cast<AStarPath*>(GetOwner()->GetComponent("AStarPath"));

		Collider* collider = static_cast<Collider*>(GetOwner()->GetComponent("Collider"));
		collider->SetCollisionHandler(EnemyCollisionHandler);
	}

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void Enemy::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		if (!patrolAI->GetMoving())
		{
			patrolAI->SetActive(false);
			//aStarPath->SetActive(true);
		}
	}

	// Gets the enemy's current health.
	int Enemy::GetHealth()
	{
		return health;
	}

	// Sets the enemy's current health.
	void Enemy::SetHealth(int health_)
	{
		health = health_;
	}
};
