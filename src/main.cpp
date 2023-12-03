#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "components/setupParams.h"
#include "components/menus.h"
#include "components/base_object.h"
#include "components/player.h"
#include "components/obstacle.h"
#include "components/animation.h"
#include "components/powerUp.h"


// These vars used to work in header file but compiler suddenly
// didn't like that and forced me to move them (linker error)
//Texture positions
int bgPosX1{0};
int bgPosX2{3835};
int groundPosX1{0};
int groundPosX2{1920};

// Player start position x
int playerPosX{windowWidth/4 - playerWidth/2};

Color playerTint{WHITE};

// Game Params
int obstacleCount{20}; // No.  of obstacles in game
int obstacleSpacing{800};
bool menu{true};
bool alive{false};
float volume{0.01};
int level{1};
int frames{0}; //Counts frames invincible player is colliding w/ object
int timer{0};
int score{0};
int powerUpOdds{0};
bool powerUpAvail{false};

// Obstacle Params
int highObsY{playerPosY}; // Flying obstacle Y position
int lowObsY{(playerPosY + playerHeight) - obstacleHeight}; // Grounded obstacle Y position

void randomizeObstacles(Obstacle obsList[]) {
    for (int i = 0; i < obstacleCount; i++) {
        // Random Boolean taken from https://stackoverflow.com/questions/43329352/generating-random-boolean
        // Gives true or false to set obstacle to high or low
        bool randomizeObstacles = 0 + (rand() % (1 - 0 + 1)) == 1;
        if (randomizeObstacles){ // Set obstacles to high or low randomly
            obsList[i] = Obstacle(windowWidth + (obstacleSpacing * i), highObsY, obstacleWidth, obstacleHeight, RED);
        } else {
            obsList[i] = Obstacle(windowWidth + (obstacleSpacing * i), lowObsY, obstacleWidth, obstacleHeight, RED);
        }
        obsList[i].hitbox.x = obsList[i].posX;
        obsList[i].hitbox.y = obsList[i].posY;
        obsList[i].hitbox.width = obstacleWidth;
        obsList[i].hitbox.height = obstacleHeight;
    }
}

void resetGame() {
    buttonText = "Try Again";
    menu = true;
    alive = false;
    timer = 0;
    frames = 0;
    score = 0;
}

