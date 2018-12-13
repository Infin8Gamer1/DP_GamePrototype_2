//------------------------------------------------------------------------------
//
// File Name:	TurretAI.h
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

	class TurretAI : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		// Params:
		//   projectileDelay = How long the turret should wait between firing.
		TurretAI(GameObject* projectileArchetype, float radius, float projectileDelay, float projectileSpeed);

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

	private:
		//------------------------------------------------------------------------------
		// Private Functions:
		//------------------------------------------------------------------------------

		// Finds the closest enemy within the turret's radius and fires at them.
		void FindClosestEnemy();

		// Fires a projectile towards the specified position.
		// Params:
		//   position = The position to fire at.
		void FireAtPosition(Vector2D position, Vector2D velocity);

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Components
		Transform* transform;
		
		// The projectile archetype.
		GameObject* projectileArchetype;

		// How far away the turret can see.
		float radius;

		// How long the turret should wait between firing.
		float projectileDelay;

		// How fast projectiles should move.
		float projectileSpeed;

		// The current time to wait before shooting.
		float projectileTimer;
	};
}

//------------------------------------------------------------------------------
