#include "Apple.h"
#include "raymath.h"
#include "Screen.h"


void Apple::Update(float deltaTime)
{
    pos.x += velocity.x * deltaTime;
    pos.y += velocity.y * deltaTime;

    if (!hasEntered)
    {

    }
    else
    {
        BounceOffScreen();
    }
}

void Apple::Respawn(Vector2 centerPos, Vector2 newPos)
{
    pos = newPos;
    velocity = Vector2Normalize(centerPos - newPos) * Vector2Length(velocity);
}

void Apple::BounceOffScreen()
{
    if (pos.x < 0)
    {
        pos.x = 0;
        velocity.x *= -1;
    }

    if (pos.x > screenWidth - width)
    {
        pos.x = screenWidth - width;
        velocity.x *= -1;
    }

    if (pos.y < 0)
    {
        pos.y = 0;
        velocity.y *= -1;
    }

    if (pos.y > screenHeight - height)
    {
        pos.y = screenHeight - height;
        velocity.y *= -1;
    }
}

void Apple::Draw() const
{
    DrawTexture(texture, (int)pos.x, (int)pos.y, WHITE);
}
