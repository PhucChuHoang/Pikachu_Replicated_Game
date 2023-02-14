#include "Drawable.h"

class MainMenu: public Drawable{
private:
    MenuState menuState;
    
    Texture2D gameName = TexturesHolder::GetInstance().get(static_cast<int>(TextureValue::gameName));
    Texture2D playButton = TexturesHolder::GetInstance().get(static_cast<int>(TextureValue::playButton));
    Texture2D settingsButton = TexturesHolder::GetInstance().get(static_cast<int>(TextureValue::settingsButton));
    Texture2D exitButton = TexturesHolder::GetInstance().get(static_cast<int>(TextureValue::exitButton));

    Rectangle playButtonRec = { (float)SCREEN_WIDTH / 2 - playButton.width / 2, (float)SCREEN_HEIGHT / 2 - playButton.height / 2, (float)playButton.width, (float)playButton.height };
    Rectangle settingsButtonRec = { (float)SCREEN_WIDTH / 2 - settingsButton.width / 2, (float)SCREEN_HEIGHT / 2 - settingsButton.height / 2 + 150, (float)settingsButton.width, (float)settingsButton.height };
    Rectangle exitButtonRec = { (float)SCREEN_WIDTH / 2 - exitButton.width / 2, (float)SCREEN_HEIGHT / 2 - exitButton.height / 2 + 300, (float)exitButton.width, (float)exitButton.height };

public:
    void draw();
    void update();
    MainMenu();
    ~MainMenu();
    MenuState getState();
    void setState(MenuState state);
};