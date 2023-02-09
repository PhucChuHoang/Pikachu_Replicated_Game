#include "Game.h"

Game::Game() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
    SetTargetFPS(60);
    timeBar = TexturesHolder::GetInstance().get(33);

    level = new Level();
    currentLevel = 1;
    totalScore = 0;
}

Game::~Game() {
    delete level;
    CloseWindow();
}

void Game::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        level->update();
        level->draw();
        DrawText(TextFormat("%d", totalScore), 1100, 20, 40, BLACK);
        DrawTexturePro(timeBar, { 0, 0, (float)timeBar.width, (float)timeBar.height }, { (float)SCREEN_WIDTH / 2 - (float)timeBar.width / 2, 10, (float)timeBar.width  - (float)((420 - level->getTime())*1.67), (float)timeBar.height }, { 0, 0 }, 0, WHITE);
        if (level->checkOver()) {
            printf("Game Over\n");
            //Do sth
        }
        if (level->checkWin()) {
            ++currentLevel;
            totalScore += (currentLevel * 10000 + level->getTime() * 100);
            delete level;
            level = new Level();
        }
        EndDrawing();
    }
}