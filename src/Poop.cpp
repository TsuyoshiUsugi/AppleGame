#include "Poop.h"

void Poop::Update(float deltaTime)
{
	pos.x += velocity.x * deltaTime;
	pos.y += velocity.y * deltaTime;
}

void Poop::Draw() const
{
	DrawTexture(texture, (int)pos.x, (int)pos.y, WHITE);
}