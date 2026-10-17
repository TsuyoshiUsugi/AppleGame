#pragma once

#include "raylib.h"
#include "Entity.h"

struct Apple : public Entity
{
	void Update(float deltaTime) override;
	void Draw() const override;
	Apple(Vector2 pos, Vector2 velocity, float width, float height, float healPoint, bool hasEntered, Texture2D texture) : Entity(pos, width, height, texture), velocity(velocity), healPoint(healPoint), hasEntered(hasEntered){}
	Vector2 velocity;
	float healPoint;
	bool hasEntered;
	void Respawn(Vector2 centerPos, Vector2 newPos);

private:
	void BounceOffScreen();
};