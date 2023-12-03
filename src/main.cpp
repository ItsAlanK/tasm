#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "components/setupParams.h"
#include "components/menus.h"
#include "components/base_object.h"
#include "components/player.h"
#include "components/obstacle.h"
#include "components/animation.h"


int main(){
    InitWindow(windowWidth,windowHeight,"TASM");
    InitAudioDevice();
    void SetMasterVolume(float volume);
    Font titleFont = LoadFont("src/resources/fonts/daydream.ttf");
    Font bodyFont = LoadFont("src/resources/fonts/retro-gaming.ttf");

    // Init Player object
    Player myPlayer(playerPosX, playerPosY, playerWidth, playerHeight, BLUE);
    myPlayer.hitbox.x = playerPosX;
    myPlayer.hitbox.y = playerPosY;
    myPlayer.hitbox.width = playerWidth;
    myPlayer.hitbox.height = playerHeight;

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
            obsList[i] = Obstacle(windowWidth + (500 * i), highObsY, obstacleWidth, obstacleHeight, RED);
        } else {
            obsList[i] = Obstacle(windowWidth + (500 * i), lowObsY, obstacleWidth, obstacleHeight, RED);
        }
        obsList[i].hitbox.x = obsList[i].posX;
        obsList[i].hitbox.y = obsList[i].posY;
        obsList[i].hitbox.width = obstacleWidth;
        obsList[i].hitbox.height = obstacleHeight;
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

        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        // Draw title menu
        DrawRectangle(100, 250, windowWidth - 200, windowHeight - 500, DARKGRAY);
        // Center text by getting size of text and divide by 2 to subtract from position
        // relative to window size
        Vector2 titleSize{MeasureTextEx(titleFont, title, 40, 4)};
        titleSize = Vector2Scale(titleSize, 0.5);
        Vector2 titlePos{windowWidth/2, windowHeight - 600};
        Vector2 finalPos = Vector2Subtract(titlePos, titleSize);

        Vector2 buttonSize{MeasureTextEx(bodyFont, buttonText, 50, 2)};
        buttonSize = Vector2Scale(buttonSize, 0.5);
        Vector2 buttonPos{windowWidth/2, windowHeight - 450};
        Vector2 finalBtnPos = Vector2Subtract(buttonPos, buttonSize);

        DrawRectangle(windowWidth/2 - 150, windowHeight - 500, 300, 100, RED);

        DrawTextEx(titleFont, title, finalPos, 40, 4, WHITE);
        DrawTextEx(bodyFont, buttonText, finalBtnPos, 50, 2, WHITE);

        Rectangle playBtn{windowWidth/2 - 150, windowHeight - 500, 300, 100};
        Vector2 mousePoint = { 0.0f, 0.0f };
        int btnState = 0;
        mousePoint = GetMousePosition();
        
        // Button logic from Raylib Example: https://www.raylib.com/examples/textures/loader.html?name=textures_sprite_button
        if (CheckCollisionPointRec(mousePoint, playBtn))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
            else btnState = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) alive = true;
        }
        else btnState = 0;

        if(alive){
            // Impose gravity on player
            myPlayer.Apply_Gravity(deltaTime, playerPosY);

            // listen for inputs
            myPlayer.Jump(deltaTime);
            myPlayer.Crouch(playerPosX, playerPosY, playerWidth, playerHeight);

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
                if(CheckCollisionRecs(myPlayer.hitbox, obsList[i].hitbox)){
                    alive = false;
                }
            }
       }
        
        EndDrawing();
    }
    UnloadTexture(playerTexture);
    UnloadSound(myPlayer.jump);
    UnloadSound(myPlayer.crouch);
    UnloadFont(titleFont);
    UnloadFont(bodyFont);
    CloseWindow();
}