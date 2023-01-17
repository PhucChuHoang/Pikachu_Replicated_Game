#include "Drawable.h"
#include "Tiles.h"

class Level: public Drawable {
private:
    std::vector<std::vector<Tiles*>> tiles;
    int currentTime;                        
    bool isOver;                            // If isOver == true => Game Over
    int totalTiles; 
    std::vector<int> countPerImg;           // Count number of tiles per image                        
public:
    Level();
    ~Level();
    void draw() override;
    void update() override;
    std::vector<std::vector<int>> random();
    bool checkOver();                       // If currentTime == 0 => Game Over
    bool checkWin();                        // If totalTiles == 0 => Win => Next Level
};