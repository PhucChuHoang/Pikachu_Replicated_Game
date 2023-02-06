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
    // if (tilesQueue.front()->getID() == tilesQueue.back()->getID()) {
    //     tilesQueue.front()->setState(TileState::Deleted);
    //     tilesQueue.back()->setState(TileState::Deleted);
    //     return;
    // }
    // if (tilesQueue.front()->getX() == tilesQueue.back()->getX()) {
    //     bool havePath = true;
    //     for (int i = std::min(tilesQueue.front()->getY(), tilesQueue.back()->getY()) + 1; i < std::max(tilesQueue.front()->getY(), tilesQueue.back()->getY()); ++i) {
    //         if (tiles[tilesQueue.front()->getX()][i]->getState() != Deleted) {
    //             havePath = false;
    //             break;
    //         }
    //     }
    //     if (havePath) {
    //         tilesQueue.front()->setState(TileState::Deleted);
    //         tilesQueue.back()->setState(TileState::Deleted);
    //         return;
    //     }
    // }
    // if (tilesQueue.front()->getY() == tilesQueue.back()->getY()) {
    //     bool havePath = true;
    //     for (int i = std::min(tilesQueue.front()->getX(), tilesQueue.back()->getX()) + 1; i < std::max(tilesQueue.front()->getX(), tilesQueue.back()->getX()); ++i) {
    //         if (tiles[i][tilesQueue.front()->getY()]->getState() != Deleted) {
    //             havePath = false;
    //             break;
    //         }
    //     }
    //     if (havePath) {
    //         tilesQueue.front()->setState(TileState::Deleted);
    //         tilesQueue.back()->setState(TileState::Deleted);
    //         return;
    //     }
    // }

}

void Level::bfs() { 
    // TODO: Chỉnh x y cho đúng với bảng
    // cột r mới tới hàng 
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        for (int j = 0; j < TILES_WIDTH + 2; ++j) {
            ansTable[i][j] = INF;
        }
    }
    std::deque<DequePoint> q;
    tilesQueue.front()->setState(TileState::Deleted);
    tilesQueue.back()->setState(TileState::Deleted);
    q.push_back({tilesQueue.front()->getX(), tilesQueue.front()->getY(), {0, 0}, 0});
    while(!q.empty()) {
        DequePoint current = q.front();
        q.pop_front();
        ansTable[current.x][current.y] = current.countChange;
        if (tiles[current.x][current.y]->getState() != Deleted) continue;
        for (int i = 0; i < 4; ++i) {
            if(current.x + directionX[i] >= 0 && current.y + directionY[i] >= 0 && current.x + directionY[i] < TILES_HEIGHT + 2 && current.y + directionY[i] < TILES_WIDTH + 2) {
                if (ansTable[current.x + directionX[i]][current.y +directionY[i]] != INF) continue;
                if (std::make_pair(directionX[i], directionY[i]) == current.prevDirection) {
                    q.push_front({current.x + directionX[i], current.y + directionY[i], {directionX[i], directionY[i]}, current.countChange});
                }
                else {
                    q.push_back({current.x + directionX[i], current.y + directionY[i], {directionX[i], directionY[i]}, current.countChange + 1});
                }
            }
        }
    }
    if (ansTable[tilesQueue.back()->getX()][tilesQueue.back()->getY()] > 3) {
        tilesQueue.front()->setState(TileState::NotChosen);
        tilesQueue.back()->setState(TileState::NotChosen);
    }
}

void Level::getClick(int x, int y) {
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        for (int j = 0; j < TILES_WIDTH + 2; ++j) {
            if (CheckCollisionPointRec({ (float) x, (float) y}, tilesRect[i][j]) && tiles[i][j]->getState() == TileState::NotChosen) {
                printf("X: %i, Y: %i \n", i, j);
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