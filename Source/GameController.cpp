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

GameController::GameController()
	:Component("GameController"), physics(nullptr), transform(nullptr), tilesAvailable(0)
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
