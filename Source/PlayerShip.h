//------------------------------------------------------------------------------
//
// File Name:	PlayerShip.h
// Author(s):	Jeremy Kings (j.kings)
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

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class Physics;

namespace FMOD { namespace Studio { class EventInstance; } }

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{

	class PlayerShip : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		// Params:
		//   forwardThrust = Amount of force added to the ship when thrusters are activated.
		//   maximumSpeed  = Maximum attainable speed of the ship.
		//   rotationSpeed = Speed at which the ship rotates.
		//   bulletSpeed   = Speed at which bullets move when fired by ship.
		PlayerShip(float forwardThrust = 100.0f, float maximumSpeed = 100.0f, 
			float rotationSpeed = (float)M_PI, float bulletSpeed = 200.0f);

		// Clone a component and return a pointer to the cloned component.
		// Returns:
		//   A pointer to a dynamically allocated clone of the component.
		Component* Clone() const override;

		// Initialize this component (happens at object creation).
		void Initialize() override;

		// Update function for this component.
		// Params:
		//   dt = The (fixed) change in time since the last step.
		void Update(float dt) override;

	private:
		//------------------------------------------------------------------------------
		// Private Functions:
		//------------------------------------------------------------------------------

		// Move forward when up arrow is pressed
		void Move() const;

		// Rotate when left or right arrow key is pressed
		void Rotate() const;

		// Shoot projectiles when space is pressed
		void Shoot() const;

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Properties (save to/load from file)
		float forwardThrust;
		float maximumSpeed;
		float rotationSpeed;
		float bulletSpeed;

		// Bullet archetype
		GameObject* bulletArchetype;

		// Components
		Transform* transform;
		Physics* physics;

		// Other
		FMOD::Studio::EventInstance* soundEvent;
	};
}

//------------------------------------------------------------------------------
