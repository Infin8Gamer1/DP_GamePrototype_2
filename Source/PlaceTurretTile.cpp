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
		
	}

	void PlaceTurretTile::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		GameController* gc = static_cast<GameController*>(GetOwner()->GetSpace()->GetObjectManager().GetObjectByName("GameController")->GetComponent("GameController"));

		//see if the player has clicked and has enough tiles
		if (Input::GetInstance().CheckTriggered(VK_RBUTTON) && gc->GetAmountOfTurrets() >= 1) {
			PlaceTurret(Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition()));
		}
	}

	void PlaceTurretTile::SetTilemap(const Tilemap* map_)
	{
		map = map_;
	}

	void PlaceTurretTile::PlaceTurret(Vector2D mousePos)
	{
		GameController* gameController = static_cast<GameController*>(GetOwner()->GetSpace()->GetObjectManager().GetObjectByName("GameController")->GetComponent("GameController"));

		ColliderTilemap* colliderTilemap = static_cast<ColliderTilemap*>(GetOwner()->GetComponent("Collider"));
		Vector2D tile = colliderTilemap->ConvertWorldCordsToTileMapCords(mousePos);

		int tileX = static_cast<int>(tile.x);
		int tileY = static_cast<int>(tile.y);

		//if the chosen path tile is a hill/mountian then return
		if (map->GetCellValue(tileX, tileY) > 2) {
			return;
		}

		Vector2D worldTile = colliderTilemap->ConvertTileMapCordsToWorldCords(Vector2D(static_cast<float>(tileX), static_cast<float>(tileY)));

		GameObjectManager& objectManager = GetOwner()->GetSpace()->GetObjectManager();

		std::vector<GameObject*> turrets = objectManager.GetAllObjectsByName("Turret");
		for (GameObject* turret : turrets)
		{
			Vector2D turretTileCoords = colliderTilemap->ConvertWorldCordsToTileMapCords(static_cast<Transform*>(turret->GetComponent("Transform"))->GetTranslation());
			turretTileCoords = Vector2D(floor(turretTileCoords.x), floor(turretTileCoords.y));
			if (Vector2D(static_cast<float>(tileX), static_cast<float>(tileY)).Distance(turretTileCoords) < 1.0f) {
				return;
			}
		}

		GameObject* turret = new GameObject(*objectManager.GetArchetypeByName("Turret"));
		static_cast<Transform*>(turret->GetComponent("Transform"))->SetTranslation(Vector2D(worldTile.x + 0.5f, worldTile.y + 0.5f));
		objectManager.AddObject(*turret);

		// Decrement the number of turrets the player can place.
		gameController->SetAmountOfTurrets(gameController->GetAmountOfTurrets() - 1);
	}
};
