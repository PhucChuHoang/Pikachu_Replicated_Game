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
            if (i == 0 || i == TILES_HEIGHT + 1 || j == 0 || j == TILES_WIDTH + 1) {    //Create a border
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
    currentTime = 420;                      // 7 minutes 
    isOver = false;              
    totalTiles = TILES_HEIGHT * TILES_WIDTH;
    countFrame = 0;
    isPause = false;
    numbShuffle = 3;
    numbSuggest = 3;
    isReturn = false;
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
    if (!isPause) {
        DrawTexture(pauseButton, 1120, 250, {251,202,206,255});
    }
    else {
        DrawTexture(resumeButton, 1120, 250, {251,202,206,255});
    }
    DrawTexture(shuffleButton, 1120, 400, {251,202,206,255});
    DrawText(TextFormat("%d", numbShuffle), 1182, 385, 30, BLACK);
    DrawTexture(suggestButton, 1120, 550, {251,202,206,255});
    DrawText(TextFormat("%d", numbSuggest), 1182, 535, 30, BLACK);
    DrawTexture(returnButton, 20, 30, {251,202,206,255});
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        for (int j = 0; j < TILES_WIDTH + 2; ++j) {
            tiles[i][j]->draw();
        }
    }
}

void Level::update() {
    Vector2 mousePos = { 0, 0 };
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        mousePos = GetMousePosition();
    }
    if (CheckCollisionPointRec(mousePos, pauseButtonRect)) {
        isPause = !isPause;
        return;
    }
    else if (CheckCollisionPointRec(mousePos, returnButtonRect)) {
        isReturn = true;
        return;
    }
    else if (isPause) {
        return;
    }
    else if (CheckCollisionPointRec(mousePos, shuffleButtonRect)) {
        if (numbShuffle != 0) {
            shuffle();
            --numbShuffle;
        }
        return;
    }
    else if (CheckCollisionPointRec(mousePos, suggestButtonRect)) {
        if (numbSuggest != 0) {
            --numbSuggest;
            isPossibleMoves(true);
        }
        return;
    }
    ++countFrame;
    if (countFrame == 60) {
        --currentTime;
        countFrame = 0;
    }
    getClick(mousePos.x, mousePos.y);
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

bool Level::checkMatching() {
    if (tilesQueue.front()->getID() != tilesQueue.back()->getID()) {
        tilesQueue.front()->setState(TileState::NotChosen);
        tilesQueue.back()->setState(TileState::NotChosen);
        return false;
    }
    bfs();
    if (tilesQueue.front()->getState() == Deleted || tilesQueue.back()->getState() == Deleted) {
        totalTiles -= 2;
        tilesQueue.pop();
        tilesQueue.pop();
        if (isPossibleMoves(false) != true) {
            shuffle();
        }
        return true;
    }
    return false;
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
    if (ansTable[tilesQueue.back()->getY()][tilesQueue.back()->getX()] > 3) {
        tilesQueue.front()->setState(TileState::NotChosen);
        tilesQueue.back()->setState(TileState::NotChosen);
    }
}

void Level::getClick(int x, int y) {
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        for (int j = 0; j < TILES_WIDTH + 2; ++j) {
            if (CheckCollisionPointRec({ (float) x, (float) y}, tilesRect[i][j])) {
                if (tiles[i][j]->getState() == Deleted) {
                    return;
                }
                if (tiles[i][j]->getState() == NotChosen || tiles[i][j]->getState() == Suggest) {
                    tiles[i][j]->setState(TileState::Chosen);
                }
                else if (tiles[i][j]->getState() == Chosen){
                    tiles[i][j]->setState(TileState::NotChosen);
                    tilesQueue.pop();
                    return;
                }
                tilesQueue.push(tiles[i][j]);
                if (tilesQueue.size() == 2) {
                    if (checkMatching()) {
                        return;
                    }
                    tilesQueue.pop();
                    tilesQueue.pop();
                }
                return;
            }
        }
    }
    return;
}

bool Level::isPossibleMoves(bool isSuggest) {
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        for (int j = 0; j < TILES_WIDTH + 2; ++j) {
            if (tiles[i][j] -> getState() == Deleted) {
                continue;
            }
            for (int k = 0; k < TILES_HEIGHT + 2; ++k) {
                for (int l = 0; l < TILES_WIDTH + 2; ++l) {
                    if (tiles[k][l] -> getState() == Deleted) {
                        continue;
                    }
                    if (tiles[i][j] -> getID() != tiles[k][l] -> getID() || (i == k && j == l)) {
                        continue;
                    }
                    tilesQueue.push(tiles[i][j]);
                    tilesQueue.push(tiles[k][l]);
                    bfs();
                    if (tilesQueue.front()->getState() == Deleted || tilesQueue.back()->getState() == Deleted) {
                        if (isSuggest) {
                            tilesQueue.front()->setState(TileState::Suggest);
                            tilesQueue.back()->setState(TileState::Suggest);
                        }
                        else {
                            tilesQueue.front()->setState(TileState::NotChosen);
                            tilesQueue.back()->setState(TileState::NotChosen);
                        }
                        tilesQueue.pop();
                        tilesQueue.pop();
                        return true;
                    }
                    tilesQueue.pop();
                    tilesQueue.pop();
                }
            }
        }
    }
    return false;
}

void Level::shuffle() {
    std::vector<int> leftID;
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        for (int j = 0; j < TILES_WIDTH + 2; ++j) {
            if (tiles[i][j] -> getState() == Deleted) {
                continue;
            }
            leftID.push_back(tiles[i][j] -> getID());
        }
    }
    std::random_shuffle(leftID.begin(), leftID.end());
    int index = 0;
    for (int i = 0; i < TILES_HEIGHT + 2; ++i) {
        for (int j = 0; j < TILES_WIDTH + 2; ++j) {
            if (tiles[i][j] -> getState() == Deleted) {
                continue;
            }
            delete tiles[i][j];
            tiles[i][j] = new Tiles(leftID[index], j, i);
            ++index;
        }
    }
}

int Level::getTime() {
    return currentTime;
}

bool Level::isReturnToMenu() {
    return isReturn;
}

void Level::setReturnToMenu() {
    isReturn = false;
    return;
}