//------------------------------------------------------------------------------
//
// File Name:	Archetypes.cpp
// Author(s):	Jacob Holyfield, Tyler Miller, David Cohen
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Archetypes.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Animation.h"
#include "Physics.h"
#include "TimedDeath.h"
#include "BulletMovement.h"
#include "ColliderPoint.h"
#include "ColliderCircle.h"
#include "ColliderRectangle.h"
#include "ColorChange.h"
#include "ScreenWrap.h"
#include "SpriteTilemap.h"
#include "ColliderTilemap.h"
#include "Enemy.h"
#include <Graphics.h>
#include "PlacePathTile.h"
#include "TurretAI.h"
#include "SpriteText.h"
#include "GameController.h"
#include "PlaceTurretTile.h"
#include "PatrolAI.h"
#include "AStarPath.h"
#include "City.h"
#include "HealthBar.h"

namespace Archetypes
{
	GameObject * CreateBulletArchetype(Mesh * mesh)
	{
		GameObject* bullet = new GameObject("Bullet");
		//transform
		Transform* transform = new Transform(Vector2D(0, 0), Vector2D(7, 7), 0.0f);
		bullet->AddComponent(transform);
		//Sprite
		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);
		bullet->AddComponent(sprite);
		//Physics
		Physics* physics = new Physics();
		bullet->AddComponent(physics);
		//TimedDeath
		Behaviors::TimedDeath* td = new Behaviors::TimedDeath(20.0f);
		bullet->AddComponent(td);
		//BulletMovement
		Behaviors::BulletMovement* bm = new Behaviors::BulletMovement();
		bullet->AddComponent(bm);

