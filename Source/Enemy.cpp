//------------------------------------------------------------------------------
//
// File Name:	Enemy.cpp
// Author(s):	David Cohen	
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Enemy.h"

// Systems
#include <GameObject.h>
#include <Space.h>
#include <GameObjectManager.h>
#include <vector>

// Components
#include <Transform.h>
#include "PatrolAI.h"
//#include "AStarPath.h"

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	// Params:
	//   projectileDelay = How long the turret should wait between firing.
	Enemy::Enemy() : Component("TurretAI"), transform(nullptr), patrolAI(nullptr), aStarPath(nullptr)
	{
	}

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* Enemy::Clone() const
	{
		return new Enemy(*this);
	}

	// Initialize data for this object.
	void Enemy::Initialize()
	{
		transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
		patrolAI = static_cast<PatrolAI*>(GetOwner()->GetComponent("PatrolAI"));
		patrolAI->SetLoopMode(PatrolAI::LoopMode::STOP);
		//aStarPath = static_cast<AStarPath*>(GetOwner()->GetComponent("AStarPath"));
	}

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void Enemy::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		if (!patrolAI->GetMoving())
		{
			patrolAI->SetActive(false);
			//aStarPath->SetActive(true);
		}
	}
};
