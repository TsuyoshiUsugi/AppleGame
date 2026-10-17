#pragma once

#include "raylib.h"

class Entity
{
public:
	virtual ~Entity() = default;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;
	Rectangle GetBounds() const;
	Vector2 GetPos() const { return pos; }

protected:
	Entity(Vector2 pos, float width, float height, Texture2D texture) : pos(pos), width(width), height(height), texture(texture){}
	Vector2 pos = { 0, 0 };
	float width = 10;
	float height = 10;
	Texture2D texture;
};