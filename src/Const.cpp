#include "Const.h"

const int SCREEN_WIDTH = 1250;
const int SCREEN_HEIGHT = 900;

const char* TEXTURES_PATH = "assets/images/pokemon/";
const char* GAME_NAME = "Pokemon Matching Game";

const int TILES_WIDTH = 16;
const int TILES_HEIGHT = 9;

const int TILES_SIZE_WIDTH = 53;
const int TILES_SIZE_HEIGHT = 65;

const int PADDING_X = 150;
const int PADDING_Y = 100;

const std::vector<int> numbPerImg = { 4, 4, 6, 4, 4, 
                                      4, 4, 4, 6, 4, 
                                      4, 6, 4, 4, 4, 
                                      4, 4, 4, 6, 4, 
                                      4, 6, 4, 4, 4, 
                                      4, 4, 4, 6, 4, 
                                      4, 4, 4};

const int directionX[4] = {1, -1, 0, 0};
const int directionY[4] = {0, 0, 1, -1};

const int INF = 100000;