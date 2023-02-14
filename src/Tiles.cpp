#include "Tiles.h"

Tiles::Tiles(int ID, int x, int y) : ID(ID), x(x), y(y), texture(TexturesHolder::GetInstance().get(ID)) {
    state = TileState::NotChosen;
}

void Tiles::setState(TileState State) {
    state = State;
}

void Tiles::draw() {
    if (state == TileState::Deleted) {
        return;
    }
    if (state == TileState::Chosen) {
        DrawTexture(texture, PADDING_X + x*TILES_SIZE_WIDTH, PADDING_Y + y*TILES_SIZE_HEIGHT, GRAY);
    }
    else if (state == TileState::NotChosen){
        DrawTexture(texture, PADDING_X + x*TILES_SIZE_WIDTH, PADDING_Y + y*TILES_SIZE_HEIGHT, WHITE);
    }
    else {
        DrawTexture(texture, PADDING_X + x*TILES_SIZE_WIDTH, PADDING_Y + y*TILES_SIZE_HEIGHT, {225,134,202,255});
    }
}

TileState Tiles::getState() {
    return state;
}

int Tiles::getID() {
    return ID;
}

int Tiles::getX() {
    return x;
}

int Tiles::getY() {
    return y;
}