#include "stdafx.h"
#include "Platformer.h"
#include "Space.h"
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
#include "MonkeyMovement.h"
#include "WinLevel.h"
#include "ColliderTilemap.h"

Levels::Platformer::Platformer() : Level("Platformer")
{
	//monkey
	meshMonkey = nullptr;
	textureMonkey = nullptr;
	spriteSourceMonkey = nullptr;

	columnsMonkey = 3;
	rowsMonkey = 5;

	MonkeyGO = nullptr;

	//map
	dataMap = nullptr;
	textureMap = nullptr;
	spriteSourceMap = nullptr;
	meshMap = nullptr;

	columnsMap = 4;
	rowsMap = 3;

	//collectables
	meshCollectable = nullptr;
	spriteSourceCollectable = nullptr;
	textureCollectable = nullptr;

	//hazards
	meshHazard = nullptr;
	spriteSourceHazard = nullptr;
	textureHazard = nullptr;

	//Enemy
	meshEnemy = nullptr;
	textureEnemy = nullptr;
	spriteSourceEnemy = nullptr;

	columnsEnemy = 7;
	rowsEnemy = 3;

	//misc
	LevelCoinCount = 4;
}

void Levels::Platformer::Load()
{
	std::cout << "Platformer::Load" << std::endl;

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

	//collectable
	meshCollectable = CreateQuadMesh(Vector2D(1, 1), Vector2D(1, 1));
	textureCollectable = Texture::CreateTextureFromFile("Coin.png");
	spriteSourceCollectable = new SpriteSource(1, 1, textureCollectable);

	GameObject* Collectable = Archetypes::CreateCollectable(meshCollectable, spriteSourceCollectable, Vector2D(0, 0));
	GetSpace()->GetObjectManager().AddObject(*Collectable);

	//hazard
	meshHazard = CreateQuadMesh(Vector2D(1, 1), Vector2D(1, 1));
	textureHazard = Texture::CreateTextureFromFile("Hazard.png");
	spriteSourceHazard = new SpriteSource(1, 1, textureHazard);

	//enemy
	Vector2D textureSizeEnemy = Vector2D(1.0f / columnsEnemy, 1.0f / rowsEnemy);
	meshEnemy = CreateQuadMesh(textureSizeEnemy, Vector2D(1, 1));

	textureEnemy = Texture::CreateTextureFromFile("Enemy.png");

	spriteSourceEnemy = new SpriteSource(columnsEnemy, rowsEnemy, textureEnemy);
}

