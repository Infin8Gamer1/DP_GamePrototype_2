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

class GameController : public Component
{
public:
	GameController();
	~GameController();
	void Initialize() override;
	void Update(float dt) override;
private:
	Physics* physics;
	Transform* transform;
};
