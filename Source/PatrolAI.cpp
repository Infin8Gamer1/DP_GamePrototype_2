//------------------------------------------------------------------------------
//
// File Name:	PatrolAI.cpp
// Author(s):	David Cohen (david.cohen)
// Project:		Cookie Manor
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "PatrolAI.h"

// Systems
#include <GameObject.h>
#include <Space.h>
#include <GameObjectManager.h>
#include <Input.h>
#include <Parser.h>
#include <Engine.h>
#include <Random.h>
#include <DebugDraw.h>
#include <Graphics.h>
#include "Utils.h"

// Components
#include <Transform.h>
#include <Physics.h>
#include <Collider.h>
#include <Sprite.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	// Params:
	//   speed = How fast the player should move.
	//   deathDuration = Length of death "animation" in seconds.
	PatrolAI::PatrolAI(float speed, bool faceVelocity, PatrolAI::LoopMode loopMode) : Component("PatrolAI"),
		speed(speed), faceVelocity(faceVelocity), loopMode(loopMode), pathSize(0), pathIndex(UINT_MAX), nextPathIndex(0), moving(true), movingForwards(true)
	{
		path = std::vector<Vector2D>();
	}

	// Destructor
	PatrolAI::~PatrolAI()
	{
	}

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* PatrolAI::Clone() const
	{
		return new PatrolAI(*this);
	}

	// Initialize this component (happens at object creation).
	void PatrolAI::Initialize()
	{
		// Store the required components for ease of access.
		transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
		physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
	}

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void PatrolAI::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		// Don't do anything if there is no path
		if (path.size() <= 1)
			return;

		// Only handle movement if the patrol AI is active.
		if (active)
		{
			// Make sure the current path point is up to date.
			UpdatePath();

			// Handle movement.
			Move();
		}

		// Draw the path for debugging purposes.
		DebugDraw& debugDraw = DebugDraw::GetInstance();

		for (unsigned i = 0; i < path.size() - 1; i++)
		{
			debugDraw.AddLineToStrip(path[i], path[i + 1], Colors::White);
		}

		debugDraw.EndLineStrip(Graphics::GetInstance().GetCurrentCamera());
	}

	// Get whether we are moving.
	bool PatrolAI::GetMoving()
	{
		return moving;
	}

	// Sets whether we are moving.
	// Params:
	//   moving = Whether to move or not.
	void PatrolAI::SetMoving(bool moving_)
	{
		moving = moving_;
	}

	// Get the current value of faceVelocity.
	bool PatrolAI::GetFaceVelocity()
	{
		return faceVelocity;
	}

	// Set the current value of faceVelocity.
	// Params:
	//   faceVelocity = The new value of faceVelocity.
	void PatrolAI::SetFaceVelocity(bool faceVelocity_)
	{
		faceVelocity = faceVelocity_;
	}

	// Get the current loop mode.
	PatrolAI::LoopMode PatrolAI::GetLoopMode()
	{
		return loopMode;
	}

	// Set the current loop mode.
	// Params:
	//   loopMode = The new loop mode.
	void PatrolAI::SetLoopMode(PatrolAI::LoopMode loopMode_)
	{
		loopMode = loopMode_;
	}

	// Sets the path.
	// Params:
	//   path = The path to follow.
	void PatrolAI::SetPath(std::vector<Vector2D> path_)
	{
		path = path_;
		pathSize = static_cast<unsigned>(path.size());
	}

	// Clears the path.
	void PatrolAI::ClearPath()
	{
		path.clear();
		pathSize = 0;
	}

	// Adds a point to the path.
	// Params:
	//   point = The point to add.
	void PatrolAI::AddPathPoint(Vector2D point)
	{
		path.push_back(point);
		++pathSize;

		// If we were already at the end of the path, begin moving.
		if (nextPathIndex == pathIndex)
		{
			//EndOfPath();
			if (movingForwards)
			{
				// Continue to the next path point.
				nextPathIndex = pathIndex + 1;
			}
		}
	}

	// Sets whether the patrol AI is currently active.
	// Params:
	//   active = Whether the patrol Ai should be active.
	void PatrolAI::SetActive(bool active_)
	{
		active = active_;
	}

	// Returns whether the patrol AI is currently active.
	bool PatrolAI::IsActive()
	{
		return active;
	}

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Update the current & next path indexes.
	void PatrolAI::UpdatePath()
	{
		Vector2D translation = transform->GetTranslation();

		// Check if we are close to the next path point.
		if (translation.Distance(path[nextPathIndex]) <= 0.5f)
		{
			pathIndex = nextPathIndex;
			
			if (movingForwards)
			{
				// Check if we are at the end of the path.
				if ((nextPathIndex + 1) >= path.size())
				{
					EndOfPath();
				}
				else
				{
					// Continue to the next path point.
					nextPathIndex = pathIndex + 1;
				}
			}
			else
			{
				// Check if we are at the start of the path.
				if (nextPathIndex == 0)
				{
					EndOfPath();
				}
				else
				{
					// Continue to the previous path point.
					nextPathIndex = pathIndex - 1;
				}
			}
		}
	}

	void PatrolAI::EndOfPath()
	{
		if (movingForwards)
		{
			switch (loopMode)
			{
			case LoopMode::LOOP:
				// Move to beginning of path.
				nextPathIndex = 0;
				break;
			case LoopMode::PINGPONG:
				// Switch directions.
				movingForwards = false;
				nextPathIndex = pathIndex - 1;
				break;
			case LoopMode::STOP:
				// Stop moving.
				moving = false;
				break;
			}
		}
		else
		{
			switch (loopMode)
			{
			case LoopMode::LOOP:
				// Move to end of path.
				nextPathIndex = pathSize - 1;
				break;
			case LoopMode::PINGPONG:
				// Switch directions.
				movingForwards = true;
				nextPathIndex = pathIndex + 1;
				break;
			case LoopMode::STOP:
				// Stop moving.
				moving = false;
				break;
			}
		}
	}

	// Move to the next path point.
	void PatrolAI::Move() const
	{
		// Don't attempt to move if there's nowhere to go.
		if (moving && nextPathIndex != pathIndex)
		{
			Vector2D translation = transform->GetTranslation();

			// Calculate the velocity to move towards the next path point.
			Vector2D direction = path[nextPathIndex] - translation;
			Vector2D velocity = direction.Normalized() * speed;

			physics->SetVelocity(velocity);

			// Check if we should face our velocity.
			if (faceVelocity)
			{
				// Linearly interpolate to the next angle.
				float rotation = transform->GetRotation();
				rotation = Utils::LerpRad(rotation, atan2(velocity.y, velocity.x), 0.05f);

				// Keep rotation within -PI to +PI
				while (rotation > M_PI_F)
					rotation -= M_PI_F * 2.0f;
				while (rotation < M_PI_F)
					rotation += M_PI_F * 2.0f;

				transform->SetRotation(rotation);
			}
		}
		else
		{
			physics->SetVelocity(Vector2D(0.0f, 0.0f));
		}
	}
}

//------------------------------------------------------------------------------
