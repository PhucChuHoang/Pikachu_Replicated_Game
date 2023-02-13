#include "Level.h"

enum GameState {
    MENU,
    PLAYING,
    PAUSE,
    GAME_OVER,
    WIN
};

class Game {
private:
    GameState gameState;
    Level* level;
    int currentLevel;
    int totalScore;
    Texture2D timeBar;
    Texture2D background;

public:
    Game();
    ~Game();
    void run();
};