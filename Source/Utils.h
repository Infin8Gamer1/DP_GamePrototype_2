//------------------------------------------------------------------------------
//
// File Name:	Utils.h
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

// Systems
#include <GameObjectManager.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

typedef class Transform Transform;
typedef class Physics Physics;
typedef struct Event Event;
typedef class Texture Texture;
typedef class Mesh Mesh;
typedef class Collider Collider;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Utils
{
	// Linearly interpolates between two floats.
	// Params:
	//   a = The first float.
	//   b = The second float.
	//   t = The mix between the two floats (0-1)
	// Returns:
	//   The interpolated output.
	float Lerp(float a, float b, float t);

	// Linearly interpolates between two vectors.
	// Params:
	//   a = The first vector.
	//   b = The second vector.
	//   t = The mix between the two vector (0-1)
	// Returns:
	//   The interpolated output.
	Vector2D Lerp(Vector2D a, Vector2D b, float t);

	// Linearly interpolates between two angles, in radians.
	// Params:
	//   a = The first angle.
	//   b = The second angles.
	//   t = The mix between the two angles (0-1)
	// Returns:
	//   The interpolated output.
	float LerpRad(float a, float b, float t);

	// Linearly interpolates between two angles, in degrees.
	// Params:
	//   a = The first angle.
	//   b = The second angles.
	//   t = The mix between the two angles (0-1)
	// Returns:
	//   The interpolated output.
	float LerpDeg(float a, float b, float t);
}

//------------------------------------------------------------------------------
