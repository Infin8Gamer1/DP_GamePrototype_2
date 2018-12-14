//------------------------------------------------------------------------------
//
// File Name:	Level1.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright � 2018 DigiPen (USA) Corporation.
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
#include "GameController.h"

Levels::Level1::Level1() : Level("Level1"), meshShip(nullptr), meshBullet(nullptr), dataMap(nullptr), textureMap(nullptr), spriteSourceMap(nullptr), meshMap(nullptr), columnsMap(4), rowsMap(3)
{
}

void Levels::Level1::Load()
{
	std::cout << GetName() << "::Load" << std::endl;
	
	// Create meshes.
	meshQuadGeneric = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));

	// Get the object manager for ease of use.
	GameObjectManager& objectManager = GetSpace()->GetObjectManager();

	//Turret Projectile Architype
	textureTurretProjectile = Texture::CreateTextureFromFile("TurretProjectile.png");
	spriteSourceTurretProjectile = new SpriteSource(1, 1, textureTurretProjectile);
	GameObject* projectileArchetype = Archetypes::CreateTurretProjectile(meshQuadGeneric, spriteSourceTurretProjectile);
	objectManager.AddArchetype(*projectileArchetype);

	//Turret Architype
	textureTurret = Texture::CreateTextureFromFile("Turret.png");
	spriteSourceTurret = new SpriteSource(1, 1, textureTurret);
	objectManager.AddArchetype(*Archetypes::CreateTurret(projectileArchetype, meshQuadGeneric, spriteSourceTurret));

	//Text Architype
	objectManager.AddArchetype(*Archetypes::CreateText());

	//Enemy Architype
	Vector2D enemyTextureSize = Vector2D(1.0f / 17, 1.0f / 1);
	meshEnemy = CreateQuadMesh(enemyTextureSize, Vector2D(1, 1));

	textureEnemy = Texture::CreateTextureFromFile("Enemy.png");

	spriteSourceEnemy = new SpriteSource(17, 1, textureEnemy);

	objectManager.AddArchetype(*Archetypes::CreateEnemy(meshEnemy, spriteSourceEnemy, Vector2D(0,0), Vector2D(50,50)));

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

	GameObject* uiText = new GameObject(*objectManager.GetArchetypeByName("Text"));
	static_cast<SpriteText*>(uiText->GetComponent("SpriteText"))->SetText("Paths Available : X\nTurets Available : X");
	static_cast<Transform*>(uiText->GetComponent("Transform"))->SetTranslation(Vector2D(0.0f, -300.0f));
	objectManager.AddObject(*uiText);

	GameObject* gameController = Archetypes::CreateGameController();
	static_cast<GameController*>(gameController->GetComponent("GameController"))->SetHUD(static_cast<SpriteText*>(uiText->GetComponent("SpriteText")));
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

	//delete Map
	delete spriteSourceMap;
	spriteSourceMap = nullptr;
	delete textureMap;
	textureMap = nullptr;
	delete meshMap;
	meshMap = nullptr;


	//delete SpriteSources
	delete spriteSourceTurretProjectile;
	spriteSourceTurretProjectile = nullptr;
	delete spriteSourceTurret;
	spriteSourceTurret = nullptr;
	delete spriteSourceEnemy;
	spriteSourceEnemy = nullptr;

	//delete textures
	delete textureTurretProjectile;
	textureTurretProjectile = nullptr;
	delete textureTurret;
	textureTurret = nullptr;
	delete textureEnemy;
	textureEnemy = nullptr;

	//delete Meshes
	delete meshEnemy;
	meshEnemy = nullptr;
	delete meshQuadGeneric;
	meshQuadGeneric = nullptr;
	delete meshBullet;
	meshBullet = nullptr;
	delete meshShip;
	meshShip = nullptr;

}