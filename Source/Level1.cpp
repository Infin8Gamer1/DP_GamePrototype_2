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
#include "SpriteText.h"

Levels::Level1::Level1() : Level("Level1"), meshShip(nullptr), meshBullet(nullptr), dataMap(nullptr), textureMap(nullptr), spriteSourceMap(nullptr), meshMap(nullptr), columnsMap(4), rowsMap(3)
{
}

void Levels::Level1::Load()
{
	std::cout << GetName() << "::Load" << std::endl;
	
	// Create meshes.
	meshShip = CreateTriangleMesh(Color(1, 0, 0), Color(0, 1, 0), Color(0, 0, 1));
	meshBullet = CreateTriangleMesh(Color(1, 0, 0), Color(1, 0, 0), Color(1, 0, 0));
	meshQuadGeneric = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));

	// Create textures.
	textureTurret = Texture::CreateTextureFromFile("Turret.png");
	textureTurretProjectile = Texture::CreateTextureFromFile("TurretProjectile.png");

	// Create sprite sources.
	spriteSourceTurret = new SpriteSource(1, 1, textureTurret);
	spriteSourceTurretProjectile = new SpriteSource(1, 1, textureTurretProjectile);

	// Get the object manager for ease of use.
	GameObjectManager& objectManager = GetSpace()->GetObjectManager();

	GameObject* projectileArchetype = Archetypes::CreateTurretProjectile(meshQuadGeneric, spriteSourceTurretProjectile);
	objectManager.AddArchetype(*projectileArchetype);
	objectManager.AddArchetype(*Archetypes::CreateTurret(projectileArchetype, meshQuadGeneric, spriteSourceTurret));

	objectManager.AddArchetype(*Archetypes::CreateText());

	GameObject* Bullet = Archetypes::CreateBulletArchetype(meshBullet);
	objectManager.AddArchetype(*Bullet);

	//map
	Vector2D textureSizeMap = Vector2D(1.0f / columnsMap, 1.0f / rowsMap);
	meshMap = CreateQuadMesh(textureSizeMap, Vector2D(1, 1));

	textureMap = Texture::CreateTextureFromFile("TilemapV2.png");

	spriteSourceMap = new SpriteSource(columnsMap, rowsMap, textureMap);
}

void Levels::Level1::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;

	// Get the object manager for ease of use.
	GameObjectManager& objectManager = GetSpace()->GetObjectManager();

	//reload the tile map
	dataMap = Tilemap::CreateTilemapFromFile("Assets/Levels/Level1.txt");
	if (dataMap == nullptr)
	{
		std::cout << "Error Loading Tilemap!";
	}

	GameObject* Map = Archetypes::CreateLevel1Tilemap(meshMap, spriteSourceMap, dataMap);
	objectManager.AddObject(*Map);

	objectManager.AddObject(*new GameObject(*objectManager.GetArchetypeByName("Turret")));

	GameObject* circle = Archetypes::CreateCircle(meshQuadGeneric, spriteSourceTurret);
	static_cast<Transform*>(circle->GetComponent("Transform"))->SetTranslation(Vector2D(000.0f, 200.0f));
	static_cast<Physics*>(circle->GetComponent("Physics"))->SetVelocity(Vector2D(25.0f, -75.0f));
	objectManager.AddObject(*circle);

	GameObject* text = new GameObject(*objectManager.GetArchetypeByName("Text"));
	static_cast<SpriteText*>(text->GetComponent("SpriteText"))->SetText("Gamer Time");
	static_cast<Transform*>(text->GetComponent("Transform"))->SetTranslation(Vector2D(0.0f, -200.0f));
	objectManager.AddObject(*text);

	GameObject* gameController = Archetypes::CreateGameController();
	objectManager.AddObject(*gameController);
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

	delete dataMap;
	dataMap = nullptr;
}

void Levels::Level1::Unload()
{
	std::cout << GetName() << "::Unload" << std::endl;

	delete spriteSourceMap;
	spriteSourceMap = nullptr;
	delete textureMap;
	textureMap = nullptr;
	delete meshMap;
	meshMap = nullptr;

	delete spriteSourceTurretProjectile;
	spriteSourceTurretProjectile = nullptr;
	delete spriteSourceTurret;
	spriteSourceTurret = nullptr;

	delete textureTurretProjectile;
	textureTurretProjectile = nullptr;
	delete textureTurret;
	textureTurret = nullptr;

	delete meshQuadGeneric;
	meshQuadGeneric = nullptr;
	delete meshBullet;
	meshBullet = nullptr;
	delete meshShip;
	meshShip = nullptr;

}