		return bullet;
	}

	GameObject * CreateCircle(Mesh * mesh, SpriteSource * spriteSource)
	{
		GameObject* circle = new GameObject("Circle");
		//transform
		Transform* transform = new Transform(Vector2D(0, 0), Vector2D(100, 100), 0.0f);
		circle->AddComponent(transform);
		//Sprite
		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);
		circle->AddComponent(sprite);
		//Physics
		Physics* physics = new Physics();
		physics->SetMass(1.0f);
		//physics->SetGravity(Vector2D(0, -98.0f));
		circle->AddComponent(physics);
		//ColliderPoint
		ColliderCircle* collider = new ColliderCircle(50.0f);
		circle->AddComponent(collider);
		//ColorChange
		Behaviors::ColorChange* colorChange = new Behaviors::ColorChange(Color(1, 1, 0), Color(1, 0, 0));
		circle->AddComponent(colorChange);
		//Screen Wrap
		Behaviors::ScreenWrap* screenWrap = new Behaviors::ScreenWrap();
		circle->AddComponent(screenWrap);

		return circle;
	}

	GameObject * CreatePoint(Mesh * mesh, SpriteSource * spriteSource)
	{
		GameObject* point = new GameObject("Point");
		//transform
		Transform* transform = new Transform(Vector2D(0, 0), Vector2D(20, 20), 0.0f);
		point->AddComponent(transform);
		//Sprite
		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);
		point->AddComponent(sprite);
		//Physics
		Physics* physics = new Physics();
		physics->SetMass(1.0f);
		//physics->SetGravity(Vector2D(0, -98.0f));
		point->AddComponent(physics);
		//ColliderPoint
		ColliderPoint* collider = new ColliderPoint();
		point->AddComponent(collider);
		//ColorChange
		Behaviors::ColorChange* colorChange = new Behaviors::ColorChange(Color(0, 0, 1), Color(1, 0, 0));
		point->AddComponent(colorChange);
		//Screen Wrap
		Behaviors::ScreenWrap* screenWrap = new Behaviors::ScreenWrap();
		point->AddComponent(screenWrap);

		return point;
	}

	GameObject * CreateRectangle(Mesh * mesh)
	{
		GameObject* circle = new GameObject("Circle");
		//transform
		Transform* transform = new Transform(Vector2D(0, 0), Vector2D(250, 100), 0.0f);
		circle->AddComponent(transform);
		//Sprite
		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);
		circle->AddComponent(sprite);
		//Physics
		Physics* physics = new Physics();
		physics->SetMass(1.0f);
		//physics->SetGravity(Vector2D(0, -98.0f));
		circle->AddComponent(physics);
		//ColliderPoint
		ColliderRectangle* collider = new ColliderRectangle(Vector2D(abs(transform->GetScale().x / 2), abs(transform->GetScale().y / 2)));
		circle->AddComponent(collider);
		//ColorChange
		Behaviors::ColorChange* colorChange = new Behaviors::ColorChange(Color(0, 1, 0), Color(1, 0, 0));
		circle->AddComponent(colorChange);
		//Screen Wrap
		Behaviors::ScreenWrap* screenWrap = new Behaviors::ScreenWrap();
		circle->AddComponent(screenWrap);

		return circle;
	}

	GameObject * CreateLevel1Tilemap(Mesh * mesh, SpriteSource * spriteSource, Tilemap * map)
	{
		GameObject* tileMap = new GameObject("tileMapLevel1");
		//transform
		Vector2D scale = Vector2D(50, 50);
		Transform* transform = new Transform(Vector2D(-(Graphics::GetInstance().GetScreenWorldDimensions().extents.x - (scale.x/2)), (Graphics::GetInstance().GetScreenWorldDimensions().extents.y - (scale.y / 2))), scale, 0.0f);
		tileMap->AddComponent(transform);
		//Sprite
		SpriteTilemap* sprite = new SpriteTilemap();
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);
		sprite->SetTilemap(map);
		tileMap->AddComponent(sprite);
		//Collider Tilemap
		ColliderTilemap* colliderTilemap = new ColliderTilemap();
		colliderTilemap->SetTilemap(map);
		tileMap->AddComponent(colliderTilemap);
		//Place Path Tile
		Behaviors::PlacePathTile* placePathTile = new Behaviors::PlacePathTile();
		placePathTile->SetTilemap(map);
		tileMap->AddComponent(placePathTile);
		// Place turret tile
		Behaviors::PlaceTurretTile* placeTurretTile = new Behaviors::PlaceTurretTile();
		placeTurretTile->SetTilemap(map);
		tileMap->AddComponent(placeTurretTile);

		return tileMap;
	}

	// Create a text game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object.
	GameObject* CreateText()
	{
		// Create a new game object.
		GameObject* text = new GameObject("Text");

		// Create a new transform.
		Transform* transform = new Transform(0.0f, 0.0f);
		transform->SetScale(Vector2D(64.0f, 64.0f));
		text->AddComponent(transform);

		// Create a new sprite text.
		SpriteText* spriteText = new SpriteText();
		spriteText->SetHorizontalAlignment(SpriteText::Alignment::CENTER);
		spriteText->SetVerticalAlignment(SpriteText::Alignment::CENTER);
		text->AddComponent(spriteText);

		return text;
	}

	// Create a turret game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateTurret(GameObject* projectileArchetype, Mesh* mesh, SpriteSource* spriteSource)
	{
		// Create a new game object.
		GameObject* turret = new GameObject("Turret");

		// Create a new transform.
		Transform* transform = new Transform(Vector2D(), Vector2D(50.0f, 50.0f));
		turret->AddComponent(transform);

		// Create a new sprite.
		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);
		turret->AddComponent(sprite);

		// Create a new turret AI.
		turret->AddComponent(new Behaviors::TurretAI(projectileArchetype, 200.0f, 1.5f, 175.0f));

		return turret;
	}

	// Create a turret projectile game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateTurretProjectile(Mesh* mesh, SpriteSource* spriteSource)
	{
		// Create a new game object.
		GameObject* projectile = new GameObject("TurretProjectile");

		// Create a new transform.
		Transform* transform = new Transform(Vector2D(), Vector2D(20.0f, 20.0f));
		projectile->AddComponent(transform);

		// Create a new sprite.
		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);
		projectile->AddComponent(sprite);

		// Create a new physics.
		projectile->AddComponent(new Physics());

		// Create a new circle collider.
		projectile->AddComponent(new ColliderCircle(transform->GetScale().x / 2.0f));

		// Create a new timed death.
		projectile->AddComponent(new Behaviors::TimedDeath(10.0f));

		return projectile;
	}

	GameObject * CreateEnemy(Mesh * mesh, SpriteSource * spriteSource, Vector2D translation, Vector2D scale)
	{
		GameObject* enemy = new GameObject("Enemy");
		//transform
		Transform* transform = new Transform(translation, scale, 0.0f);
		enemy->AddComponent(transform);
		//Sprite
		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);
		enemy->AddComponent(sprite);
		//Animation
		Animation* animation = new Animation();
		//animation->Play(0, 16, 0.4f, true);
		enemy->AddComponent(animation);
		//Physics
		Physics* physics = new Physics();
		physics->SetMass(1.0f);
		enemy->AddComponent(physics);
		//Box Collider
		ColliderRectangle* collider = new ColliderRectangle(Vector2D(transform->GetScale().x / 2, transform->GetScale().y / 2));
		enemy->AddComponent(collider);
		//PatrolAI
		Behaviors::PatrolAI* patrolAI = new Behaviors::PatrolAI(75.0f);
		enemy->AddComponent(patrolAI);
		//AStarPath
		Behaviors::AStarPath* aStar = new Behaviors::AStarPath();
		enemy->AddComponent(aStar);
		//Enemy
		Behaviors::Enemy* enemyComponent = new Behaviors::Enemy(2);
		enemy->AddComponent(enemyComponent);

		return enemy;
	}

	// Create a health bar game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateHealthBar(Mesh* mesh, SpriteSource* spriteSource)
	{
		// Create a new game object.
		GameObject* healthBar = new GameObject("HealthBar");

		// Create a new transform.
		Transform* transform = new Transform(Vector2D(), Vector2D(64.0f, 16.0f));
		healthBar->AddComponent(transform);

		// Create a new sprite.
		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);
		healthBar->AddComponent(sprite);

		return healthBar;
	}

	GameObject * CreateGameController()
	{
		GameObject* gameController = new GameObject("GameController");
		GameController* gc = new GameController();
		gc->SetAmountOfTiles(2);
		gc->SetAmountOfTurrets(2);
		gameController->AddComponent(gc);

		return gameController;
	}

	GameObject * CreateCity(Mesh * mesh, SpriteSource * spriteSource)
	{
		GameObject* city = new GameObject("City");
		Transform* transform = new Transform(Vector2D(100, 100), Vector2D(50,50), 0.f);
		city->AddComponent(transform);
		ColliderRectangle* collider = new ColliderRectangle(Vector2D(transform->GetScale().x / 2.f, transform->GetScale().y / 2.f));
		city->AddComponent(collider);
		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);
		city->AddComponent(sprite);
		Behaviors::City* cityComponent = new Behaviors::City(10);
		city->AddComponent(cityComponent);
		city->AddComponent(new Behaviors::HealthBar(cityComponent->GetHealth(), cityComponent->GetHealth()));
		return city;
	}
};