int main(){
    InitWindow(windowWidth,windowHeight,"TASM");
    InitAudioDevice();
    void SetMasterVolume(float volume);
    Font titleFont = LoadFont("src/resources/fonts/daydream.ttf");
    Font bodyFont = LoadFont("src/resources/fonts/retro-gaming.ttf");

    // World Textures
    Texture2D bgTexture1 = LoadTexture("src/resources/textures/bg.png");
    Texture2D bgTexture2 = LoadTexture("src/resources/textures/bg.png");
    Texture2D groundTexture1 = LoadTexture("src/resources/textures/ground.png");
    Texture2D groundTexture2 = LoadTexture("src/resources/textures/ground.png");

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

    if (level == 2){
        obstacleCount = 30;
        obstacleSpacing = 500;
    }

    // Init Array of obstacles
    Obstacle obsList[obstacleCount];
    randomizeObstacles(obsList);

    Texture2D obstacleTextureHigh = LoadTexture("src/resources/textures/obstacle-high.png");
    Texture2D obstacleTextureLow = LoadTexture("src/resources/textures/obstacle-low.png");

    // Init Power up
    Power powerUp;
    powerUp.posX = windowWidth;
    powerUp.color = Color{225, 211, 168, 255};

    // MENU VARIABLES (LIVES HERE TO ACCESS FONTS)
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

    Rectangle playBtn{windowWidth/2 - 150, windowHeight - 500, 300, 100};
    Vector2 mousePoint = { 0.0f, 0.0f };

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
        DrawTexture(bgTexture1, bgPosX1, 0, WHITE);
        DrawTexture(bgTexture2, bgPosX2, 0, WHITE);
        DrawTexture(groundTexture1, groundPosX1, 0, WHITE);
        DrawTexture(groundTexture2, groundPosX2, 0, WHITE);

        // Allows Main menu to clear when game is started
        if (alive) {
            menu = false;
        }

        // Draw title menu
        if (menu){
            DrawRectangle(100, 250, windowWidth - 200, windowHeight - 500, DARKGRAY);
            
            // DrawRectangle(windowWidth/2 - 150, windowHeight - 500, 300, 100, RED); // Visualizes play button bounds

            DrawTextEx(titleFont, title, finalPos, 40, 4, WHITE);
            DrawTextEx(bodyFont, buttonText, finalBtnPos, 50, 2, playBtnColor);


            mousePoint = GetMousePosition();
            
            // Button logic from Raylib Example: https://www.raylib.com/examples/textures/loader.html?name=textures_sprite_button
            if (CheckCollisionPointRec(mousePoint, playBtn))
            {
                playBtnColor = LIGHTGRAY;
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    playBtnColor = RAYWHITE;
                }

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) alive = true;
            }
            else {
                playBtnColor = WHITE;
            }
        }


        if(alive){
            // Count time while alive
            // frames ++;
            // if (frames == 60) {
            //     timer ++;
            //     frames = 0;
            // }

            // Draw Score to screen
            // DrawText(TextFormat("%d", frames), 40, 40, 100, RED);
            DrawText(TextFormat("%d", score), 100, 100, 100, RAYWHITE);


            // Scroll Bg textures
            if (bgPosX1 <= -3840) {
                bgPosX1 = 3835;
            } else {
                bgPosX1 -= 1;
            }

            if (bgPosX2 <= -3840) {
                bgPosX2 = 3835;
            } else {
                bgPosX2 -= 1;
            }

            if (groundPosX1 <= -1920) {
                groundPosX1 = 1920;
            } else {
                groundPosX1 -= 5;
            }
            if (groundPosX2 <= -1920) {
                groundPosX2 = 1920;
            } else {
                groundPosX2 -= 5;
            }

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

            DrawTextureRec(playerTexture, playerAnim.rec, playerAnim.pos, playerTint);

            // Invincibility
            if (myPlayer.invincible) {
                playerTint = YELLOW;
                powerUpAvail = false;
                powerUp.posX = windowWidth;
                powerUpOdds = 0;
            } else {
                playerTint = WHITE;
                // Randomly spawns powerup. Odds increase with score.
                if ((rand() % 1000) < 0.01 * powerUpOdds/1000) {
                    powerUpAvail = true;
                };
            }

            

            // Listen for power up becoming available to draw to screen and enable button press to activate
            if (powerUpAvail) {
                powerUp.Draw();
                powerUp.Update();
                powerUp.Key(powerUp.posX, powerUp.posY);
                myPlayer.invincible = powerUp.Activate(myPlayer.invincible);
                if (powerUp.posX <= -100) {
                    powerUpAvail = false;
                    powerUp.posX = windowWidth;
                    powerUpOdds = 0;
                }
            }

            // Loop through array of obstacles to draw and move them across screen
            for (int i = 0; i < obstacleCount; i++){
                // obsList[i].Draw();
                obsList[i].Update();
                if (obsList[i].posY == highObsY){
                    DrawTexture(obstacleTextureHigh, obsList[i].posX, obsList[i].posY, WHITE);
                } else {
                    DrawTexture(obstacleTextureLow, obsList[i].posX, obsList[i].posY, WHITE);
                }
                
                // Collision detection
                if(CheckCollisionRecs(myPlayer.hitbox, obsList[i].hitbox)){
                    if (!myPlayer.invincible){
                        randomizeObstacles(obsList);
                        resetGame();
                    } else {
                        // player collides with obstacles for 15 frames. Counts 15 frames before disabling invincibility
                        frames ++;
                        if (frames == 15) {
                            myPlayer.invincible = false;
                            frames = 0;
                        }
                    }
                }
                if(obsList[i].posX == myPlayer.posX - obstacleWidth) {
                    score ++;
                    powerUpOdds ++;
                }
            }
       }
        
        EndDrawing();
    }
    UnloadTexture(playerTexture);
    UnloadTexture(obstacleTextureHigh);
    UnloadTexture(obstacleTextureLow);
    UnloadTexture(bgTexture1);
    UnloadTexture(bgTexture2);
    UnloadTexture(groundTexture1);
    UnloadTexture(groundTexture2);
    UnloadSound(myPlayer.jump);
    UnloadSound(myPlayer.crouch);
    UnloadFont(titleFont);
    UnloadFont(bodyFont);
    CloseWindow();
}