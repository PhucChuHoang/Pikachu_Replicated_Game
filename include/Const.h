#pragma once
#include <vector>
#include <utility>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const char* TEXTURES_PATH;
extern const char* GAME_NAME;

extern const int TILES_WIDTH;
extern const int TILES_HEIGHT;

extern const int TILES_SIZE_WIDTH;
extern const int TILES_SIZE_HEIGHT;

extern const int PADDING_X;
extern const int PADDING_Y;

extern const int INF;

extern const std::vector<int> numbPerImg;           // number of each image

extern const int directionX[4];
extern const int directionY[4];

enum GameState {
    MENU,
    PLAYING,
    PAUSE,
    GAME_OVER,
    WIN,
    EXIT_GAME
};

enum MenuState {
    Menu, 
    Exit, 
    Play, 
    Settings,
};

enum TileState {
    NotChosen,
    Chosen,
    Deleted, 
    Suggest,
};

enum TextureValue {
    timeBar = 33,
    pauseButton = 34,
    resumeButton = 35,
    background = 36,
    shuffleButton = 37,
    suggestButton = 38,
    playButton = 39,
    settingsButton = 40,
    exitButton = 41,
    gameName = 42,
    returnButton = 43,
};