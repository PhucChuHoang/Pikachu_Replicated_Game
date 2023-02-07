#include "Drawable.h"
#include "Tiles.h"

class Level: public Drawable {
private:
    std::vector<std::vector<Tiles*>> tiles;
    std::vector<std::vector<Rectangle>> tilesRect;
    int currentTime;                        
    bool isOver;                            // If isOver == true => Game Over
    int totalTiles; 
    std::vector<int> countPerImg;           // Count number of tiles per image    
    std::queue<Tiles*> tilesQueue;          // Queue of tiles that have been clicked
    int ansTable[11][18];

public:
    Level();
    ~Level();
    void createMap();                       // Create base matrix + Random
    void draw() override;
    void update() override;
    std::vector<std::vector<int>> random();
    bool checkMatching();
    bool checkOver();                       // If currentTime == 0 => Game Over
    bool checkWin();                        // If totalTiles == 0 => Win => Next Level
    void getClick(int x, int y);            // Get click from mouse
    void bfs();
    bool isPossibleMoves();
};