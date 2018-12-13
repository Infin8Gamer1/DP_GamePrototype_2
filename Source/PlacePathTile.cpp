#include "stdafx.h"
#include "PlacePathTile.h"
#include <Tilemap.h>
#include <Input.h>
#include <Vector2D.h>
#include <ColliderTilemap.h>
#include <GameObject.h>
#include <Graphics.h>


Behaviors::PlacePathTile::PlacePathTile() : Component("PlacePathTile")
{
}

Component * Behaviors::PlacePathTile::Clone() const
{
	return new PlacePathTile(*this);
}

void Behaviors::PlacePathTile::Initialize()
{
}

void Behaviors::PlacePathTile::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	//see if the player has clicked and has enough tiles
	if (Input::GetInstance().CheckTriggered(VK_LBUTTON)) {
		SetTileToPath(Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition()));
	}
}

void Behaviors::PlacePathTile::SetTilemap(const Tilemap * _map)
{
	map = _map;
}

void Behaviors::PlacePathTile::SetTileToPath(Vector2D MousePos)
{
	ColliderTilemap* CT = static_cast<ColliderTilemap*>(GetOwner()->GetComponent("Collider"));
	Vector2D tile = CT->ConvertWorldCordsToTileMapCords(MousePos);

	int tileX = static_cast<int>(tile.x);
	int tileY = static_cast<int>(tile.y);

	//if the chosen path tile is a path then return
	if (map->GetCellValue(tileX, tileY) == 1) {
		return;
	}

	//check if the chosen tile is neiboring another path
	if (map->GetCellValue(tileX, tileY + 1) == 1 || map->GetCellValue(tileX, tileY - 1) == 1 || map->GetCellValue(tileX + 1, tileY) == 1 || map->GetCellValue(tileX - 1, tileY) == 1) {
		map->SetCellValue(tileX, tileY, 1);

		//remove one from the number of tiles the player can place
	}

	
}
