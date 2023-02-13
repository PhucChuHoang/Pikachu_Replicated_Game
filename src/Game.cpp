#include "Game.h"

Game::Game() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
    SetTargetFPS(60);
    timeBar = TexturesHolder::GetInstance().get(33);
    background = TexturesHolder::GetInstance().get(34);

    level = new Level();
    currentLevel = 1;
    totalScore = 0;
    gameState = PLAYING;
}

Game::~Game() {
    delete level;
    CloseWindow();
}

void Game::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        switch (gameState) {
            case MENU:
                break;
            case PLAYING: {
                level->update();
                level->draw();
                DrawText(TextFormat("%d", totalScore), 1050, 30, 40, BLACK);
                DrawTexturePro(timeBar, { 0, 0, (float)timeBar.width, (float)timeBar.height }, { (float)SCREEN_WIDTH / 2 - (float)timeBar.width / 2, 30, (float)timeBar.width  - (float)((420 - level->getTime())*1.67), (float)timeBar.height / 2 }, { 0, 0 }, 0, WHITE);
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
            }
            case PAUSE:
                break;
            case GAME_OVER:
                break;
            case WIN:
                break;
        }
        EndDrawing();
    }
}