#include "raylib.h"
#include "raymath.h"
#include "Screen.h"
#include "Player.h"
#include "Apple.h"
#include "Texture.h"
#include "Poop.h"
#include <vector>
#include <algorithm>
#include <random>
#include <array>

enum class GameState
{
    Start,
    Playing,
    GameOver,
};

int main()
{
    //システム設定
    InitWindow(screenWidth, screenHeight, "raylib practice");
    std::mt19937 rng(std::random_device{}());
    GameState currentState = GameState::Start;
    SetTargetFPS(60);

    //プレイヤー設定
    TextureResource playerTex = TextureResource("resources/player.png");
    constexpr float playerSpeed = 100;
    constexpr float playerWidth = 20;
    constexpr float playerHeight = 20;
    constexpr float playerHealth = 10;
    Player player(Vector2{screenWidth / 2, screenHeight / 2}, playerSpeed, playerWidth, playerHeight, playerHealth, playerTex.tex);

    //リンゴ設定
    std::vector<Apple> apples;
    constexpr float appleWidth = 10;
    constexpr float appleHeight = 10;
    constexpr float appleHealPoint = 10;
    constexpr Vector2 screenCenter = { screenWidth / 2.0f, screenHeight / 2.0f };
    constexpr std::array<float, 4> eachDirSpawnPos = 
    {
        100,
        100,
        100,
        100
    };

    TextureResource appleTex = TextureResource("resources/apple.png");
    apples.push_back(Apple(Vector2{ 100, 100 }, Vector2{ -100, 100 }, appleWidth, appleHeight, appleHealPoint, true, appleTex.tex));
    apples.push_back(Apple(Vector2{ -200, 200 }, Vector2{ -200, 200 }, appleWidth, appleHeight, appleHealPoint, true, appleTex.tex));
    apples.push_back(Apple(Vector2{ 300, -300 }, Vector2{ 300, -300 }, appleWidth, appleHeight, appleHealPoint, true, appleTex.tex));
    std::uniform_real_distribution<float> distX(0, screenWidth - appleWidth);
    std::uniform_real_distribution<float> distY(0, screenHeight - appleHeight);
    std::uniform_int_distribution<int> spawnPosIndex(0, 3);

    //ウンコ設定
    std::vector<Poop> poops;
    TextureResource poopTex = TextureResource("resources/poop.png");
    constexpr float poopWidth = 10;
    constexpr float poopHeight = 10;
    constexpr float poopDmage = 15;
    constexpr float poopSpawnDur = 10;
    constexpr float poopGenerateLength = 50;
    float currentSpawnTimer = 0;
    
    //UI設定
    constexpr int fontSize = 20;
    constexpr int textHeight = 20;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentState == GameState::Start)
        {
            if (IsKeyDown(KEY_ENTER))
            {
                currentState = GameState::Playing;
            }

            const char* startText = TextFormat("Press Enter To Start");
            DrawText(startText, screenWidth / 2 - MeasureText(startText, fontSize) / 2, screenHeight / 2, fontSize, DARKGRAY);
        }
        else if (currentState == GameState::Playing)
        {
            float elapsedTime = GetFrameTime();

            //プレイヤーの更新
            player.Update(elapsedTime);

            if (player.IsDeath())
            {
                currentState = GameState::GameOver;
            }

            //リンゴの更新
            for (Apple& a : apples)
            {
                a.Update(elapsedTime);

                if (CheckCollisionRecs(a.GetBounds(), player.GetBounds()))
                {
                    int spawnDir = spawnPosIndex(rng);
                    auto spanwPos = Vector2{ 0, 0 };
                    if (spawnDir == 0) //上
                    {
                        spanwPos = Vector2{ distX(rng), 0 - eachDirSpawnPos[spawnDir] };
                    }
                    else if (spawnDir == 1) //下
                    {
                        spanwPos = Vector2{ distX(rng), screenHeight + eachDirSpawnPos[spawnDir] };
                    }
                    else if (spawnDir == 2) //左
                    {
                        spanwPos = Vector2{ 0 - eachDirSpawnPos[spawnDir] , distY(rng) };
                    }
                    else //右
                    {
                        spanwPos = Vector2{ screenWidth + eachDirSpawnPos[spawnDir] , distY(rng) };
                    }

                    a.Respawn(screenCenter, spanwPos);
                    player.Heal(a.healPoint);
                }
            }

            //ウンコの更新
            currentSpawnTimer += elapsedTime;

            if (currentSpawnTimer >= poopSpawnDur)
            {
                currentSpawnTimer = 0;

                Poop poop = Poop(player.GetPos() + player.lastDirection * poopGenerateLength, poopWidth, poopHeight, poopDmage, poopTex.tex);
                poops.push_back(poop);
            }

            for (auto it = poops.begin(); it != poops.end(); )
            {
                it->Update(elapsedTime);

                if (CheckCollisionRecs(it->GetBounds(), player.GetBounds()))
                {
                    player.DecreaseHP(it->damagePoint);
                    it = poops.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            //各描画処理
            player.Draw();
            for (const Apple& a : apples)
            {
                a.Draw();
            }

            for (const Poop& p : poops)
            {
                p.Draw();
            }

            DrawText(TextFormat("Health Remain: %.2f", player.health), 10, 10, fontSize, DARKGRAY);

        }
        else
        {
            if (IsKeyDown(KEY_ENTER))
            {
                player.Reset();
                currentState = GameState::Playing;
            }

            const char* gameOverText = TextFormat("GAME OVER");
            DrawText(gameOverText, screenWidth / 2 - MeasureText(gameOverText, fontSize) /2 , screenHeight / 2, fontSize, DARKGRAY);
            const char* resultText = TextFormat("RESULT : %.2f", player.surviveTime);
            DrawText(resultText, screenWidth / 2 - MeasureText(resultText, fontSize) / 2, screenHeight / 2 + textHeight, fontSize, DARKGRAY);
            const char* restartText = TextFormat("Press Enter To Restart");
            DrawText(restartText, screenWidth / 2 - MeasureText(restartText, fontSize) / 2, screenHeight / 2 + textHeight * 2, fontSize, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}


