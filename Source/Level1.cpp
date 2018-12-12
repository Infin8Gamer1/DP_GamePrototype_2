//------------------------------------------------------------------------------
//
// File Name:	Level1.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Level1.h"
#include "Level2.h"
#include "Space.h"
#include "MeshHelper.h"
#include "Sprite.h"
#include "Transform.h"
#include "Physics.h"
#include "Archetypes.h"
#include <Input.h>
#include <Mesh.h>
#include <Color.h>
#include <Engine.h>
#include "Level3.h"
#include "SoundManager.h"

Levels::Level1::Level1() : Level("Level1")
{
	// Meshes
	meshShip = nullptr;
	meshBullet = nullptr;

	// Sound manager
	soundManager = nullptr;
	musicChannel = nullptr;
}

void Levels::Level1::Load()
{
	std::cout << GetName() << "::Load" << std::endl;
	meshShip = CreateTriangleMesh(Color(1, 0, 0), Color(0, 1, 0), Color(0, 0, 1));
	meshBullet = CreateTriangleMesh(Color(1, 0, 0), Color(1, 0, 0), Color(1, 0, 0));

	GameObject* Bullet = Archetypes::CreateBulletArchetype(meshBullet);
	GetSpace()->GetObjectManager().AddArchetype(*Bullet);

	soundManager = Engine::GetInstance().GetModule<SoundManager>();
	soundManager->AddMusic("Asteroid_Field.mp3");
	soundManager->AddEffect("teleport.wav");

	soundManager->AddBank("Master Bank.strings.bank");
	soundManager->AddBank("Master Bank.bank");
}

void Levels::Level1::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;

	GameObject* Ship = Archetypes::CreateShip(meshShip);
	GetSpace()->GetObjectManager().AddObject(*Ship);

	musicChannel = soundManager->PlaySound("Asteroid Field");
}

void Levels::Level1::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (Input::GetInstance().CheckReleased('T')) {
		soundManager->PlaySound("teleport.wav");
	}

	if (Input::GetInstance().CheckReleased('1')) {
		GetSpace()->RestartLevel();
	}
	else if (Input::GetInstance().CheckReleased('2'))
	{
		GetSpace()->SetLevel(new Levels::Level2());
	}
	else if (Input::GetInstance().CheckReleased('3')) {
		GetSpace()->SetLevel(new Levels::Level3());
	}
}

void Levels::Level1::Shutdown()
{
	std::cout << GetName() << "::Shutdown" << std::endl;

	musicChannel->stop();
	musicChannel = nullptr;
}

void Levels::Level1::Unload()
{
	std::cout << GetName() << "::Unload" << std::endl;

	delete meshShip;
	meshShip = nullptr;
	delete meshBullet;
	meshBullet = nullptr;

	soundManager->Shutdown();
}