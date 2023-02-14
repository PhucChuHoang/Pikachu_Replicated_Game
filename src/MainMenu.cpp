#include "MainMenu.h"

MainMenu::MainMenu() {
    menuState = MenuState::Menu;
}

MainMenu::~MainMenu() {

}

void MainMenu::draw() {
    DrawTexture(gameName, (float)SCREEN_WIDTH / 2 - gameName.width / 2, (float)SCREEN_HEIGHT / 2 - gameName.height / 2 - 250, {251,202,206,255});
    DrawTexture(playButton, (float)SCREEN_WIDTH / 2 - playButton.width / 2, (float)SCREEN_HEIGHT / 2 - playButton.height / 2, {251,202,206,255});
    DrawTexture(settingsButton, (float)SCREEN_WIDTH / 2 - settingsButton.width / 2, (float)SCREEN_HEIGHT / 2 - settingsButton.height / 2 + 150, {251,202,206,255});
    DrawTexture(exitButton, (float)SCREEN_WIDTH / 2 - exitButton.width / 2, (float)SCREEN_HEIGHT / 2 - exitButton.height / 2 + 300, {251,202,206,255});
}

void MainMenu::update() {
    Vector2 mousePos;
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        mousePos = GetMousePosition();
    }
    if (CheckCollisionPointRec(mousePos, playButtonRec)) {
        menuState = MenuState::Play;
    }
    else if (CheckCollisionPointRec(mousePos, settingsButtonRec)) {
        menuState = MenuState::Settings;
    }
    else if (CheckCollisionPointRec(mousePos, exitButtonRec)) {
        menuState = MenuState::Exit;
    }
}

MenuState MainMenu::getState() {
    return menuState;
}

void MainMenu::setState(MenuState state) {
    menuState = state;
}