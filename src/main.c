#include <raylib.h>
#include <stdlib.h>

int main(void)
{

    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib o brrr");
    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Model model = LoadModel("assets/chicken.obj");                    // Load the animated model mesh and basic data
    Texture2D texture = LoadTexture("assets/chicken.png");         // Load model texture and set material
    SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);     // Set model material map texture

    Vector3 position = { 0.0f, 0.0f, 0.0f };            // Set model position
    SetCameraMode(camera, CAMERA_FREE); 
    //SetTargetFPS(60);    

    while (!WindowShouldClose()) 
    {  
        UpdateCamera(&camera);  
        if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        BeginDrawing();
        {
            ClearBackground((Color){ 0, 0, 0, 255 });

            BeginMode3D(camera);
            {
                DrawModel(model, position, 1.0f, WHITE);
                DrawGrid(10, 1.0f);         // Draw a grid
            }
            EndMode3D();
            DrawText("Raylib ez lol", screenWidth - 200, screenHeight - 20, 10, GRAY);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    UnloadTexture(texture);
    UnloadModel(model);         // Unload model

    CloseWindow();              // Close window and OpenGL context

    return 0;
}