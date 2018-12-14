#include "stdafx.h"
#include "AStarPath.h"
#include "PatrolAI.h"
#include <Transform.h>

Behaviors::AStarPath::AStarPath() : Component("AStarPath")
{
}

Component * Behaviors::AStarPath::Clone() const
{
	return new AStarPath(*this);
}

void Behaviors::AStarPath::Initialize()
{
}

void Behaviors::AStarPath::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}
