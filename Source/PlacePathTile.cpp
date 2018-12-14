//------------------------------------------------------------------------------
//
// File Name:	PlacePathTile.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "PlacePathTile.h"
#include <Tilemap.h>
#include <Input.h>
#include <Vector2D.h>
#include <ColliderTilemap.h>
#include <GameObject.h>
#include <Graphics.h>
#include "GameController.h"
#include <Space.h>

Behaviors::PlacePathTile::PlacePathTile() : Component("PlacePathTile")
{
}

Component * Behaviors::PlacePathTile::Clone() const
{
	return new PlacePathTile(*this);
}

void Behaviors::PlacePathTile::Initialize()
{
	lastPathPos = Vector2D(9,2);
}

void Behaviors::PlacePathTile::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	//see if the player has clicked and has enough tiles
	if (Input::GetInstance().CheckTriggered(VK_LBUTTON) && static_cast<GameController*>(GetOwner()->GetSpace()->GetObjectManager().GetObjectByName("GameController")->GetComponent("GameController"))->GetAmountOfTiles() >= 1) {
		PlacePath(Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition()));
	}
}

void Behaviors::PlacePathTile::SetTilemap(const Tilemap * _map)
{
	map = _map;
}

void Behaviors::PlacePathTile::PlacePath(Vector2D MousePos)
{
	ColliderTilemap* CT = static_cast<ColliderTilemap*>(GetOwner()->GetComponent("Collider"));
	Vector2D tile = CT->ConvertWorldCordsToTileMapCords(MousePos);

	int tileX = static_cast<int>(tile.x);
	int tileY = static_cast<int>(tile.y);

	//if the chosen path tile is a path then return
	if (map->GetCellValue(tileX, tileY) == 1) {
		return;
	}

	//check that the chosen tile is neiboring another path
	if (map->GetCellValue(tileX, tileY + 1) == 1 || map->GetCellValue(tileX, tileY - 1) == 1 || map->GetCellValue(tileX + 1, tileY) == 1 || map->GetCellValue(tileX - 1, tileY) == 1) {
		//also check that it is next to the last path tile
		int lastPathPosX = static_cast<int>(lastPathPos.x);
		int lastPathPosY = static_cast<int>(lastPathPos.y);
		if ((lastPathPosX + 1 == tileX || lastPathPosX - 1 == tileX || lastPathPosX == tileX) && (lastPathPosY + 1 == tileY || lastPathPosY - 1 == tileY || lastPathPosY == tileY)) {
			//check that it isn't a corner
			if ((lastPathPosX + 1 == tileX || lastPathPosX - 1 == tileX) && (lastPathPosY + 1 == tileY || lastPathPosY - 1 == tileY)) {
				return;
			}
			map->SetCellValue(tileX, tileY, 1);

			//remove one from the number of tiles the player can place
			GameController* gc = static_cast<GameController*>(GetOwner()->GetSpace()->GetObjectManager().GetObjectByName("GameController")->GetComponent("GameController"));
			gc->SetAmountOfTiles(gc->GetAmountOfTiles() - 1);

			//add the point to the enemy path
			Vector2D auctualTile = Vector2D(static_cast<float>(tileX), static_cast<float>(tileY));
			gc->AddPointToEnemyPath(CT->ConvertTileMapCordsToWorldCords(auctualTile));

			//update the last path position
			lastPathPos = auctualTile;
		}	
	}

	
}
