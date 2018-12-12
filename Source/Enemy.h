//------------------------------------------------------------------------------
//
// File Name:	ColorChange.h
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
#include <Color.h>	 // Color

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Sprite;
class Transform;
class Physics;
class Animation;
struct MapCollision;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{
	enum InnerStates
	{
		InnerStateEnter,
		InnerStateUpdate,
		InnerStateExit
	};

	enum EnemyStates
	{
		StateIdle,
		StateWander,
		StateChase
	};

	enum EnemyWanderDirections
	{
		Left,
		Right,
		Jump,
		Last
	};

	class Enemy : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		Enemy();

		// Return a new copy of the component.
		Component* Clone() const;

		// Initialize data for this object.
		void Initialize();

		// Update function for this component.
		// Params:
		//   dt = The (fixed) change in time since the last step.
		void Update(float dt) override;

		// Sets the next state of the enemy.
		// Params:
		//   nextState = The next state the enemy should be in.
		void SetState(EnemyStates nextState);

		// Map collision handler for Monkey objects.
		// Params:
		//   object = The monkey object.
		//   collision = Which sides the monkey collided on.
		friend void EnemyMapCollisionHandler(GameObject& object,
			const MapCollision& collision);

	private:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		EnemyStates currentState;  // The current state of the enemy. Ex: idle, wander, chase
		EnemyStates nextState;		// The next state of the enemy.

		InnerStates innerState; // The inner state of the current state. Ex: enter, update, exit
		
		EnemyWanderDirections wanderDirection; //the direction to wander
		EnemyWanderDirections previousWanderDirection; //the direction to wander

		float timer; // Used for delaying state changes, etc.
		float stateChangeTime; // Amount of time to wait before changing states.

		bool onGround;
		bool onWallLeft;
		bool onWallRight;

		const Color normalColor = Color(1,1,1,1);
		const Color madColor = Color(1,0,0,1);

		// Components
		Transform* transform;
		Physics* physics;
		Animation* animation;
		Sprite* sprite;
	};
}
