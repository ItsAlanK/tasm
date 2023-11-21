#include <iostream>
#include "raylib.h"
#include "components/base_object.h"
#include "components/player.h"
#include "components/obstacle.h"

#include <string>

using namespace std;


int main(){
    // Set window size
    const int windowWidth{960};
    const int windowHeight{960};
    
    InitWindow(windowWidth,windowHeight,"TASM");

    // Test adding texture
    Vector2 position{0.0f, 0.0f};
    Texture2D playerTexture = LoadTexture("src/resources/textures/tasm-run-cycle.png");
    Rectangle sourceRec = (Rectangle){0.0f, 0.0f, (float)(playerTexture.width)/6, (float)(playerTexture.height)};

    //Set Game params
    int obstacleCount{10}; // No.  of obstacles in game

    // Set Player params (could include consts in Player class later)
    const int playerWidth{80};
    const int playerHeight{160};
    const int playerPosY{(windowHeight/4)*3 - playerHeight/2};
    int playerPosX{windowWidth/4 - playerWidth/2};

    // Set Obstacle params
    const int obstacleWidth{80};
    const int obstacleHeight(40);
    int highObsY{playerPosY}; // Flying obstacle Y position
    int lowObsY{(playerPosY + playerHeight) - obstacleHeight}; // Grounded obstacle Y position

    Player myPlayer(playerPosX, playerPosY, playerWidth, playerHeight, BLUE);

    // Init Array of obstacles
    Obstacle obsList[obstacleCount];
    for (int i = 0; i < obstacleCount; i++) {
        // Random Boolean taken from https://stackoverflow.com/questions/43329352/generating-random-boolean
        bool randomizeObstacles = 0 + (rand() % (1 - 0 + 1)) == 1;
        if (randomizeObstacles){ // Set obstacles to high or low randomly
            obsList[i] = Obstacle(windowWidth + (500 * i), highObsY, 80, 40, RED);
        } else {
            obsList[i] = Obstacle(windowWidth + (500 * i), lowObsY, 80, 40, RED);
        }
    }

    // Set FPS
    SetTargetFPS(60);

    // Main game loop
	while(!WindowShouldClose()){

        // Quick close button
        if(IsKeyPressed(KEY_ESCAPE)) {
            CloseWindow();
        }

        const float deltaTime{GetFrameTime()};

        // Impose gravity on player
        myPlayer.Apply_Gravity(deltaTime, playerPosY);

        // listen for inputs
        myPlayer.Jump(deltaTime);
        myPlayer.Crouch(playerPosX, playerPosY, playerWidth, playerHeight);

        BeginDrawing();
        DrawTextureRec(playerTexture, sourceRec, position, WHITE);
        ClearBackground(LIGHTGRAY);
        myPlayer.Draw();

        // Loop through array of obstacles to draw and move them across screen
        for (int i = 0; i < obstacleCount; i++){
            obsList[i].Draw();
            obsList[i].Update();
        }
        EndDrawing();
    }
    UnloadTexture(playerTexture);
    CloseWindow();
}