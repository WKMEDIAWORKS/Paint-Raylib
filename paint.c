#include <stdio.h>
#include "raylib.h"

#define WIDTH 800
#define HEIGHT 450
#define MAX_COLORS_COUNT 5

#define CUSTOM_RED     (Color){255,   0,   0, 255}
#define CUSTOM_GREEN   (Color){  0, 255,   0, 255}
#define CUSTOM_ORANGE  (Color){255, 165,   0, 255}
#define CUSTOM_BLUE    (Color){  0,   0, 255, 255}
#define CUSTOM_PURPLE  (Color){128,   0, 128, 255}

Color currentColor = WHITE;

Color getColorFromScreen(void)
{
    Vector2 mouse = GetMousePosition();
    Vector2 scale = GetWindowScaleDPI();

    int px = (int)(mouse.x * scale.x);
    int py = (int)(mouse.y * scale.y);

    if (px >= 20 * scale.x && px <= 120 * scale.x &&
        py >= 10 * scale.y && py <= 30 * scale.y)
    {
        Image img = LoadImageFromScreen();
        Color c = GetImageColor(img, px, py);
        UnloadImage(img);
        return c;
    }

    return (Color){0, 0, 0, 0}; 
}

void drawOnCanvas(RenderTexture2D canvas, Color color)
{
    Vector2 mouse = GetMousePosition();
    Vector2 scale = GetWindowScaleDPI();

    int x = (int)(mouse.x);
    int y = (int)(mouse.y);

    BeginTextureMode(canvas);
        DrawPixel(x, y, color);
    EndTextureMode();
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Paint");
    SetTargetFPS(60);

    const Color palette[MAX_COLORS_COUNT] = {
        CUSTOM_RED, CUSTOM_GREEN, CUSTOM_ORANGE,
        CUSTOM_BLUE, CUSTOM_PURPLE
    };

    Rectangle paletteRects[MAX_COLORS_COUNT];

    for (int i = 0; i < MAX_COLORS_COUNT; i++)
    {
        paletteRects[i] = (Rectangle){
            20 + i * 20,
            10,
            20,
            20
        };
    }

    RenderTexture2D canvas = LoadRenderTexture(WIDTH, HEIGHT);

    BeginTextureMode(canvas);
        ClearBackground(BLACK);
    EndTextureMode();

    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Color picked = getColorFromScreen();
            if (picked.a != 0)
            {
                currentColor = picked;
                printf("Picked: %d %d %d %d\n",
                       picked.r, picked.g, picked.b, picked.a);
            }
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            drawOnCanvas(canvas, currentColor);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTextureRec(
            canvas.texture,
            (Rectangle){
                0,
                0,
                (float)canvas.texture.width,
               -(float)canvas.texture.height
            },
            (Vector2){0, 0},
            WHITE
        );

        for (int i = 0; i < MAX_COLORS_COUNT; i++)
        {
            DrawRectangleRec(paletteRects[i], palette[i]);
        }

        EndDrawing();
    }

    UnloadRenderTexture(canvas);
    CloseWindow();

    return 0;
}