#pragma once

#include "raylib.h"
#include "Entity.h"

struct Poop : public Entity
{
	void Update(float deltaTime) override;
	void Draw() const override;
	Poop(Vector2 pos, float width, float height, float damagePoint, Texture2D texture) : Entity(pos, width, height, texture), damagePoint(damagePoint), velocity({0, 0}) {}
	float damagePoint;
	Vector2 velocity;
};