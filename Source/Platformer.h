//------------------------------------------------------------------------------
//
// File Name:	Platformer.h
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

#include "Vector2D.h"
#include "Level.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Texture;
class Mesh;
class SpriteSource;
class GameObject;
class Tilemap;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Levels
{
	class Platformer : public Level
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Creates an instance of Platformer.
		Platformer();

		// Load the resources associated with Platformer.
		void Load() override;

		// Initialize the memory associated with Platformer.
		void Initialize() override;

		// Update Platformer.
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop.
		void Update(float dt) override;

		// Unload the resources associated with Platformer.
		void Unload() override;

	private:

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------\

		// Monkey
		Mesh* meshMonkey;
		Texture* textureMonkey;
		SpriteSource* spriteSourceMonkey;

		unsigned columnsMonkey;
		unsigned rowsMonkey;

		GameObject* MonkeyGO;

		// Tilemap
		Tilemap* dataMap;
		Texture* textureMap;
		SpriteSource* spriteSourceMap;
		Mesh* meshMap;

		unsigned columnsMap;
		unsigned rowsMap;

		//Collectables
		Mesh* meshCollectable;
		SpriteSource* spriteSourceCollectable;
		Texture* textureCollectable;

		//Hazards
		Mesh* meshHazard;
		SpriteSource* spriteSourceHazard;
		Texture* textureHazard;

		//Enemy
		Mesh* meshEnemy;
		Texture* textureEnemy;
		SpriteSource* spriteSourceEnemy;

		unsigned columnsEnemy;
		unsigned rowsEnemy;

		//misc
		int LevelCoinCount;
		
	};
}

//----------------------------------------------------------------------------
