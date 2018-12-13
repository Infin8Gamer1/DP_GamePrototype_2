/*
File: GameController.cpp
Name: Tyler Miller
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

GameController::GameController()
	:Component("GameController"), physics(nullptr), transform(nullptr), tilesAvailable(0)
{
	tilesAvailable = 1;
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
	enemyPath.push_back(CT->ConvertTileMapCordsToWorldCords(Vector2D(8, 0)));
	enemyPath.push_back(CT->ConvertTileMapCordsToWorldCords(Vector2D(8, 1)));
	enemyPath.push_back(CT->ConvertTileMapCordsToWorldCords(Vector2D(8, 2)));
}

void GameController::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	/*if (static_cast<Behaviors::PatrolAI*>(GetOwner()->GetComponent("PatrolAI"))->GetMoving() != true)
	{
		//Activate A* here
	}*/
}

void GameController::SetAmountOfTiles(int tiles)
{
	tilesAvailable = tiles;
}

int GameController::GetAmountOfTiles(void)
{
	return tilesAvailable;
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
