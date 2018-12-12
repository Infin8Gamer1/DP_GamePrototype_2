//------------------------------------------------------------------------------
//
// File Name:	TurretAI.cpp
// Author(s):	David Cohen	
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "TurretAI.h"

#include <GameObject.h>

namespace Behaviors
{
	TurretAI::TurretAI(float projectileDelay_) : Component("TurretAI"), projectileDelay(projectileDelay_), projectileTimer(0.0f)
	{
	}

	Component * TurretAI::Clone() const
	{
		return new TurretAI(*this);
	}

	void TurretAI::Update(float dt)
	{
		projectileTimer = max(0.0f, projectileTimer - dt);
	}
};
