#include "Game.h"

Game::Game() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
    SetTargetFPS(60);
    timeBar = TexturesHolder::GetInstance().get(static_cast<int>(TextureValue::timeBar));
    background = TexturesHolder::GetInstance().get(static_cast<int>(TextureValue::background));

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
                DrawText(TextFormat("%d", totalScore), 1100, 30, 40, BLACK);
                DrawTextureRec(timeBar, {0, 0, (float)timeBar.width - (float)((420 - level->getTime())*1.9), (float)timeBar.height - 10}, {(float)SCREEN_WIDTH / 2 - timeBar.width / 2, 30}, WHITE);
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