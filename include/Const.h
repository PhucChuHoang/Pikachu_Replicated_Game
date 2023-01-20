#pragma once
#include <vector>

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

extern const std::vector<int> numbPerImg;           // number of each image

enum TileState {
    NotChosen,
    Chosen,
    Deleted
};