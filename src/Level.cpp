#include "Level.h"
#include <ctime>

int random() {
    srand(time(NULL));
    return rand() % 33 + 1;                // 1 <= random <= 34
}

Level::Level() {
    currentTime = 300;                     // 5 minutes 
    isOver = false;
    tiles.resize(TILES_HEIGHT);
    for (int i = 0; i < TILES_HEIGHT; ++i) {
        tiles[i].resize(TILES_WIDTH);
    }
    for (int i = 0; i < TILES_HEIGHT; ++i) {
        for (int j = 0; j < TILES_WIDTH; ++j) {
            tiles[i][j] = new Tiles(random(), j, i);
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