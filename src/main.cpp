#include <iostream>
#include "raylib.h"
#include "components/base_object.h"
#include "components/player.h"
#include "components/obstacle.h"
#include "components/animation.h"


int main(){
    // Set window size
    const int windowWidth{960};
    const int windowHeight{960};
    
    InitWindow(windowWidth,windowHeight,"TASM");

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


    // Init Player object
    Player myPlayer(playerPosX, playerPosY, playerWidth, playerHeight, BLUE);

    /**
     * Loading texture for animation using anim struct. 
     * For now works here but cant refactor into player.cpp where it should live
     * 
    */
    Vector2 position{(float)(playerPosX), (float)(playerPosY)};
    Texture2D playerTexture = LoadTexture("src/resources/textures/tasm-run-cycle.png");

    Anim playerAnim;
    playerAnim.rec.width = playerTexture.width/6;
    playerAnim.rec.height = playerTexture.height;
    playerAnim.rec.x = 0;
    playerAnim.rec.y = 0;
    playerAnim.pos = position;
    playerAnim.frame = 0;
    playerAnim.updateTime = 1.0/12.0;
    playerAnim.runningTime = 0.0;
    playerAnim.isRunning = true;


    // Init Array of obstacles
    Obstacle obsList[obstacleCount];
    for (int i = 0; i < obstacleCount; i++) {
        // Random Boolean taken from https://stackoverflow.com/questions/43329352/generating-random-boolean
        // Gives true or false to set obstacle to high or low
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
        ClearBackground(LIGHTGRAY);

        /**
         * Running animation for character
         * Works off running bool so animations can be changed later for other actions
        */
        if(playerAnim.isRunning) {
            playerAnim.rec.width = playerTexture.width/6;
            playerAnim.runningTime += deltaTime;

            if (playerAnim.runningTime >= playerAnim.updateTime){
                playerAnim.runningTime = 0.0;
                playerAnim.rec.x = playerAnim.frame * playerAnim.rec.width;
                playerAnim.frame ++;
                if (playerAnim.frame>5) {
                    playerAnim.frame = 0;
                }
            }
        }

        // Change texture for player on crouch
        if (myPlayer.isCrouching){
            playerAnim.rec.width = playerHeight;
            playerAnim.rec.height = playerWidth;
            playerTexture = LoadTexture("src/resources/textures/crouch.png");
        } else {
            playerAnim.rec.width = playerTexture.width/6;
            playerAnim.rec.height = playerTexture.height;
            playerTexture = LoadTexture("src/resources/textures/tasm-run-cycle.png");
        }

        // track animation to player hitbox
        playerAnim.pos.x = myPlayer.posX;
        playerAnim.pos.y = myPlayer.posY;

        DrawTextureRec(playerTexture, playerAnim.rec, playerAnim.pos, WHITE);

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