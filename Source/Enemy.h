//------------------------------------------------------------------------------
//
// File Name:	Enemy.h
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
typedef class Tilemap Tilemap;
typedef class ColliderTilemap ColliderTilemap;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{
	typedef class PatrolAI PatrolAI;
	

	enum EnemyMode
	{
		PathFollow,
		AStar,
		Attack
	};

	class Enemy : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		// Params:
		//   health = How much health the enemy should have.
		Enemy(int health);

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
		friend void EnemyCollisionHandler(GameObject& object, GameObject& other);

	private:

		void AStarToClosestCity();

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Components
		Transform* transform;
		const Tilemap* dataMap;
		PatrolAI* patrolAI;
		ColliderTilemap* ct;

		EnemyMode mode;

		int health;
	};
}

//------------------------------------------------------------------------------
