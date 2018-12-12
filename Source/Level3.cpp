//------------------------------------------------------------------------------
//
// File Name:	Level3.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Level3.h"
#include "MeshHelper.h"
#include "SpriteSource.h"
#include "Archetypes.h"
#include "GameObject.h"
#include "Physics.h"
#include "Space.h"
#include <Texture.h>
#include <Mesh.h>
#include <Input.h>
#include "Level1.h"
#include "Level2.h"

Levels::Level3::Level3() : Level("Level3")
{
	// Resources
	meshQuad = nullptr;
	spriteSourceCircle = nullptr;
	textureCircle = nullptr;

	// Properties
	circleSpeed = 45.0f;
	pointSpeed = 100.0f;
}

void Levels::Level3::Load()
{
	std::cout << "Level3::Load" << std::endl;
	meshQuad = CreateQuadMesh(Vector2D(1, 1), Vector2D(1, 1));

	textureCircle = Texture::CreateTextureFromFile("Circle.png");

	spriteSourceCircle = new SpriteSource(1, 1, textureCircle);
}

void Levels::Level3::Initialize()
{
	std::cout << "Level3::Initialize" << std::endl;

	GameObject* circle1 = Archetypes::CreateCircle(meshQuad, spriteSourceCircle);
	GetSpace()->GetObjectManager().AddObject(*circle1);

	GameObject* point = Archetypes::CreatePoint(meshQuad, spriteSourceCircle);
	static_cast<Physics*>(point->GetComponent("Physics"))->SetVelocity(Vector2D(0, -500));
	GetSpace()->GetObjectManager().AddObject(*point);

	GameObject* rectangle = Archetypes::CreateRectangle(meshQuad);
	static_cast<Physics*>(rectangle->GetComponent("Physics"))->SetVelocity(Vector2D(200, 200));
	GetSpace()->GetObjectManager().AddObject(*rectangle);

	GameObject* rectangle2 = Archetypes::CreateRectangle(meshQuad);
	static_cast<Physics*>(rectangle2->GetComponent("Physics"))->SetVelocity(Vector2D(-200, 400));
	GetSpace()->GetObjectManager().AddObject(*rectangle2);

	GameObject* circle2 = Archetypes::CreateCircle(meshQuad, spriteSourceCircle);
	static_cast<Physics*>(circle2->GetComponent("Physics"))->SetVelocity(Vector2D(400, 100));
	GetSpace()->GetObjectManager().AddObject(*circle2);
}

void Levels::Level3::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (Input::GetInstance().CheckReleased('1')) {
		GetSpace()->SetLevel(new Levels::Level1());
	}
	else if (Input::GetInstance().CheckReleased('2'))
	{
		GetSpace()->SetLevel(new Levels::Level2());
	}
	else if (Input::GetInstance().CheckReleased('3')) {
		GetSpace()->RestartLevel();
	}
}

void Levels::Level3::Unload()
{
	std::cout << "Level3::Unload" << std::endl;

	delete meshQuad;
	meshQuad = nullptr;
	delete spriteSourceCircle;
	spriteSourceCircle = nullptr;
	delete textureCircle;
	textureCircle = nullptr;
}
