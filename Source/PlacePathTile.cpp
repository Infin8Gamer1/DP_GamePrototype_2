#include "stdafx.h"
#include "PlacePathTile.h"
#include <Tilemap.h>
#include <Input.h>
#include <Vector2D.h>
#include <ColliderTilemap.h>
#include <GameObject.h>


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
	if (Input::GetInstance().CheckReleased(' ')) {
		SetTileToPath(Input::GetInstance().GetCursorPosition());
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

	map->SetCellValue(static_cast<int>(tile.x), static_cast<int>(tile.y), 1);
}
