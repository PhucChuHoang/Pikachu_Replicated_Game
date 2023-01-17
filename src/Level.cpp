#include "Level.h"
#include <ctime>

std::vector<std::vector<int>> random() {            // 0 <= random <= 32
    srand(time(0));
    std::vector<std::vector<int>> ans;
    ans.resize(TILES_HEIGHT);
    for (int i = 0; i < TILES_HEIGHT; ++i) {
        ans[i].resize(TILES_WIDTH);
    }
    for (int i = 0; i < TILES_HEIGHT; ++i) {
        for (int j = 0; j < TILES_WIDTH; ++j) {
            ans[i][j] = rand() % 33;
        }
    }
    return ans;
}

Level::Level() {
    currentTime = 300;                     // 5 minutes 
    isOver = false;
    tiles.resize(TILES_HEIGHT);
    std::vector<std::vector<int>> randomMatrix = random();
    for (int i = 0; i < TILES_HEIGHT; ++i) {
        tiles[i].resize(TILES_WIDTH);
    }
    for (int i = 0; i < TILES_HEIGHT; ++i) {
        for (int j = 0; j < TILES_WIDTH; ++j) {
            tiles[i][j] = new Tiles(randomMatrix[i][j], j, i);
        }
    }
    totalTiles = TILES_HEIGHT * TILES_WIDTH;
}

Level::~Level() {
    for (int i = 0; i < TILES_HEIGHT; ++i) {
        for (int j = 0; j < TILES_WIDTH; ++j) {
            delete tiles[i][j];
        }
    }
}

void Level::draw() {
    for (int i = 0; i < TILES_HEIGHT; ++i) {
        for (int j = 0; j < TILES_WIDTH; ++j) {
            tiles[i][j]->draw();
        }
    }
}

void Level::update() {
    currentTime--;
}