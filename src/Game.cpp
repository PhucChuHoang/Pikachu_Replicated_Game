#include "Game.h"

Game::Game() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
    SetTargetFPS(60);
    timeBar = TexturesHolder::GetInstance().get(static_cast<int>(TextureValue::timeBar));
    background = TexturesHolder::GetInstance().get(static_cast<int>(TextureValue::background));

    level = new Level();
    menu = new MainMenu();
    currentLevel = 1;
    totalScore = 0;
    gameState = MENU;
}

Game::~Game() {
    if (level != nullptr) delete level;
    if (menu != nullptr) delete menu;
}

void Game::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        switch (gameState) {
            case EXIT_GAME: {
                CloseWindow();
                return;
            }
            case MENU:
                menu->update();
                menu->draw();
                if (menu->getState() == Play) {
                    gameState = PLAYING;
                    menu->setState(Menu);
                }
                else if (menu->getState() == Exit) {
                    gameState = EXIT_GAME;
                }
                break;
            case PLAYING: {
                if (level->isReturnToMenu() == true) {
                    gameState = MENU;
                    level->setReturnToMenu();
                    break;
                }
                level->update();
                level->draw();
                DrawText(TextFormat("%d", totalScore), 1100, 30, 40, BLACK);
                DrawTextureRec(timeBar, {0, 0, (float)timeBar.width - (float)((420 - level->getTime())*1.9), (float)timeBar.height / 3}, {(float)SCREEN_WIDTH / 2 - timeBar.width / 2, 50}, WHITE);
                if (level->checkOver()) {
                    gameState = GAME_OVER;
                    break;
                    //Do sth
                }
                if (level->checkWin()) {
                    ++currentLevel;
                    totalScore += (currentLevel * 10000 + level->getTime() * 100);
                    delete level;
                    level = new Level();
                    break;
                }
                break;
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