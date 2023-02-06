#include "TexturesHolder.h"

class Tiles {
private:
    TileState state;    // state of tile
    int ID;                         // ID of image in TexturesHolder
    int x, y;                       // coordinates of tile
    Texture2D& texture;             // texture of tile

public:
    Tiles(int ID, int x, int y);
    void setState(TileState State);
    void draw();
    TileState getState();
    int getID();
    int getX();
    int getY();
};