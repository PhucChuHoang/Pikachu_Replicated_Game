#include <raylib.h>
#include <vector>
#include <string>
#include "TexturesHolder.h"
using std::vector;

int main() {
    InitWindow(1000, 800, "Pokemon");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 33; ++i) {
            if (i <= 16) {
                DrawTexture(TexturesHolder::GetInstance().get(i), 53*i, 0, WHITE);
            }
            else {
                DrawTexture(TexturesHolder::GetInstance().get(i), 53*(i-17), 65, WHITE);
            }
        }
        for (int i = 0; i < 33; ++i) {
            if (i <= 16) {
                DrawTexture(TexturesHolder::GetInstance().get(i), 53*i, 65*2, PINK);
            }
            else {
                DrawTexture(TexturesHolder::GetInstance().get(i), 53*(i-17), 65*3, PINK);
            }
        }
        EndDrawing();
    }
    CloseWindow();
}