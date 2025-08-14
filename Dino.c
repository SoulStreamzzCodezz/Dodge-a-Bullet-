#include "raylib.h" 

int main(void) {
	const int windowWidth = 800;
	const int  windowHeight = 500;
	 InitWindow(windowWidth, windowHeight, "Game");
	int playerPosX = 100;
	float playerPosY = 470.0f;
	 float playerVelY = 0.0f;
	const float  grav = 650.0f;
	float deltaTime = GetFrameTime();
	const int GLev = 470;
	float enemyPosX = 700.0f;
	const float enemyPosXDef = 700.0f;
	const float enemySpeed = 255.0f;
        float enemyPosYDef = 425.0f;
	int score = 0;

	SetTargetFPS(60);
	Texture2D myImage = LoadTexture("something.png");
	Rectangle myImageCollRect = { playerPosX, playerPosY, myImage.width, myImage.height };
           
	myImageCollRect.x += 5;
	myImageCollRect.y += 5;
	myImageCollRect.width -= 10;
	myImageCollRect.height -= 10;


	Texture2D Enemy = LoadTexture("bullet.png");
	if (myImage.id == 0) // myImage.id will be 0 if the texture failed to load
	{
   	 TraceLog(LOG_ERROR, "Failed to load texture:something.png");
    	CloseWindow(); // Close window if texture failed to load
   	 return 1; // Exit program with an error code
	}
	if (Enemy.id == 0)
        {
           TraceLog(LOG_ERROR, "Failed to load enemy texture.");
           UnloadTexture(myImage); // Unload the player texture before exiting
            CloseWindow();
            return 1;
        }
	while (!WindowShouldClose()) 
	{
		deltaTime = GetFrameTime();
		playerVelY +=  grav * deltaTime;
		playerPosY +=  playerVelY * deltaTime;
		enemyPosX -= enemySpeed * deltaTime; 
		
		myImageCollRect.x = playerPosX;
		myImageCollRect.y = playerPosY;

		Rectangle obstacleCollisionRect = { enemyPosX, enemyPosYDef, Enemy.width, Enemy.height };

		if (CheckCollisionRecs(myImageCollRect, obstacleCollisionRect))
		{
			enemyPosX = enemyPosXDef;
			score -= score;
		}


		if (enemyPosX < -Enemy.width)
		{
			enemyPosX = enemyPosXDef;
			score += 1;
		}
		if (playerPosY >=  GLev) 
		{
			playerPosY = GLev;
			playerVelY = 0.0f;
		}

		if (IsKeyPressed(KEY_UP) && playerPosY >= GLev)
		{
			playerVelY = -400.0f;
		}


		 BeginDrawing();
			 ClearBackground(GRAY);
			DrawTexture(myImage, playerPosX, playerPosY,WHITE);
			DrawTexture(Enemy, enemyPosX, enemyPosYDef, WHITE);
			Font GetFontDefault(void);
		        DrawText(TextFormat("Score: %i", score), 10, 10, 20, BLACK);
		 EndDrawing();

	}
	UnloadTexture(myImage);
	UnloadTexture(Enemy);
	CloseWindow();
	TraceLog(LOG_INFO," PlayerPosY: %f, PlayerVelY: %f, DeltaTime: %f", playerPosY, playerVelY, deltaTime);
	return 0;

}


