//------------------------------------------------------------------------------
//
// File Name:	Utils.cpp
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

#include "Utils.h"

// Systems
#include <GameObject.h>
#include <Space.h>
#include <GameObjectManager.h>
#include <Input.h>
#include <Parser.h>
#include <Engine.h>
#include <Random.h>

// Components
#include <Transform.h>
#include <Physics.h>
#include <Collider.h>
#include <ColliderRectangle.h>
#include <Sprite.h>

//------------------------------------------------------------------------------

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
	float Lerp(float a, float b, float t)
	{
		return a * (1.0f - t) + b * t;
	}

	// Linearly interpolates between two vectors.
	// Params:
	//   a = The first vector.
	//   b = The second vector.
	//   t = The mix between the two vector (0-1)
	// Returns:
	//   The interpolated output.
	Vector2D Lerp(Vector2D a, Vector2D b, float t)
	{
		return a * (1.0f - t) + b * t;
	}

	// Linearly interpolates between two angles, in radians.
	// Params:
	//   a = The first angle.
	//   b = The second angles.
	//   t = The mix between the two angles (0-1)
	// Returns:
	//   The interpolated output.
	float LerpRad(float a, float b, float t)
	{
		float offset = 0.0f;

		// Move B as close to A as possible in 2Pi increments.
		while (abs(a - (b + offset + M_PI_F * 2.0f)) < abs(a - (b + offset)))
		{
			offset += M_PI_F * 2.0f;
		}

		while (abs(a - (b + offset - M_PI_F * 2.0f)) < abs(a - (b + offset)))
		{
			offset -= M_PI_F * 2.0f;
		}

		return a * (1.0f - t) + (b + offset) * t;
	}

	// Linearly interpolates between two angles, in degrees.
	// Params:
	//   a = The first angle.
	//   b = The second angles.
	//   t = The mix between the two angles (0-1)
	// Returns:
	//   The interpolated output.
	float LerpDeg(float a, float b, float t)
	{
		float offset = 0.0f;

		// Move B as close to A as possible in 360 degree increments.
		while (abs(a - (b + offset + 360.0f)) < abs(a - (b + offset)))
		{
			offset += 360.0f;
		}

		while (abs(a - (b + offset - 360.0f)) < abs(a - (b + offset)))
		{
			offset -= 360.0f;
		}

		return a * (1.0f - t) + (b + offset) * t;
	}
}

//------------------------------------------------------------------------------
