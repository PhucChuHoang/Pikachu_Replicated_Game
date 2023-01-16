#include "Drawable.h"
#include "Tiles.h"

class Level: public Drawable {
private:
    std::vector<std::vector<Tiles*>> tiles;
    int currentTime;                        
    bool isOver;                            // If isOver == true => Game Over
    int totalTiles;                         
public:
    Level();
    ~Level();
    void draw() override;
    void update() override;
    bool checkOver();                       // If currentTime == 0 => Game Over
    bool checkWin();                        // If totalTiles == 0 => Win => Next Level
};