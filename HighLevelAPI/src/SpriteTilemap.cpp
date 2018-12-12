#include "stdafx.h"
#include "SpriteTilemap.h"
#include "Tilemap.h"
#include "Transform.h"
#include "Sprite.h"
#include <vector>

SpriteTilemap::SpriteTilemap()
{
	map = nullptr;
}

Component * SpriteTilemap::Clone() const
{
	return new SpriteTilemap(*this);
}

void SpriteTilemap::Draw()
{
	int height = map->GetHeight();
	int width = map->GetWidth();
	Vector2D tileScale = transform->GetScale();

	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			int cellValue = map->GetCellValue(c, r);

			//skip if this cell is empty or has an error aka it is less than or equal to 0
			if(cellValue > 0)
			{
				SetFrame(cellValue - 1);

				Sprite::Draw(Vector2D(tileScale.x * c, tileScale.y * -r));
			}
		}
	}

}

void SpriteTilemap::SetTilemap(const Tilemap * _map)
{
	map = _map;
}
