#pragma once
#include "TexturesHolder.h"

class Drawable {
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual ~Drawable() = default;
};