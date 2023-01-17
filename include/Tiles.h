#include "TexturesHolder.h"

class Tiles {
private:
    bool isChosen = false;
    int ID;                         // ID of image in TexturesHolder
    int x, y;                       // coordinates of tile
    Texture2D& texture;             // texture of tile
    bool isDeleted = false;         // if true, tile will be deleted, will not be drawn

public:
    Tiles(int ID, int x, int y);
    void setChosen(bool State);     // State = true => tile is chosen
    void draw();
};