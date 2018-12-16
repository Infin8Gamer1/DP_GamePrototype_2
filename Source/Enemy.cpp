//------------------------------------------------------------------------------
//
// File Name:	Enemy.cpp
// Author(s):	David Cohen	
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Enemy.h"

// Systems
#include <GameObject.h>
#include <Space.h>
#include <GameObjectManager.h>
#include <vector>

// Components
#include <Transform.h>
#include "PatrolAI.h"
#include <Collider.h>
#include <ColliderTilemap.h>

#include <Tilemap.h>
#include <limits.h>

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Collision handler for Enemy objects.
	// Params:
	//   object = The first object.
	//   other  = The other object the first object is colliding with.
	void EnemyCollisionHandler(GameObject& object, GameObject& other)
	{
		// Turret projectile collision handler.
		if (other.GetName() == "TurretProjectile")
		{
			Enemy* enemy = static_cast<Enemy*>(object.GetComponent("Enemy"));

			// Decrement the enemy's health and destroy the enemy if it has 0 health remaining.
			if (--enemy->health <= 0)
				object.Destroy();

			other.Destroy();
		}
	}

	// Constructor
	// Params:
	//   health = How much health the enemy should have.
	Enemy::Enemy(int health) : Component("Enemy"), transform(nullptr), patrolAI(nullptr), health(health)
	{
		mode = EnemyMode::PathFollow;
	}

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* Enemy::Clone() const
	{
		return new Enemy(*this);
	}

	// Initialize data for this object.
	void Enemy::Initialize()
	{
		transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));

		ct = static_cast<ColliderTilemap*>(GetOwner()->GetSpace()->GetObjectManager().GetObjectByName("tileMapLevel1")->GetComponent("Collider"));
		dataMap = ct->GetTilemap();

		patrolAI = static_cast<PatrolAI*>(GetOwner()->GetComponent("PatrolAI"));
		patrolAI->SetLoopMode(PatrolAI::LoopMode::STOP);

		Collider* collider = static_cast<Collider*>(GetOwner()->GetComponent("Collider"));
		collider->SetCollisionHandler(EnemyCollisionHandler);
	}

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void Enemy::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		if (!patrolAI->GetMoving() && mode == EnemyMode::PathFollow)
		{
			patrolAI->SetActive(false);
			mode = EnemyMode::AStar;
			AStarToClosestCity();
		} else if (!patrolAI->GetMoving() && mode == EnemyMode::AStar)
		{
			patrolAI->SetActive(false);
			mode = EnemyMode::Attack;
		}
	}

	// Gets the enemy's current health.
	int Enemy::GetHealth()
	{
		return health;
	}

	// Sets the enemy's current health.
	void Enemy::SetHealth(int health_)
	{
		health = health_;
	}


	void Enemy::AStarToClosestCity()
	{

		//set start to the current position
		Vector2D start = ct->ConvertWorldCordsToTileMapCords(Vector2D(floor(transform->GetTranslation().x), floor(transform->GetTranslation().y)));
		//set the goal to the closest city
		std::vector<GameObject*> citys = GetOwner()->GetSpace()->GetObjectManager().GetAllObjectsByName("City");

		if (citys.size() < 1) {
			return;
		}

		float minDistance = 1000000;

		GameObject* closestCity = nullptr;

		for (size_t i = 0; i < citys.size(); i++)
		{
			Transform* cityTransform = static_cast<Transform*>(citys.at(i)->GetComponent("Transform"));
			float distance = cityTransform->GetTranslation().Distance(transform->GetTranslation());
			if (distance < minDistance) {
				minDistance = distance;
				closestCity = citys.at(i);
			}
		}
		
		Transform* closestCityTransform = static_cast<Transform*>(closestCity->GetComponent("Transform"));
		Vector2D goal = ct->ConvertWorldCordsToTileMapCords(closestCityTransform->GetTranslation());

		//the path for thing to follow in world cords
		std::vector<Vector2D> finalPath;
		//we know the first node is start so put that in
		finalPath.push_back(ct->ConvertTileMapCordsToWorldCords(Vector2D(start.x - 0.5f, start.y - 0.5f)));
		//TODO: Auctualy generate path around obsticles using A*
		//but for now just put the end point in
		finalPath.push_back(ct->ConvertTileMapCordsToWorldCords(Vector2D(goal.x - 0.5f, goal.y - 0.5f)));

		//set the PatrolAI to go follow the path
		patrolAI->ClearPath();
		patrolAI->SetPath(finalPath);
		patrolAI->SetActive(true);
		patrolAI->SetMoving(true);

		/*// The set of nodes already evaluated
		std::vector<Vector2D> closedSet;

		// The set of currently discovered nodes that are not evaluated yet.
		// Initially, only the start node is known.
		std::vector<Vector2D> openSet;
		openSet.push_back(start);

		// For each node, which node it can most efficiently be reached from.
		// If a node can be reached from many nodes, cameFrom will eventually contain the
		// most efficient previous step.
		std::vector<Vector2D> cameFrom;

		// For each node, the cost of getting from the start node to that node.
		gScore : = map with default value of Infinity

		// The cost of going from start to start is zero.
		gScore[start] : = 0

		// For each node, the total cost of getting from the start node to the goal
		// by passing by that node. That value is partly known, partly heuristic.
		fScore : = map with default value of Infinity

		// For the first node, that value is completely heuristic.
		fScore[start] : = heuristic_cost_estimate(start, goal)

		//while openSet is not empty
		while (!openSet.empty()) {
			Vector2D current; //= the node in openSet having the lowest fScore[] value
			if (current == goal) {
				return reconstruct_path(cameFrom, current);
			}
				
			openSet.Remove(current);
			closedSet.Add(current);
				

				for each neighbor of current
					if neighbor in closedSet
						continue		// Ignore the neighbor which is already evaluated.

										// The distance from start to a neighbor
						tentative_gScore : = gScore[current] + dist_between(current, neighbor)

						if neighbor not in openSet	// Discover a new node
							openSet.Add(neighbor)
						else if tentative_gScore >= gScore[neighbor]
							continue;

				 // This path is the best until now. Record it!
				 cameFrom[neighbor] : = current
				gScore[neighbor] : = tentative_gScore
				fScore[neighbor] : = gScore[neighbor] + heuristic_cost_estimate(neighbor, goal)
		}*/
			
	}
};
