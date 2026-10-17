#pragma once

#include "raylib.h"

class TextureResource
{
public:
	explicit TextureResource(const char* fileName) : tex(LoadTexture(fileName)) {}
	~TextureResource() { UnloadTexture(tex); }

	TextureResource(const TextureResource&) = delete;
	TextureResource& operator=(const TextureResource&) = delete;

	Texture2D tex;
};