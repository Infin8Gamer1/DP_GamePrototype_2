//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "SpriteSource.h"
#include <Vector2D.h>

SpriteSource::SpriteSource(int numColsInput, int numRowsInput, Texture * textureInput)
{
	numRows = numRowsInput;
	numCols = numColsInput;
	texture = textureInput;
}

Texture * SpriteSource::GetTexture() const
{
	return texture;
}

unsigned SpriteSource::GetFrameCount() const
{
	return numRows * numCols;
}

void SpriteSource::GetUV(unsigned int frameIndex, Vector2D & textureCoords) const
{
	float k_X = 1.0f / static_cast<float>(numCols);
	float k_Y = 1.0f / static_cast<float>(numRows);

	float xOffset = k_X * (frameIndex % numCols);
	float yOffset = k_Y * (frameIndex / numCols);

	textureCoords = Vector2D(xOffset, yOffset);
}
