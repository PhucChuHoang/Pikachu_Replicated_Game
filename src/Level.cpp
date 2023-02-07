#include "Level.h"
#include <ctime>

std::vector<std::vector<int>> Level::random() {            // 0 <= random <= 32
    std::vector<std::vector<int>> ans;
    ans.resize(TILES_HEIGHT + 2);
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        ans[i].resize(TILES_WIDTH + 2);
    }
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        for (int j = 0; j < TILES_WIDTH + 2; ++j) {
            if (i == 0 || i == TILES_HEIGHT + 1 || j == 0 || j == TILES_WIDTH + 1) {
                ans[i][j] = 32;                             // 32 is the image of the border
                continue;
            }
            int typeChoose;
            do {
                typeChoose = GetRandomValue(0, 32);
            } while (countPerImg[typeChoose] == numbPerImg[typeChoose]);
            ans[i][j] = typeChoose;
            ++countPerImg[typeChoose];
        }
    }
    return ans;
}

void Level::createMap() {
    countPerImg.resize(33, 0);              // 33 images (0 - 32) 
    std::vector<std::vector<int>> randomMatrix = random();
    tiles.resize(TILES_HEIGHT + 2);
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        tiles[i].resize(TILES_WIDTH + 2);
    }
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        for (int j = 0; j < TILES_WIDTH + 2; ++j) {
            tiles[i][j] = new Tiles(randomMatrix[i][j], j, i);
            if (i == 0 || i == TILES_HEIGHT + 1 || j == 0 || j == TILES_WIDTH + 1) {
                tiles[i][j]->setState(Deleted);
            }
        }
    }

    tilesRect.resize(TILES_HEIGHT + 2);
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        tilesRect[i].resize(TILES_WIDTH + 2);
    }
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        for (int j = 0; j < TILES_WIDTH + 2; ++j) {
            tilesRect[i][j] = { (float)PADDING_X + (j) * TILES_SIZE_WIDTH, (float)PADDING_Y + (i) * TILES_SIZE_HEIGHT, (float)TILES_SIZE_WIDTH, (float)TILES_SIZE_HEIGHT };
        }
    }
}

Level::Level() {
    currentTime = 300;                      // 5 minutes 
    isOver = false;              
    totalTiles = TILES_HEIGHT * TILES_WIDTH;
    createMap();
}

Level::~Level() {
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        for (int j = 0; j < TILES_WIDTH + 2; ++j) {
            delete tiles[i][j];
        }
    }
}

void Level::draw() {
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        for (int j = 0; j < TILES_WIDTH + 2; ++j) {
            tiles[i][j]->draw();
        }
    }
}

void Level::update() {
    if (checkOver()) {
        printf("Game Over\n");
        //Do sth
        return;
    }
    if (checkWin()) {
        printf("Win\n");
        //Do sth
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
    if (tilesQueue.front()->getID() != tilesQueue.back()->getID()) {
        tilesQueue.front()->setState(TileState::NotChosen);
        tilesQueue.back()->setState(TileState::NotChosen);
        return;
    }
    bfs();
}

void Level::bfs() { 
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        for (int j = 0; j < TILES_WIDTH + 2; ++j) {
            ansTable[i][j] = INF;
        }
    }
    std::queue<std::pair<int, int>> q;
    tilesQueue.front()->setState(TileState::Deleted);
    tilesQueue.back()->setState(TileState::Deleted);
    ansTable[tilesQueue.front()->getY()][tilesQueue.front()->getX()] = 0;
    q.push({tilesQueue.front()->getX(), tilesQueue.front()->getY()});
    while(!q.empty()) {
        auto current = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            for (
                int x = current.first + directionX[i], y = current.second + directionY[i], val = ansTable[current.second][current.first] + 1; 
                x >= 0 && y >= 0 && y < TILES_HEIGHT + 2 && x < TILES_WIDTH + 2;
                x += directionX[i], y += directionY[i]){
                if (ansTable[y][x] < val || tiles[y][x]->getState() != Deleted){
                    break;
                }
                ansTable[y][x] = val;
                q.push({x, y});
            }
        }
    }
    printf("ansTable: %i\n", ansTable[tilesQueue.back()->getY()][tilesQueue.back()->getX()]);
    if (ansTable[tilesQueue.back()->getY()][tilesQueue.back()->getX()] > 3) {
        tilesQueue.front()->setState(TileState::NotChosen);
        tilesQueue.back()->setState(TileState::NotChosen);
    }
}

void Level::getClick(int x, int y) {
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        for (int j = 0; j < TILES_WIDTH + 2; ++j) {
            if (CheckCollisionPointRec({ (float) x, (float) y}, tilesRect[i][j]) && tiles[i][j]->getState() == TileState::NotChosen) {
                printf("X: %i, Y: %i \n", tiles[i][j] -> getX(), tiles[i][j] -> getY());
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