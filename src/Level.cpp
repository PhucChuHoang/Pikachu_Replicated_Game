#include "Level.h"
#include <ctime>

std::vector<std::vector<int>> Level::random() {            // 0 <= random <= 32
    srand(time(0));
    std::vector<std::vector<int>> ans;
    ans.resize(TILES_HEIGHT);
    for (int i = 0; i < TILES_HEIGHT; ++i) {
        ans[i].resize(TILES_WIDTH);
    }
    for (int i = 0; i < TILES_HEIGHT; ++i) {
        for (int j = 0; j < TILES_WIDTH; ++j) {
            int typeChoose;
            do {
                typeChoose = rand() % 33;
            } while (countPerImg[typeChoose] == numbPerImg[typeChoose]);
            ans[i][j] = typeChoose;
            ++countPerImg[typeChoose];
        }
    }
    return ans;
}

Level::Level() {
    currentTime = 300;                     // 5 minutes 
    isOver = false;
    tiles.resize(TILES_HEIGHT);
    countPerImg.resize(33, 0);              // 33 images (0 - 32)
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
    tilesRect.resize(TILES_HEIGHT);
    for (int i = 0; i < TILES_HEIGHT; ++i) {
        tilesRect[i].resize(TILES_WIDTH);
    }
    for (int i = 0; i < TILES_HEIGHT; ++i) {
        for (int j = 0; j < TILES_WIDTH; ++j) {
            tilesRect[i][j] = { (float)PADDING_X + j * TILES_SIZE_WIDTH, (float)PADDING_Y + i * TILES_SIZE_HEIGHT, (float)TILES_SIZE_WIDTH, (float)TILES_SIZE_HEIGHT };
        }
    }
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
    if (checkOver()) {
        printf("Game Over\n");
        return;
    }
    if (checkWin()) {
        return;
    }
    Vector2 mousePos = { 0, 0 };
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        mousePos = GetMousePosition();
        getClick(mousePos.x, mousePos.y);
    }
}

bool Level::checkOver() {
    if (currentTime == 0) {
        isOver = true;
    }
    return isOver;
}

bool Level::checkWin() {
    return totalTiles == 0;
}

void Level::checkMatching() {
    if (tilesQueue.front()->getID() == tilesQueue.back()->getID()) {
        tilesQueue.front()->setState(TileState::Deleted);
        tilesQueue.back()->setState(TileState::Deleted);
        totalTiles -= 2;
        return;
    }
    else {
        tilesQueue.front()->setState(TileState::NotChosen);
        tilesQueue.back()->setState(TileState::NotChosen);
        return;
    }
    return;
}

void Level::getClick(int x, int y) {
    for (int i = 0; i < TILES_HEIGHT; ++i) {
        for (int j = 0; j < TILES_WIDTH; ++j) {
            if (CheckCollisionPointRec({ (float)x, (float)y }, tilesRect[i][j]) && tiles[i][j]->getState() == TileState::NotChosen) {
                tiles[i][j]->setState(TileState::Chosen);
                tilesQueue.push(tiles[i][j]);
                if (tilesQueue.size() == 2) {
                    checkMatching();
                    tilesQueue.pop();
                    tilesQueue.pop();
                }
                return;
            }
        }
    }
    return;
}