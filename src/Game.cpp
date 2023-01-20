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
        level->draw();
        EndDrawing();
    }
}