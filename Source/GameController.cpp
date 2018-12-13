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

GameController::GameController()
	:Component("GameController"), physics(nullptr), transform(nullptr)
{
}

GameController::~GameController()
{
}

void GameController::Initialize()
{
}

void GameController::Update(float dt)
{
	if (physics->GetVelocity().x == 0 && physics->GetVelocity().y == 0)
	{
		//check to see if place is moveable
			//if moveable find moveable space and move accordingly
		//if path has ended, update current state of enemy
			//find the nearest city
		//go to the A* pathfinding for city
	}
}
