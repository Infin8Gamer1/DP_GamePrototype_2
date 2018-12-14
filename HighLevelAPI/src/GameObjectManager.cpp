//------------------------------------------------------------------------------
//
// File Name:	GameObjectManager.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameObjectManager.h"
#include "Space.h"
#include "GameObject.h"
#include "Collider.h"

GameObjectManager::GameObjectManager(Space * space) : BetaObject("ObjectManager", space)
{
	timeAccumulator = 0.0f;
	numArchetypes = 0;
	numObjects = 0;
}

GameObjectManager::~GameObjectManager()
{
	Shutdown();
	Unload();
}

void GameObjectManager::Update(float dt)
{
	if (!static_cast<Space*>(GetParent())->IsPaused()) {
		VariableUpdate(dt);
		FixedUpdate(dt);
	}
	DestroyObjects();
	Draw();
}

void GameObjectManager::Shutdown(void)
{
	for (size_t i = 0; i < numObjects; i++)
	{
		delete gameObjectActiveList[i];
		gameObjectActiveList[i] = nullptr;
	}

	numObjects = 0;
}

void GameObjectManager::Unload(void)
{
	for (size_t i = 0; i < numArchetypes; i++)
	{
		delete gameObjectArchetypes[i];
		gameObjectArchetypes[i] = nullptr;
	}

	numArchetypes = 0;
}

void GameObjectManager::AddObject(GameObject & _gameObject)
{
	if (numObjects + 1 < maxObjects) {
		gameObjectActiveList[numObjects++] = &_gameObject;
		_gameObject.SetParent(GetParent());
		_gameObject.Initialize();
	}
	else {
		std::cout << "added too many objects!" << std::endl;
		delete &_gameObject;
	}
}

void GameObjectManager::AddArchetype(GameObject & _gameObject)
{
	if (numArchetypes + 1 < maxArchetypes) {
		gameObjectArchetypes[numArchetypes] = &_gameObject;
		numArchetypes++;
	}
	else {
		std::cout << "added too many Archetypes!" << std::endl;
		_gameObject.~GameObject();
	}
}

GameObject * GameObjectManager::GetObjectByName(const std::string & objectName) const
{
	for (size_t i = 0; i < numObjects; i++)
	{
		if (gameObjectActiveList[i]->GetName() == objectName) {
			return gameObjectActiveList[i];
		}
	}
	//std::cout << "Couldn't find object with name of " << objectName << "." << std::endl;
	return nullptr;
}

// Returns a vector of pointers to active game objects matching the specified name.
// Params:
//	 objectName = The name of the object to be returned, if found.
// Returns:
//   A vector of pointers to the named game objects.
std::vector<GameObject*> GameObjectManager::GetAllObjectsByName(const std::string& objectName) const
{
	std::vector<GameObject*> objects;

	for (size_t i = 0; i < numObjects; i++)
	{
		if (gameObjectActiveList[i]->GetName() == objectName) {
			objects.push_back(gameObjectActiveList[i]);
		}
	}

	return objects;
}

GameObject * GameObjectManager::GetArchetypeByName(const std::string & objectName) const
{
	for (size_t i = 0; i < numArchetypes; i++)
	{
		if (gameObjectArchetypes[i]->GetName() == objectName) {
			return gameObjectArchetypes[i];
		}
	}

	std::cout << "Couldn't find archetype with name of " << objectName << "." << std::endl;
	return nullptr;
}

unsigned GameObjectManager::GetObjectCount(const std::string & objectName) const
{
	int output = 0;

	for (size_t i = 0; i < numObjects; i++)
	{
		if (gameObjectActiveList[i]->GetName() == objectName && !gameObjectActiveList[i]->IsDestroyed()) {
			output++;
		}
	}

	return output;
}

void GameObjectManager::VariableUpdate(float dt)
{
	for (size_t i = 0; i < numObjects; i++)
	{
		gameObjectActiveList[i]->Update(dt);
	}
}

void GameObjectManager::FixedUpdate(float dt)
{
	timeAccumulator += dt;

	if (timeAccumulator >= fixedUpdateDt)
	{
		for (size_t i = 0; i < numObjects; i++)
		{
			gameObjectActiveList[i]->FixedUpdate(fixedUpdateDt);
		}

		CheckCollisions();

		timeAccumulator -= fixedUpdateDt;
	}
}

void GameObjectManager::DestroyObjects()
{
	for (size_t i = 0; i < numObjects; i++)
	{
		if (gameObjectActiveList[i]->IsDestroyed()) {
			//delete the memory assosiated with it
			delete gameObjectActiveList[i];
			gameObjectActiveList[i] = nullptr;

			//shift the array so that there isn't a gap
			for (size_t z = i; z < numObjects; z++)
			{
				gameObjectActiveList[z] = gameObjectActiveList[z + 1];
			}
			
			//decrease the number of objects
			numObjects--;
		}
	}
}

void GameObjectManager::Draw(void)
{
	for (size_t i = 0; i < numObjects; i++)
	{
		gameObjectActiveList[i]->Draw();
	}
}

void GameObjectManager::CheckCollisions()
{
	for (size_t i = 0; i < numObjects; i++)
	{
		GameObject* go1 = gameObjectActiveList[i];
		if (!go1->IsDestroyed()) {
			Collider* collider1 = static_cast<Collider*>(go1->GetComponent("Collider"));
			if (collider1 != nullptr) {
				for (size_t x = 0; x < numObjects; x++)
				{
					GameObject* go2 = gameObjectActiveList[x];
					if (!go2->IsDestroyed()) {
						Collider* collider2 = static_cast<Collider*>(go2->GetComponent("Collider"));
						if (collider2 != nullptr && go1 != go2) {
							collider1->CheckCollision(*collider2);
						}
					}
				}
				
			}
		}
	}
}
