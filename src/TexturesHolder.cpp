#include "TexturesHolder.h"

TexturesHolder& TexturesHolder::GetInstance() {
    static TexturesHolder instance;
    return instance;
}

TexturesHolder::~TexturesHolder() {
    for (auto& img : textures) {
        UnloadTexture(img.second);
    }
    textures.clear();
}

TexturesHolder::TexturesHolder() {
    for (int i = 0; i < 33; ++i) {
        std::string path = TEXTURES_PATH + std::to_string(i + 1) + ".png";
        Texture2D img = LoadTexture(path.c_str());
        textures.insert(std::make_pair(i, img));
    }

    std::string path = "assets/images/timebar.png";
    Texture2D img = LoadTexture(path.c_str());
    textures.insert(std::make_pair(static_cast<int>(TextureValue::timeBar), img));

    path = "assets/button/pauseButton.png";
    img = LoadTexture(path.c_str());
    textures.insert(std::make_pair(static_cast<int>(TextureValue::pauseButton), img));

    path = "assets/button/resumeButton.png";
    img = LoadTexture(path.c_str());
    textures.insert(std::make_pair(static_cast<int>(TextureValue::resumeButton), img));

    path = "assets/images/background.png";
    img = LoadTexture(path.c_str());
    textures.insert(std::make_pair(static_cast<int>(TextureValue::background), img));

    path = "assets/button/shuffleButton.png";
    img = LoadTexture(path.c_str());
    textures.insert(std::make_pair(static_cast<int>(TextureValue::shuffleButton), img));

    path = "assets/button/suggestButton.png";
    img = LoadTexture(path.c_str());
    textures.insert(std::make_pair(static_cast<int>(TextureValue::suggestButton), img));

    path = "assets/button/playButton.png";
    img = LoadTexture(path.c_str());
    textures.insert(std::make_pair(static_cast<int>(TextureValue::playButton), img));

    path = "assets/button/settingsButton.png";
    img = LoadTexture(path.c_str());
    textures.insert(std::make_pair(static_cast<int>(TextureValue::settingsButton), img));

    path = "assets/button/exitButton.png";
    img = LoadTexture(path.c_str());
    textures.insert(std::make_pair(static_cast<int>(TextureValue::exitButton), img));

    path = "assets/button/gameName.png";
    img = LoadTexture(path.c_str());
    textures.insert(std::make_pair(static_cast<int>(TextureValue::gameName), img));

    path = "assets/button/returnButton.png";
    img = LoadTexture(path.c_str());
    textures.insert(std::make_pair(static_cast<int>(TextureValue::returnButton), img));
}

Texture2D& TexturesHolder::get(int ID) {
    auto img = textures.find(ID);
    if (img == textures.end()) {
        throw std::runtime_error("Texture not found");
    }
    return img->second;
}

const Texture2D& TexturesHolder::get(int ID) const {
    auto img = textures.find(ID);
    if (img == textures.end()) {
        throw std::runtime_error("Texture not found");
    }
    return img->second;
}