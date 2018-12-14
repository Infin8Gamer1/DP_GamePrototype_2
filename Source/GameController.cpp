/*
File: GameController.cpp
Name: Tyler Miller, Jacob Holyfield, David Cohen
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
#include "SpriteText.h"
#include <sstream>

GameController::GameController()
	:Component("GameController"), physics(nullptr), transform(nullptr), tilemap(nullptr), HUD(nullptr),
	roundState(RoundStates::RoundStateStrategy), roundNumber(1),
	enemiesPerRound(2), enemiesInQueue(0), enemySpawnTimer(0.0f), enemySpawnDelay(0.25f),
	pathTilesAvailable(0), turretsAvailable(0)
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
	switch (roundState)
	{
	case RoundStates::RoundStateStrategy:
	{
		if (HUD != nullptr)
		{
			// Build HUD text.
			std::stringstream ss;
			ss << "Round " << roundNumber << std::endl;
			ss << "Enemies: " << enemiesPerRound << std::endl;
			ss << "Paths available: " << pathTilesAvailable << std::endl;
			ss << "Turrets available: " << turretsAvailable;

			// Display HUD text.
			HUD->SetText(ss.str());
		}

		if (Input::GetInstance().CheckTriggered(' ')) {
			roundState = RoundStates::RoundStateWave;
			enemiesInQueue = enemiesPerRound;
		}

		break;
	}
	case RoundStates::RoundStateWave:
	{
		enemySpawnTimer = max(0.0f, enemySpawnTimer - dt);

		// If we still need to spawn enemies and the timer is up, spawn a new one and reset the timer.
		if (enemiesInQueue > 0 && enemySpawnTimer <= 0.0f)
		{
			enemySpawnTimer = enemySpawnDelay;
			SpawnEnemy();
			--enemiesInQueue;
		}

		GameObjectManager& objectManager = GetOwner()->GetSpace()->GetObjectManager();

		int enemyCount = objectManager.GetObjectCount("Enemy");

		if (HUD != nullptr)
		{
			// Build HUD text.
			std::stringstream ss;
			ss << "Round " << roundNumber << std::endl;
			ss << "Enemies left: " << (enemiesInQueue + enemyCount) << std::endl;

			// Display HUD text.
			HUD->SetText(ss.str());
		}

		if (enemiesInQueue <= 0 && enemyCount <= 0)
		{
			// Prepare next round.
			roundState = RoundStates::RoundStateStrategy;
			++roundNumber;
			enemiesPerRound += 4;
			++pathTilesAvailable;
			++turretsAvailable;
		}

		break;
	}
	}
}

// Sets the current HUD pointer.
// Params:
//   HUD = The SpriteText* to use as the HUD.
void GameController::SetHUD(SpriteText* HUD_)
{
	HUD = HUD_;
}

// Gets the current HUD pointer.
// Returns:
//   The SpriteText* currently being used as the HUD.
SpriteText* GameController::GetHUD()
{
	return HUD;
}

void GameController::SetAmountOfTiles(int tiles)
{
	pathTilesAvailable = tiles;
}

int GameController::GetAmountOfTiles(void)
{
	return pathTilesAvailable;
}

// Sets the current amount of turrets.
// Params:
//   turrets = The amount of turrets.
void GameController::SetAmountOfTurrets(int turrets)
{
	turretsAvailable = turrets;
}

// Gets the current amount of turrets.
// Returns:
//   The amount of turrets.
int GameController::GetAmountOfTurrets()
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
