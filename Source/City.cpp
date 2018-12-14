//------------------------------------------------------------------------------
//
// File Name:	City.cpp
// Author(s):	David Cohen	
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "City.h"

// Systems
#include <GameObject.h>
#include <Space.h>
#include <GameObjectManager.h>
#include <vector>

// Components
#include "HealthBar.h"
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
	void CityCollisionHandler(GameObject& object, GameObject& other)
	{
		// Turret projectile collision handler.
		if (other.GetName() == "Enemy")
		{
			City* city = static_cast<City*>(object.GetComponent("City"));

			// Decrement the city's health and destroy the city if it has 0 health remaining.
			if (--city->health <= 0)
				object.Destroy();

			other.Destroy();
		}
	}

	// Constructor
	// Params:
	//   health = How much health the city should have.
	City::City(int health) : Component("City"), healthBar(nullptr), health(health)
	{
	}

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* City::Clone() const
	{
		return new City(*this);
	}

	// Initialize data for this object.
	void City::Initialize()
	{
		healthBar = static_cast<HealthBar*>(GetOwner()->GetComponent("HealthBar"));

		Collider* collider = static_cast<Collider*>(GetOwner()->GetComponent("Collider"));
		collider->SetCollisionHandler(CityCollisionHandler);
	}

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void City::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		healthBar->SetHealth(health);
	}

	// Gets the enemy's current health.
	int City::GetHealth()
	{
		return health;
	}

	// Sets the enemy's current health.
	void City::SetHealth(int health_)
	{
		health = health_;
	}
};
