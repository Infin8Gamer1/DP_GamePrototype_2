//------------------------------------------------------------------------------
//
// File Name:	PlaceTurretTile.cpp
// Author(s):	David Cohen (david.cohen)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "PlaceTurretTile.h"

// Systems
#include <Input.h>
#include <GameObject.h>
#include <Graphics.h>
#include <Space.h>

// Components
#include <Transform.h>
#include <Tilemap.h>
#include <ColliderTilemap.h>
#include "GameController.h"

namespace Behaviors
{
	PlaceTurretTile::PlaceTurretTile() : Component("PlaceTurretTile")
	{
	}

	Component* PlaceTurretTile::Clone() const
	{
		return new PlaceTurretTile(*this);
	}

	void PlaceTurretTile::Initialize()
	{
		gameController = static_cast<GameController*>(GetOwner()->GetSpace()->GetObjectManager().GetObjectByName("GameController")->GetComponent("GameController"));
	}

	void PlaceTurretTile::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		//see if the player has clicked and has enough tiles
		if (Input::GetInstance().CheckTriggered(VK_RBUTTON) && gameController->GetAmountOfTurrets() >= 1) {
			PlaceTurret(Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition()));
		}
	}

	void PlaceTurretTile::SetTilemap(const Tilemap* map_)
	{
		map = map_;
	}

	void PlaceTurretTile::PlaceTurret(Vector2D mousePos)
	{
		ColliderTilemap* colliderTilemap = static_cast<ColliderTilemap*>(GetOwner()->GetComponent("Collider"));
		Vector2D tile = colliderTilemap->ConvertWorldCordsToTileMapCords(mousePos);

		int tileX = static_cast<int>(tile.x);
		int tileY = static_cast<int>(tile.y);

		//if the chosen path tile is a path then return
		if (map->GetCellValue(tileX, tileY) <= 2) {
			return;
		}

		GameObjectManager& objectManager = GetOwner()->GetSpace()->GetObjectManager();

		std::vector<GameObject*> turrets = objectManager.GetAllObjectsByName("Turret");
		for (GameObject* turret : turrets)
		{
			Vector2D turretTileCoords = colliderTilemap->ConvertWorldCordsToTileMapCords(static_cast<Transform*>(turret->GetComponent("Transform"))->GetTranslation());
			if (tile.Distance(turretTileCoords) <= 25.0f)
				return;
		}

		GameObject* turret = objectManager.GetArchetypeByName("Turret");
		static_cast<Transform*>(turret->GetComponent("Transform"))->SetTranslation(colliderTilemap->ConvertTileMapCordsToWorldCords(tile));
		objectManager.AddObject(*turret);

		// Decrement the number of turrets the player can place.
		gameController->SetAmountOfTurrets(gameController->GetAmountOfTurrets() - 1);
	}
};
