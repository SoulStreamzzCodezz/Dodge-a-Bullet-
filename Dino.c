#include "raylib.h" 

int main(void) {
	const int windowWidth = 800;
	const int  windowHeight = 500;
	 InitWindow(windowWidth, windowHeight, "Game");
	int playerPosX = 100;
	float playerPosY = 470.0f;
	 float playerVelY = 0.0f;
	const float  grav = 400.0f;
	float deltaTime = GetFrameTime();
	const int GLev = 470;
	float enemyPosX = 700.0f;
	const enemyPosXDef = 700.0f;
	const enemySpeed = 100.0f;

	SetTargetFPS(60);
	Texture2D myImage = LoadTexture("/home/soulstremzz/something.png");
	Texture2D Enemy = LoadTexture("/home/soulstremzz/bullet.png");
	if (myImage.id == 0) // myImage.id will be 0 if the texture failed to load
	{
   	 TraceLog(LOG_ERROR, "Failed to load texture: /home/soulstremzz/something.png");
    	CloseWindow(); // Close window if texture failed to load
   	 return 1; // Exit program with an error code
	}
	while (!WindowShouldClose()) 
	{
		deltaTime = GetFrameTime();
		playerVelY +=  grav * deltaTime;
		playerPosY +=  playerVelY * deltaTime;
		enemyPosX -= enemySpeed * deltaTime; 

		if (enemyPosX < -Enemy.width)
		{
			enemyPosX = enemyPosXDef;
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
			DrawTexture(Enemy, enemyPosX, 470, WHITE);
		 EndDrawing();

	}
	UnloadTexture(myImage);
	UnloadTexture(Enemy);
	CloseWindow();
	TraceLog(LOG_INFO," PlayerPosY: %f, PlayerVelY: %f, DeltaTime: %f", playerPosY, playerVelY, deltaTime);
	return 0;

}


