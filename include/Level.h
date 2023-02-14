#pragma once
#include "Drawable.h"
#include "Tiles.h"

class Level: public Drawable {
private:
    std::vector<std::vector<Tiles*>> tiles;
    std::vector<std::vector<Rectangle>> tilesRect;
    int countFrame;
    int currentTime;     
    bool isPause;                           // If isPause == true => Pause                   
    bool isOver;                            // If isOver == true => Game Over
    bool isReturn;                          // If isReturn == true => Return to main menu
    int totalTiles; 
    int numbShuffle;                        // Number of shuffle (3 shuffle per level)
    int numbSuggest;                        // Number of suggest (3 suggest per level)
    std::vector<int> countPerImg;           // Count number of tiles per image    
    std::queue<Tiles*> tilesQueue;          // Queue of tiles that have been clicked
    int ansTable[11][18];
    
    Texture2D pauseButton = TexturesHolder::GetInstance().get(static_cast<int>(TextureValue::pauseButton));
    Texture2D resumeButton = TexturesHolder::GetInstance().get(static_cast<int>(TextureValue::resumeButton));
    Rectangle pauseButtonRect = { 1120, 250, (float)pauseButton.width, (float)pauseButton.height };

    Texture2D shuffleButton = TexturesHolder::GetInstance().get(static_cast<int>(TextureValue::shuffleButton));
    Rectangle shuffleButtonRect = { 1120, 400, (float)shuffleButton.width, (float)shuffleButton.height };

    Texture2D suggestButton = TexturesHolder::GetInstance().get(static_cast<int>(TextureValue::suggestButton));
    Rectangle suggestButtonRect = { 1120, 550, (float)suggestButton.width, (float)suggestButton.height };

    Texture2D returnButton = TexturesHolder::GetInstance().get(static_cast<int>(TextureValue::returnButton));
    Rectangle returnButtonRect = { 20, 30, (float)returnButton.width, (float)returnButton.height };

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
    bool isPossibleMoves(bool isSuggest);
    bool isReturnToMenu();
    void setReturnToMenu();
    void shuffle();
    int getTime();
    void suggest();
};