//------------------------------------------------------------------------------
//
// File Name:	WinLevel.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
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
#include "WinLevel.h"
#include "Platformer.h"
#include <Texture.h>
#include "SpriteSource.h"

Levels::WinLevel::WinLevel() : Level("WinLevel")
{
	meshYouWinText = nullptr;
	textureText = nullptr;
	spriteSourceText = nullptr;
}

void Levels::WinLevel::Load()
{
	std::cout << "WinLevel::Load" << std::endl;

	meshYouWinText = CreateQuadMesh(Vector2D(1, 1), Vector2D(1, 1));
	textureText = Texture::CreateTextureFromFile("YouWin.png");

	spriteSourceText = new SpriteSource(1, 1, textureText);
}

void Levels::WinLevel::Initialize()
{
	std::cout << "WinLevel::Initialize" << std::endl;

	GameObject* WinTextGO = Archetypes::CreateText(meshYouWinText, spriteSourceText, Vector2D(0,0), Vector2D(500, 500));
	GetSpace()->GetObjectManager().AddObject(*WinTextGO);
}

void Levels::WinLevel::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (Input::GetInstance().CheckReleased(' ')) {
		GetSpace()->SetLevel(new Levels::Platformer);
	}
	
}

void Levels::WinLevel::Unload()
{
	std::cout << "WinLevel::Unload" << std::endl;

	delete meshYouWinText;
	meshYouWinText = nullptr;
	delete textureText;
	textureText = nullptr;
	delete spriteSourceText;
	spriteSourceText = nullptr;
}
