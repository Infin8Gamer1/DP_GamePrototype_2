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
typedef class Physics Physics;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{

	class BulletMovement : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Default constructor
		BulletMovement();

		// Non-default constructor
		// Params:
		//   timeUntilDeath = Amount of time until the object self-destructs.
		BulletMovement(Vector2D Direction, float Speed);

		// Clone a component and return a pointer to the cloned component.
		// Returns:
		//   A pointer to a dynamically allocated clone of the component.
		Component* Clone() const override;

		// Update function for this component.
		// Params:
		//   dt = The (fixed) change in time since the last step.
		void Update(float dt) override;

		void SetSpeed(float Speed);

		void SetDirection(Vector2D Direction);

	private:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Amount of time until the object self-destructs.
		//float timeUntilDeath;
		Vector2D forceDirection;
		float speed;

		// Number of objects with this component in existence
		static unsigned instanceCount;
	};
}

//------------------------------------------------------------------------------
