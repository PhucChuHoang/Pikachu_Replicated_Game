#include "Level.h"

enum class GameState {
    MENU,
    PLAYING,
    PAUSE,
    GAME_OVER,
    WIN
};

class Game {
private:
    Level* level;
    int currentLevel;
    int totalScore;

public:
    Game();
    ~Game();
    void run();
};