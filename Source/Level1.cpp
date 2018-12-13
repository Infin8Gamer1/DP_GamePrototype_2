//------------------------------------------------------------------------------
//
// File Name:	Level1.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Level1.h"
#include "Space.h"
#include "MeshHelper.h"
#include "Sprite.h"
#include "Transform.h"
#include "Physics.h"
#include "Archetypes.h"
#include <Input.h>
#include <Mesh.h>
#include <Color.h>
#include <Engine.h>
#include <Texture.h>
#include <SpriteSource.h>
#include <Tilemap.h>

Levels::Level1::Level1() : Level("Level1")
{

	// Tilemap
	dataMap = nullptr;
	textureMap = nullptr;
	spriteSourceMap = nullptr;
	meshMap = nullptr;

	columnsMap = 4;
	rowsMap = 3;
}

void Levels::Level1::Load()
{
	std::cout << GetName() << "::Load" << std::endl;

	//map
	Vector2D textureSizeMap = Vector2D(1.0f / columnsMap, 1.0f / rowsMap);
	meshMap = CreateQuadMesh(textureSizeMap, Vector2D(1, 1));

	textureMap = Texture::CreateTextureFromFile("TilemapV2.png");

	spriteSourceMap = new SpriteSource(columnsMap, rowsMap, textureMap);
}

void Levels::Level1::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;

	dataMap = Tilemap::CreateTilemapFromFile("Assets/Levels/Level1.txt");
	if (dataMap == nullptr)
	{
		std::cout << "Error Loading Tilemap!";
	}

	GameObject* Map = Archetypes::CreateLevel1Tilemap(meshMap, spriteSourceMap, dataMap);
	GetSpace()->GetObjectManager().AddObject(*Map);

	/*GameObject* Ship = Archetypes::CreateShip(meshShip);
	GetSpace()->GetObjectManager().AddObject(*Ship);*/
}

void Levels::Level1::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (Input::GetInstance().CheckReleased('1')) {
		GetSpace()->RestartLevel();
	}
}

void Levels::Level1::Shutdown()
{
	std::cout << GetName() << "::Shutdown" << std::endl;
}

void Levels::Level1::Unload()
{
	std::cout << GetName() << "::Unload" << std::endl;

	delete dataMap;
	dataMap = nullptr;
	delete textureMap;
	textureMap = nullptr;
	delete spriteSourceMap;
	spriteSourceMap = nullptr;
	delete meshMap;
	meshMap = nullptr;
}