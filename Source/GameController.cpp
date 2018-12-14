/*
File: GameController.cpp
Name: Tyler Miller, Jacob Holyfield
Date: 12-12-18
Desc: The controller of the enemies
*/
#include "stdafx.h"
#include "GameController.h"
#include "Physics.h"
#include "Transform.h"
#include "Space.h"
#include "Tilemap.h"
#include "PatrolAI.h"
#include <ColliderTilemap.h>
#include <GameObject.h>
#include <Input.h>
#include <Animation.h>
#include "PatrolAI.h"

GameController::GameController()
	:Component("GameController"), physics(nullptr), transform(nullptr), pathTilesAvailable(0), turretsAvailable(0)
{
}

GameController::~GameController()
{
}

Component * GameController::Clone() const
{
	return new GameController(*this);
}

void GameController::Initialize()
{
	ColliderTilemap* CT = static_cast<ColliderTilemap*>(GetOwner()->GetSpace()->GetObjectManager().GetObjectByName("tileMapLevel1")->GetComponent("Collider"));
	enemyPath.push_back(CT->ConvertTileMapCordsToWorldCords(Vector2D(9, 0)));
	enemyPath.push_back(CT->ConvertTileMapCordsToWorldCords(Vector2D(9, 1)));
	enemyPath.push_back(CT->ConvertTileMapCordsToWorldCords(Vector2D(9, 2)));
}

void GameController::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (Input::GetInstance().CheckTriggered(' ')) {
		SpawnEnemy();
	}

	/*if (static_cast<Behaviors::PatrolAI*>(GetOwner()->GetComponent("PatrolAI"))->GetMoving() != true)
	{
		//Activate A* here
	}*/
}

void GameController::SetAmountOfTiles(int tiles)
{
	pathTilesAvailable = tiles;
}

int GameController::GetAmountOfTiles(void)
{
	return pathTilesAvailable;
}

void GameController::SetAmountOfTurrets(int turrets)
{
	turretsAvailable = turrets;
}

int GameController::GetAmountOfTurrets(void)
{
	return turretsAvailable;
}

void GameController::SetEnemyPath(std::vector<Vector2D> path)
{
	enemyPath = path;
}

std::vector<Vector2D> GameController::GetEnemyPath()
{
	return enemyPath;
}

void GameController::AddPointToEnemyPath(Vector2D point)
{
	enemyPath.push_back(point);
}

void GameController::SpawnEnemy()
{
	GameObjectManager& gom = GetOwner()->GetSpace()->GetObjectManager();

	ColliderTilemap* ct = static_cast<ColliderTilemap*>(gom.GetObjectByName("tileMapLevel1")->GetComponent("Collider"));

	GameObject* enemy = new GameObject(*gom.GetArchetypeByName("Enemy"));
	static_cast<Transform*>(enemy->GetComponent("Transform"))->SetTranslation(ct->ConvertTileMapCordsToWorldCords(EnemySpawnLocation));
	static_cast<Animation*>(enemy->GetComponent("Animation"))->Play(0, 17, 0.05f, true);
	static_cast<Behaviors::PatrolAI*>(enemy->GetComponent("PatrolAI"))->SetPath(enemyPath);
	gom.AddObject(*enemy);
	
}
