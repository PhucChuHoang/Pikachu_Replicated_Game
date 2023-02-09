#include "Game.h"

Game::Game() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
    SetTargetFPS(60);


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
        if (level->checkOver()) {
            printf("Game Over\n");
            //Do sth
            return;
        }
        if (level->checkWin()) {
            ++currentLevel;
            totalScore += 10000;
            level = new Level();
            printf("Next Level\n");
            //Do sth
            return;
        }
        level->draw();
        EndDrawing();
    }
}