//------------------------------------------------------------------------------
//
// File Name:	Archetypes.h
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
#include <Vector2D.h>
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class GameObject;
class SpriteSource;
class Mesh;
class Tilemap;
class Vector2D;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Archetypes
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Create the archetype for the bullet object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateBulletArchetype(Mesh* mesh);

	// Create the circle game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateCircle(Mesh* mesh, SpriteSource* spriteSource);

	// Create the point game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreatePoint(Mesh* mesh, SpriteSource* spriteSource);

	// Create the rectangle game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateRectangle(Mesh* mesh);

	// Create a tilemap object for the Platformer level
	// Params:
	//   mesh = The mesh to use for the sprite.
	//   spriteSource = The sprite source to use for the sprite.
	//   map = The map to use for tilemap related components.
	// Returns:
	//   A pointer to the newly constructed game object.
	GameObject* CreateLevel1Tilemap(Mesh* mesh, SpriteSource* spriteSource, Tilemap* map);

	// Create a text game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object.
	GameObject* CreateText();

	// Create a turret game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateTurret(GameObject* projectileArchetype, Mesh* mesh, SpriteSource* spriteSource);

	// Create a turret projectile game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateTurretProjectile(Mesh* mesh, SpriteSource* spriteSource);

	// Create an Enemy game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateEnemy(Mesh* mesh, SpriteSource* spriteSource, Vector2D translation = Vector2D(0,0), Vector2D scale = Vector2D(80, 80));

	GameObject* CreateGameController();
}

//----------------------------------------------------------------------------
