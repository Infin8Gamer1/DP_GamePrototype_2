//------------------------------------------------------------------------------
//
// File Name:	City.h
// Author(s):	David Cohen (david.cohen)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
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
	typedef class HealthBar HealthBar;

	class City : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		// Params:
		//   health = How much health the city should have.
		City(int health);

		// Clone a component and return a pointer to the cloned component.
		// Returns:
		//   A pointer to a dynamically allocated clone of the component.
		Component* Clone() const override;

		// Initialize data for this object.
		void Initialize() override;

		// Update function for this component.
		// Params:
		//   dt = The (fixed) change in time since the last step.
		void Update(float dt) override;

		// Gets the enemy's current health.
		int GetHealth();

		// Sets the enemy's current health.
		void SetHealth(int health);

		// Collision handler for Enemy objects.
		// Params:
		//   object = The first object.
		//   other  = The other object the first object is colliding with.
		friend void CityCollisionHandler(GameObject& object, GameObject& other);

	private:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Components
		HealthBar* healthBar;

		// Miscellaneous variables
		int health;
	};
}

//------------------------------------------------------------------------------
