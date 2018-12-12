//------------------------------------------------------------------------------
//
// File Name:	Archetypes.cpp
// Author(s):	Jacob Holyfield
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

GameObject * Archetypes::CreateBulletArchetype(Mesh * mesh)
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

GameObject * Archetypes::CreateCircle(Mesh * mesh, SpriteSource * spriteSource)
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

GameObject * Archetypes::CreatePoint(Mesh * mesh, SpriteSource * spriteSource)
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
	Behaviors::ColorChange* colorChange = new Behaviors::ColorChange(Color(0,0,1), Color(1,0,0));
	point->AddComponent(colorChange);
	//Screen Wrap
	Behaviors::ScreenWrap* screenWrap = new Behaviors::ScreenWrap();
	point->AddComponent(screenWrap);

	return point;
}

GameObject * Archetypes::CreateRectangle(Mesh * mesh)
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

GameObject * Archetypes::CreateTilemapObject(Mesh * mesh, SpriteSource * spriteSource, Tilemap * map)
{
	GameObject* tileMap = new GameObject("tileMap");
	//transform
	Transform* transform = new Transform(Vector2D(-350, 250), Vector2D(100, 100), 0.0f);
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

	return tileMap;
}

GameObject * Archetypes::CreateLevel1Tilemap(Mesh * mesh, SpriteSource * spriteSource, Tilemap * map)
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

	return tileMap;
}

GameObject * Archetypes::CreateCollectable(Mesh * mesh, SpriteSource * spriteSource, Vector2D translation)
{
	GameObject* Collectable = new GameObject("Collectable");
	//transform
	Transform* transform = new Transform(translation, Vector2D(50, 50), 0.0f);
	Collectable->AddComponent(transform);
	//Sprite
	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);
	Collectable->AddComponent(sprite);
	//ColliderPoint
	ColliderCircle* collider = new ColliderCircle(transform->GetScale().x/4);
	Collectable->AddComponent(collider);

	return Collectable;
}

GameObject * Archetypes::CreateHazard(Mesh * mesh, SpriteSource * spriteSource, Vector2D translation, Vector2D scale)
{
	GameObject* Hazard = new GameObject("Hazard");
	//transform
	Transform* transform = new Transform(translation, scale, 0.0f);
	Hazard->AddComponent(transform);
	//Sprite
	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);
	Hazard->AddComponent(sprite);
	//Box Collider
	ColliderRectangle* collider = new ColliderRectangle(Vector2D(abs(transform->GetScale().x / 2.1f), abs(transform->GetScale().y / 2.1f)));
	Hazard->AddComponent(collider);

	return Hazard;
}

GameObject * Archetypes::CreateText(Mesh * mesh, SpriteSource * spriteSource, Vector2D translation, Vector2D scale)
{
	GameObject* Text = new GameObject("Text");
	//transform
	Transform* transform = new Transform(translation, scale, 0.0f);
	Text->AddComponent(transform);
	//Sprite
	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);
	Text->AddComponent(sprite);

	return Text;
}

GameObject * Archetypes::CreateEnemy(Mesh * mesh, SpriteSource * spriteSource, Vector2D translation, Vector2D scale)
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
	//animation->Play(0, 8, 0.4f, false);
	enemy->AddComponent(animation);
	//Physics
	Physics* physics = new Physics();
	physics->SetMass(1.0f);
	physics->SetGravity(Vector2D(0, -200.0f));
	enemy->AddComponent(physics);
	//Box Collider
	ColliderRectangle* collider = new ColliderRectangle(Vector2D(abs(transform->GetScale().x / 2), abs(transform->GetScale().y / 2)));
	enemy->AddComponent(collider);
	//Enemy
	Behaviors::Enemy* enemyComponent = new Behaviors::Enemy();
	enemy->AddComponent(enemyComponent);

	return enemy;
}
