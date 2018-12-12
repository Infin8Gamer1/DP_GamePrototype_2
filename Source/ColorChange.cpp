//------------------------------------------------------------------------------
//
// File Name:	ColorChange.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ColorChange.h"
#include "Sprite.h"
#include "Collider.h"
#include "GameObject.h"

Behaviors::ColorChange::ColorChange(const Color & _normalColor, const Color & _collidedColor, float _collidedColorTime) : Component("ColorChange")
{
	// Components
	sprite = nullptr;

	// Properties
	normalColor = _normalColor;
	collidedColor = _collidedColor;
	collidedColorTime = _collidedColorTime;

	// Other variables
	collided = false;
	timer = 0.0f;
}

Component * Behaviors::ColorChange::Clone() const
{
	return new ColorChange(normalColor, collidedColor, collidedColorTime);
}

void Behaviors::ColorChangeCollisionHandler(GameObject & object, GameObject & other)
{
	UNREFERENCED_PARAMETER(other);
	ColorChange* objectColorChange = static_cast<ColorChange*>(object.GetComponent("ColorChange"));

	objectColorChange->collided = true;
	objectColorChange->timer = 0.0f;
}

void Behaviors::ColorChange::Initialize()
{
	sprite = static_cast<Sprite*>(GetOwner()->GetComponent("Sprite"));
	Collider* collider = static_cast<Collider*>(GetOwner()->GetComponent("Collider"));
	collider->SetCollisionHandler(ColorChangeCollisionHandler);
}

void Behaviors::ColorChange::Update(float dt)
{
	timer -= dt;
	if (collided) {
		timer = collidedColorTime;
		collided = false;
		sprite->SetColor(collidedColor);
	} else if (timer <= 0.0f) {
		sprite->SetColor(normalColor);
	}
}


