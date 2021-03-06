//------------------------------------------------------------------------------
//
// File Name:	HealthBar.h
// Author(s):	David Cohen (david.cohen)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h" // base class

#include "Vector2D.h" // Vector2D

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

typedef class Transform Transform;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{
	class HealthBar : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		// Params:
		//   health = How much health the health bar should display.
		HealthBar(int health, int maxHealth, float offset = 0.0f);

		// Clone a component and return a pointer to the cloned component.
		// Returns:
		//   A pointer to a dynamically allocated clone of the component.
		Component* Clone() const override;

		// Initialize data for this object.
		void Initialize() override;

		// Free memory associated with this object.
		void Shutdown() override;

		// Update function for this component.
		// Params:
		//   dt = The (fixed) change in time since the last step.
		void Update(float dt) override;

		// Gets the enemy's current health.
		int GetHealth();

		// Sets the enemy's current health.
		void SetHealth(int health);

		// Gets the health bar's offset.
		float GetOffset();

		// Sets the health bar's offset.
		void SetOffset(float offset);

		// Returns the game object being used as the visual health bar.
		GameObject* GetHealthBarObject();

	private:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// How many frames there are in the health bar spritesheet.
		static const int healthBarFrames = 16;

		// Components
		Transform* transform;

		// Miscellaneous variables
		int health;
		int maxHealth;
		float offset;
		GameObject* healthBar;
	};
}

//------------------------------------------------------------------------------