void Levels::Platformer::Initialize()
{
	std::cout << "Platformer::Initialize" << std::endl;
	//Tilemap
	dataMap = Tilemap::CreateTilemapFromFile("Assets/Levels/PlatformerTilemap.txt");
	if (dataMap == nullptr)
	{
		std::cout << "Error Loading Tilemap!";
	}

	GameObject* Map = Archetypes::CreatePlatformerTilemapObject(meshMap, spriteSourceMap, dataMap);
	GetSpace()->GetObjectManager().AddObject(*Map);

	ColliderTilemap* ct = static_cast<ColliderTilemap*>(Map->GetComponent("Collider"));

	//Monkey
	MonkeyGO = Archetypes::CreatePlatformerMonkey(meshMonkey, spriteSourceMonkey);
	static_cast<Transform*>(MonkeyGO->GetComponent("Transform"))->SetTranslation(ct->ConvertTileMapCordsToWorldCords(Vector2D(1,2)));
	static_cast<Animation*>(MonkeyGO->GetComponent("Animation"))->Play(0, 8, 0.05f, false);
	GetSpace()->GetObjectManager().AddObject(*MonkeyGO);

	//Collectables!
	GameObject* Collectable1 = Archetypes::CreateCollectable(meshCollectable, spriteSourceCollectable, ct->ConvertTileMapCordsToWorldCords(Vector2D(2,5)));
	GetSpace()->GetObjectManager().AddObject(*Collectable1);

	GameObject* Collectable2 = Archetypes::CreateCollectable(meshCollectable, spriteSourceCollectable, ct->ConvertTileMapCordsToWorldCords(Vector2D(5, 8)));
	GetSpace()->GetObjectManager().AddObject(*Collectable2);

	GameObject* Collectable3 = Archetypes::CreateCollectable(meshCollectable, spriteSourceCollectable, ct->ConvertTileMapCordsToWorldCords(Vector2D(6, 2)));
	GetSpace()->GetObjectManager().AddObject(*Collectable3);

	GameObject* Collectable4 = Archetypes::CreateCollectable(meshCollectable, spriteSourceCollectable, ct->ConvertTileMapCordsToWorldCords(Vector2D(11, 8)));
	GetSpace()->GetObjectManager().AddObject(*Collectable4);

	//Hazards!
	GameObject* Hazard1 = Archetypes::CreateHazard(meshHazard, spriteSourceHazard, ct->ConvertTileMapCordsToWorldCords(Vector2D(7, 8)));
	GetSpace()->GetObjectManager().AddObject(*Hazard1);

	GameObject* Hazard2 = Archetypes::CreateHazard(meshHazard, spriteSourceHazard, ct->ConvertTileMapCordsToWorldCords(Vector2D(4, 8)));
	GetSpace()->GetObjectManager().AddObject(*Hazard2);

	GameObject* Hazard3 = Archetypes::CreateHazard(meshHazard, spriteSourceHazard, ct->ConvertTileMapCordsToWorldCords(Vector2D(3, 8)));
	GetSpace()->GetObjectManager().AddObject(*Hazard3);

	GameObject* Hazard4 = Archetypes::CreateHazard(meshHazard, spriteSourceHazard, ct->ConvertTileMapCordsToWorldCords(Vector2D(8, 9)));
	GetSpace()->GetObjectManager().AddObject(*Hazard4);

	//Enemy
	GameObject* EnemyGO = Archetypes::CreateEnemy(meshEnemy, spriteSourceEnemy, ct->ConvertTileMapCordsToWorldCords(Vector2D(13, 8)));
	static_cast<Animation*>(EnemyGO->GetComponent("Animation"))->Play(0, 8, 0.1f, true);
	GetSpace()->GetObjectManager().AddObject(*EnemyGO);

	GameObject* EnemyGO2 = Archetypes::CreateEnemy(meshEnemy, spriteSourceEnemy, ct->ConvertTileMapCordsToWorldCords(Vector2D(14, 5)));
	static_cast<Animation*>(EnemyGO2->GetComponent("Animation"))->Play(0, 8, 0.1f, true);
	GetSpace()->GetObjectManager().AddObject(*EnemyGO2);

	GameObject* EnemyGO3 = Archetypes::CreateEnemy(meshEnemy, spriteSourceEnemy, ct->ConvertTileMapCordsToWorldCords(Vector2D(12, 1)));
	static_cast<Animation*>(EnemyGO3->GetComponent("Animation"))->Play(0, 8, 0.1f, true);
	GetSpace()->GetObjectManager().AddObject(*EnemyGO3);
}

void Levels::Platformer::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	Behaviors::MonkeyMovement* MM = static_cast<Behaviors::MonkeyMovement*>(MonkeyGO->GetComponent("MonkeyMovement"));

	//if we have collected all of the coins then go to the win level
	if (MM->GetCoinsCollected() >= LevelCoinCount) {
		GetSpace()->SetLevel(new Levels::WinLevel());
	}
	else if (MM->GetHealth() <= 0) {
		GetSpace()->RestartLevel();
	}
}

void Levels::Platformer::Unload()
{
	std::cout << "Platformer::Unload" << std::endl;

	//Monkey
	delete spriteSourceMonkey;
	spriteSourceMonkey = nullptr;
	delete meshMonkey;
	meshMonkey = nullptr;
	delete textureMonkey;
	textureMonkey = nullptr;

	//Tilemap
	delete dataMap;
	dataMap = nullptr;
	delete textureMap;
	textureMap = nullptr;
	delete spriteSourceMap;
	spriteSourceMap = nullptr;
	delete meshMap;
	meshMap = nullptr;

	//Collectables
	delete meshCollectable;
	meshCollectable = nullptr;
	delete spriteSourceCollectable;
	spriteSourceCollectable = nullptr;
	delete textureCollectable;
	textureCollectable = nullptr;

	//Hazards
	delete meshHazard;
	meshHazard = nullptr;
	delete spriteSourceHazard;
	spriteSourceHazard = nullptr;
	delete textureHazard;
	textureHazard = nullptr;

	//Enemy
	delete spriteSourceEnemy;
	spriteSourceEnemy = nullptr;
	delete meshEnemy;
	meshEnemy = nullptr;
	delete textureEnemy;
	textureEnemy = nullptr;
}
