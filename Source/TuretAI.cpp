//------------------------------------------------------------------------------
//
// File Name:	TurretAI.cpp
// Author(s):	David Cohen	
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "TurretAI.h"

// Systems
#include <GameObject.h>
#include <Space.h>
#include <GameObjectManager.h>
#include <vector>

// Components
#include <Transform.h>
#include <Physics.h>

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	// Params:
	//   projectileDelay = How long the turret should wait between firing.
	TurretAI::TurretAI(GameObject* projectileArchetype, float radius, float projectileDelay, float projectileSpeed) : Component("TurretAI"), transform(nullptr), projectileArchetype(projectileArchetype), radius(radius), projectileDelay(projectileDelay), projectileSpeed(projectileSpeed), projectileTimer(0.0f)
	{
	}

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* TurretAI::Clone() const
	{
		return new TurretAI(*this);
	}

	// Initialize data for this object.
	void TurretAI::Initialize()
	{
		transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	}

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void TurretAI::Update(float dt)
	{
		projectileTimer = max(0.0f, projectileTimer - dt);

		if (projectileTimer <= 0.0f)
		{
			FindClosestEnemy();
		}
	}

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Finds the closest enemy within the turret's radius and fires at them.
	void TurretAI::FindClosestEnemy()
	{
		// Get all enemies in the level.
		std::vector<GameObject*> enemies = GetOwner()->GetSpace()->GetObjectManager().GetAllObjectsByName("Circle");

		// The current closest enemy distance (defaults to just outside the turret radius).
		float closestDistanceSquared = radius * radius + 1.0f;

		// The current closest enemy position & velocity.
		Vector2D closestEnemyTranslation;
		Vector2D closestEnemyVelocity;
		
		// Iterate through all enemies.
		for (size_t i = 0; i < enemies.size(); i++)
		{
			GameObject* enemy = enemies[i];
			Transform* enemyTransform = static_cast<Transform*>(enemy->GetComponent("Transform"));
			Physics* enemyPhysics = static_cast<Physics*>(enemy->GetComponent("Physics"));
			Vector2D enemyTranslation = enemyTransform->GetTranslation();

			// Calculate the squared distance to the current enemy.
			float distanceSquared = transform->GetTranslation().DistanceSquared(enemyTranslation);

			// If the distance is closer than anything seen previously, update the closest distance and store the enemy's position.
			if (distanceSquared < closestDistanceSquared)
			{
				closestEnemyTranslation = enemyTranslation;
				closestEnemyVelocity = enemyPhysics->GetVelocity();
				closestDistanceSquared = distanceSquared;
			}
		}

		// If the enemy is within the turret's radius, fire at it.
		if (closestDistanceSquared <= radius * radius)
		{
			FireAtPosition(closestEnemyTranslation, closestEnemyVelocity);
			projectileTimer = projectileDelay;
		}
	}

	// Fires a projectile towards the specified position.
	// Params:
	//   position = The position to fire at.
	void TurretAI::FireAtPosition(Vector2D position, Vector2D velocity)
	{
		Vector2D translation = transform->GetTranslation();

		// The following is ripped from this stackoverflow post: https://stackoverflow.com/questions/17204513/how-to-find-the-interception-coordinates-of-a-moving-target-in-3d-space
		// FIXME: this doesn't work lol
		float a = velocity.MagnitudeSquared() - projectileSpeed * projectileSpeed;
		float b = 2 * ((position.x * velocity.x) + (position.y * velocity.y) - (translation.x * velocity.x) - (translation.y * velocity.y));
		float c = position.MagnitudeSquared() + translation.MagnitudeSquared() - (2 * translation.x * position.x) - (2 * translation.y * position.y);

		float t1 = (-b + sqrt((b * b) - (4 * a * c))) / (2 * a);
		float t2 = (-b - sqrt((b * b) - (4 * a * c))) / (2 * a);

		float t = t1;

		if (t <= 0.0f || isnan(t))
			t = t2;
		else if (t2 > 0.0f)
			t = min(t, t2);

		if (t <= 0.0f || isnan(t))
			return;

		// So, somehow we got here, with a velocity which will make the projectile aim at where the enemy will be.
		Vector2D projectileVelocity = (position - translation + (t * projectileSpeed * velocity)) / (t * projectileSpeed);

		// Calculate the direction towards the specified position.
		//Vector2D direction = (position - transform->GetTranslation()).Normalized();

		GameObject* projectile = new GameObject(*projectileArchetype);

		// Copy our translation to the projectile.
		static_cast<Transform*>(projectile->GetComponent("Transform"))->SetTranslation(transform->GetTranslation());

		// Set the projectile's velocity to our calculated value.
		static_cast<Physics*>(projectile->GetComponent("Physics"))->SetVelocity(projectileVelocity);

		// Add the projectile to the scene.
		GetOwner()->GetSpace()->GetObjectManager().AddObject(*projectile);
	}
};
