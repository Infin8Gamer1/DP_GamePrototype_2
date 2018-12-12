//------------------------------------------------------------------------------
//
// File Name:	Level2.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Space.h"
#include "Level2.h"
#include "MeshHelper.h"
#include "SpriteSource.h"
#include "Sprite.h"
#include "Animation.h"
#include "Level1.h"
#include "Transform.h"
#include "Physics.h"
#include "Archetypes.h"
#include <Input.h>
#include <Mesh.h>
#include <gdiplus.h>
#include <Texture.h>
#include <Engine.h>
#include "Level3.h"
#include "Tilemap.h"

Levels::Level2::Level2() : Level("Level2")
{
	//monkey
	meshMonkey = nullptr;
	textureMonkey = nullptr;
	spriteSourceMonkey = nullptr;

	columnsMonkey = 3;
	rowsMonkey = 5;

	//map
	dataMap = nullptr;
	textureMap = nullptr;
	spriteSourceMap = nullptr;
	meshMap = nullptr;

	columnsMap = 4;
	rowsMap = 3;
}

void Levels::Level2::Load()
{
	std::cout << "Level2::Load" << std::endl;

	//monkey
	Vector2D textureSize = Vector2D(1.0f / columnsMonkey, 1.0f / rowsMonkey);
	meshMonkey = CreateQuadMesh(textureSize, Vector2D(1, 1));

	textureMonkey = Texture::CreateTextureFromFile("Monkey.png");
	
	spriteSourceMonkey = new SpriteSource(columnsMonkey, rowsMonkey, textureMonkey);

	//map
	Vector2D textureSizeMap = Vector2D(1.0f / columnsMap, 1.0f / rowsMap);
	meshMap = CreateQuadMesh(textureSizeMap, Vector2D(1, 1));

	textureMap = Texture::CreateTextureFromFile("Tilemap.png");

	spriteSourceMap = new SpriteSource(columnsMap, rowsMap, textureMap);
}

void Levels::Level2::Initialize()
{
	std::cout << "Level2::Initialize" << std::endl;

	dataMap = Tilemap::CreateTilemapFromFile("Assets/Levels/Level2.txt");
	if (dataMap == nullptr)
	{
		std::cout << "Error Loading Tilemap!";
	}

	GameObject* Map = Archetypes::CreateTilemapObject(meshMap, spriteSourceMap, dataMap);
	GetSpace()->GetObjectManager().AddObject(*Map);

	GameObject* Monkey = Archetypes::CreateMonkey(meshMonkey, spriteSourceMonkey);
	static_cast<Animation*>(Monkey->GetComponent("Animation"))->Play(0, 8, 0.4f, false);
	GetSpace()->GetObjectManager().AddObject(*Monkey);
}

void Levels::Level2::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (Input::GetInstance().CheckReleased('1')) {
		GetSpace()->SetLevel(new Levels::Level1());
	}
	else if (Input::GetInstance().CheckReleased('2'))
	{
		GetSpace()->RestartLevel();
	}
	else if (Input::GetInstance().CheckReleased('3')) {
		GetSpace()->SetLevel(new Levels::Level3());
	}
}

void Levels::Level2::Unload()
{
	std::cout << "Level2::Unload" << std::endl;

	delete spriteSourceMonkey;
	spriteSourceMonkey = nullptr;
	delete meshMonkey;
	meshMonkey = nullptr;
	delete textureMonkey;
	textureMonkey = nullptr;

	delete dataMap;
	dataMap = nullptr;
	delete textureMap;
	textureMap = nullptr;
	delete spriteSourceMap;
	spriteSourceMap = nullptr;
	delete meshMap;
	meshMap = nullptr;
}
