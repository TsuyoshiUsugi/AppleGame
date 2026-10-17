#include "Player.h"
#include "Screen.h"
#include "Entity.h"

static Vector2 ClampToScreen(Vector2 pos, float width, float height);

 void Player::Update(float deltaTime)
{
    float currentSpeed = speed * deltaTime;

    if (IsKeyDown(KEY_RIGHT))
    {
        pos.x += currentSpeed;
        lastDirection = { -1, 0 };
    }

    if (IsKeyDown(KEY_LEFT))
    {
        pos.x -= currentSpeed;
        lastDirection = { 1, 0 };
    }

    if (IsKeyDown(KEY_UP))
    {
        pos.y -= currentSpeed;
        lastDirection = { 0, 1 };
    }

    if (IsKeyDown(KEY_DOWN))
    {
        pos.y += currentSpeed;
        lastDirection = { 0, -1 };
    }

    pos = ClampToScreen(pos, width, height);
    surviveTime += deltaTime;
    DecreaseHP(deltaTime);
 }


Vector2 ClampToScreen(Vector2 pos, float width, float height)
{
    if (pos.x < 0)
    {
        pos.x = 0;
    }

    if (pos.x > screenWidth - width)
    {
        pos.x = screenWidth - width;
    }

    if (pos.y < 0)
    {
        pos.y = 0;
    }

    if (pos.y > screenHeight - height)
    {
        pos.y = screenHeight - height;
    }

    return pos;
}

void Player::Draw() const
{
    DrawTexture(texture, pos.x, pos.y, WHITE);
}

void Player::Heal(float healPoint)
{
    health += healPoint;
}

void Player::DecreaseHP(float deltaTime)
{
    if (health <= 0)
    {
        return;
    }
    health -= deltaTime;
}

bool Player::IsDeath() const
{
    return health <= 0;
}

void Player::Reset()
{
    health = originalHP;
    surviveTime = 0;
    pos = Vector2{screenWidth / 2, screenHeight / 2};
}




