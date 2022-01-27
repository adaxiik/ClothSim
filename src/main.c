#include <raylib.h>
#include <stdlib.h>
#include "cloth.h"
int main(void)
{

    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "cloth sim go brrr");
    
    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type


    Vector3 position = { 0.0f, 0.0f, 0.0f };            // Set model position
    SetCameraMode(camera, CAMERA_FREE); 
    //SetTargetFPS(60);    
    Cloth cloth = CreateCloth(50,50);
    bool paused = true;
    while (!WindowShouldClose()) 
    {  
        UpdateCamera(&camera); 
        if(!paused) 
            UpdateCloth(&cloth);
        if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        if (IsKeyDown('X')) TakeScreenshot("screenshot.png");
        if (IsKeyPressed(KEY_SPACE)) paused=!paused;
        BeginDrawing();
        {
            ClearBackground(DARKGRAY);

            BeginMode3D(camera);
            {
                DrawGrid(10, 1.0f);         // Draw a grid
                DrawCloth(&cloth);
            }
            EndMode3D();
            DrawFPS(10, 10);
        }
        EndDrawing();
    }
    DestroyCloth(&cloth);
    CloseWindow();              // Close window and OpenGL context

    return 0;
}