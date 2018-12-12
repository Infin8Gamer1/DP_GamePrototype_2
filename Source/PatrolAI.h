//------------------------------------------------------------------------------
//
// File Name:	PatrolAI.h
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

#include "Component.h" // base class
#include <Vector2D.h>
#include <vector>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

typedef class Transform Transform;
typedef class Physics Physics;
typedef struct Event Event;
typedef class Texture Texture;
typedef class Mesh Mesh;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{
	class PatrolAI : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Structures:
		//------------------------------------------------------------------------------

		enum class LoopMode
		{
			LOOP = 0,
			PINGPONG = 1,
			STOP = 2
		};

		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		// Params:
		//   speed = How fast the player should move.
		//   path = Vector of points to traverse.
		PatrolAI(float speed = 100.0f, bool faceVelocity = true, LoopMode loopMode = LoopMode::LOOP);

		// Destructor
		~PatrolAI();

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

		// Get whether we are moving.
		bool GetMoving();

		// Sets whether we are moving.
		// Params:
		//   moving = Whether to move or not.
		void SetMoving(bool moving);

		// Get the current value of faceVelocity.
		bool GetFaceVelocity();

		// Set the current value of faceVelocity.
		// Params:
		//   faceVelocity = The new value of faceVelocity.
		void SetFaceVelocity(bool faceVelocity);

		// Get the current loop mode.
		LoopMode GetLoopMode();

		// Set the current loop mode.
		// Params:
		//   loopMode = The new loop mode.
		void SetLoopMode(LoopMode loopMode);

		// Clears the path.
		void ClearPath();

		// Adds a point to the path.
		void AddPathPoint(Vector2D point);

	private:
		//------------------------------------------------------------------------------
		// Private Functions:
		//------------------------------------------------------------------------------

		// Update the current & next path indexes.
		void UpdatePath();

		// Called when the AI is at the end of the path.
		void EndOfPath();

		// Move to the next path point.
		void Move() const;

		// The collision handling function for players.
		// Params:
		//	 event = The collision event object.
		void CollisionHandler(const Event& event);

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Properties (save to/load from file)
		float speed;
		bool faceVelocity;
		LoopMode loopMode;
		unsigned pathSize;
		std::vector<Vector2D> path;

		// Components
		Transform* transform;
		Physics* physics;

		// Other variables
		unsigned pathIndex;
		unsigned nextPathIndex;
		bool moving;
		bool movingForwards;
	};
}

//------------------------------------------------------------------------------
