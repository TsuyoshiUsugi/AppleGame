#pragma once

#include "raylib.h"
#include "Entity.h"

struct Player : public Entity
{
    void Update(float deltaTime) override;
    void Draw() const override;
    void Heal(float healPoint);
    void DecreaseHP(float deltaTime);
    bool IsDeath() const;
    void Reset();
    Player(Vector2 pos, float speed, float width, float height, float health, Texture2D texture) : Entity(pos, width, height,texture), speed(speed), health(health), originalHP(health){}
    float speed;
    float health;
    float originalHP;
    float surviveTime = 0;
    Vector2 lastDirection = { 0, 0 };
};
