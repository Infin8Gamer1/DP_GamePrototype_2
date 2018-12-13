/*
File: GameController.h
Name: Tyler Miller
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

class GameController : public Component
{
public:
	GameController();
	~GameController();
	Component* Clone() const override;
	void Initialize() override;
	void Update(float dt) override;
	void SetAmountOfTiles(int tiles);
	int GetAmountOfTiles(void);
	void SetEnemyPath(std::vector<Vector2D> path);
	std::vector<Vector2D> GetEnemyPath();
	void AddPointToEnemyPath(Vector2D point);
private:
	Physics* physics;
	Transform* transform;
	Tilemap* tilemap;
	int tilesAvailable;
	std::vector<Vector2D> enemyPath;

};
