//------------------------------------------------------------------------------
//
// File Name:	HealthBar.cpp
// Author(s):	David Cohen	
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "HealthBar.h"

// Systems
#include <GameObject.h>
#include <Space.h>
#include <GameObjectManager.h>

// Components
#include <Sprite.h>

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	// Params:
	//   health = How much health the health bar should display.
	HealthBar::HealthBar(int health, int maxHealth) : Component("HealthBar"), health(health), maxHealth(maxHealth)
	{
	}

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* HealthBar::Clone() const
	{
		return new HealthBar(*this);
	}

	// Initialize data for this object.
	void HealthBar::Initialize()
	{
		//GameObjectManager& objectManager = GetOwner()->GetSpace()->GetObjectManager();
		//healthBar = new GameObject(*objectManager.GetArchetypeByName("HealthBar"));
		//objectManager.AddObject(*healthBar);
	}

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void HealthBar::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		//Sprite* sprite = static_cast<Sprite*>(healthBar->GetComponent("Sprite"));
		//sprite->SetFrame(healthBarFrames - static_cast<int>(static_cast<float>(health) / static_cast<float>(maxHealth) * static_cast<float>(healthBarFrames)));
	}

	// Gets the enemy's current health.
	int HealthBar::GetHealth()
	{
		return health;
	}

	// Sets the enemy's current health.
	void HealthBar::SetHealth(int health_)
	{
		health = health_;
	}

	// Returns the game object being used as the visual health bar.
	GameObject* HealthBar::GetHealthBarObject()
	{
		return healthBar;
	}
};
