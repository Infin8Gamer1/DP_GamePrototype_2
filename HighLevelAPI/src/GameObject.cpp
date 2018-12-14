//------------------------------------------------------------------------------
//
// File Name:	GameObject.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"
#include "Space.h"

GameObject::GameObject(const std::string & name) : BetaObject(name)
{
	numComponents = 0;
	isDestroyed = false;
}

GameObject::GameObject(const GameObject & other) : BetaObject(other.GetName())
{
	numComponents = 0;

	for (unsigned i = 0; i < other.numComponents; i++)
	{
		Component* newComp = other.components[i]->Clone();

		if (newComp != nullptr) {
			AddComponent(newComp);
		}
		
	}
	
	isDestroyed = false;
}

GameObject::~GameObject()
{
	for (unsigned i = 0; i < numComponents; i++)
	{
		delete components[i];
		components[i] = nullptr;
	}
}

void GameObject::Initialize()
{
	for (unsigned i = 0; i < numComponents; i++)
	{
		components[i]->Initialize();
	}
}

void GameObject::Update(float dt)
{
	for (unsigned i = 0; i < numComponents; i++)
	{
		components[i]->Update(dt);
	}
}

void GameObject::FixedUpdate(float dt)
{
	for (unsigned i = 0; i < numComponents; i++)
	{
		components[i]->FixedUpdate(dt);
	}
}

void GameObject::Draw()
{
	for (unsigned i = 0; i < numComponents; i++)
	{
		components[i]->Draw();
	}
}

void GameObject::AddComponent(Component* component)
{
	component->SetParent(this);
	components[numComponents] = component;
	numComponents++;
}

Component* GameObject::GetComponent(const std::string & _name)
{
	for (unsigned i = 0; i < numComponents; i++)
	{
		if (components[i]->GetName() == _name)
		{
			return components[i];
		}
	}
	//std::cout << "No component with the name " + _name + " was found!" << std::endl;
	return nullptr;
}

void GameObject::Destroy()
{
	isDestroyed = true;
}

bool GameObject::IsDestroyed() const
{
	return isDestroyed;
}

Space * GameObject::GetSpace() const
{
	return static_cast<Space*>(GetParent());
}
