/*
File: GameController.h
Name: Tyler Miller
Date: 12-12-18
Desc: The controller of the enemies
*/
#pragma once
#include "Component.h"
#include "Vector2D.h"

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
private:
	Physics* physics;
	Transform* transform;
	Tilemap* tilemap;
	int tilesAvailable;

};
