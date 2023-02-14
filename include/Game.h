#pragma once
#include "Level.h"
#include "MainMenu.h"

class Game {
private:
    GameState gameState;
    Level* level;
    MainMenu* menu;
    int currentLevel;
    int totalScore;
    Texture2D timeBar;
    Texture2D background;

public:
    Game();
    ~Game();
    void run();
};