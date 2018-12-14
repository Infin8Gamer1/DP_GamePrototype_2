/*
File: GameController.h
Name: Tyler Miller, Jacob Holyfield, David Cohen
Date: 12-12-18
Desc: The controller of the enemies
*/
#pragma once
#include "Component.h"
#include "Vector2D.h"
#include <vector>

typedef class Transform Transform;
typedef class Physics Physics;
typedef class Tilemap Tilemap;
typedef class SpriteText SpriteText;

enum RoundStates
{
	RoundStateStrategy,
	RoundStateWave,
};

class GameController : public Component
{
public:
	GameController();
	~GameController();
	Component* Clone() const override;
	void Initialize() override;
	void Update(float dt) override;

	// Sets the current HUD pointer.
	// Params:
	//   HUD = The SpriteText* to use as the HUD.
	void SetHUD(SpriteText* HUD);

	// Gets the current HUD pointer.
	// Returns:
	//   The SpriteText* currently being used as the HUD.
	SpriteText* GetHUD();

	void SetAmountOfTiles(int tiles);
	int GetAmountOfTiles(void);

	// Sets the current amount of turrets.
	// Params:
	//   turrets = The amount of turrets.
	void SetAmountOfTurrets(int turrets);

	// Gets the current amount of turrets.
	// Returns:
	//   The amount of turrets.
	int GetAmountOfTurrets();

	void SetEnemyPath(std::vector<Vector2D> path);
	std::vector<Vector2D> GetEnemyPath();
	void AddPointToEnemyPath(Vector2D point);
private:
	void SpawnEnemy();

	//Components
	Physics* physics;
	Transform* transform;
	Tilemap* tilemap;
	SpriteText* HUD;

	RoundStates roundState;
	int roundNumber;

	int enemiesPerRound;
	int enemiesInQueue;
	float enemySpawnTimer;
	float enemySpawnDelay;

	const Vector2D EnemySpawnLocation = Vector2D(9,0);

	int pathTilesAvailable;

	int turretsAvailable;

	std::vector<Vector2D> enemyPath;


};
