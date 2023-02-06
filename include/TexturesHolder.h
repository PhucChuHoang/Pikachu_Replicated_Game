#pragma once
#include <map>
#include <string>
#include <raylib.h>
#include <stdexcept>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include "Const.h"

class TexturesHolder {
private:
    static TexturesHolder instance;
    std::map<int, Texture2D> textures;
    TexturesHolder();
    TexturesHolder(const TexturesHolder&) = delete;
    TexturesHolder& operator=(const TexturesHolder&) = delete;

public:
    static TexturesHolder& GetInstance();
    ~TexturesHolder();
    Texture2D& get(int ID);
    const Texture2D& get(int ID) const;
};