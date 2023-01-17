#include "Tiles.h"

Tiles::Tiles(int ID, int x, int y) : ID(ID), x(x), y(y), texture(TexturesHolder::GetInstance().get(ID)) {

}

void Tiles::setChosen(bool State) {
    isChosen = State;
}

void Tiles::draw() {
    if (isDeleted) {
        return;
    }
    if (isChosen) {
        DrawTexture(texture, PADDING_X + x*texture.width, PADDING_Y + y*texture.height, GRAY);
    }
    else {
        DrawTexture(texture, PADDING_X + x*texture.width, PADDING_Y + y*texture.height, WHITE);
    }
}