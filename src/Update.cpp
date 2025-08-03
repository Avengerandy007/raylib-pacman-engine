#include "../include/Update.hpp"

void ResfreshWindow(){
	BeginDrawing();

	ClearBackground(BLACK);

	EndDrawing();
}

void Update(){
	InitWindow(640, 480, "Pacman");
	SetExitKey(KEY_NULL);
	bool running = true;
	while (running){
		if (WindowShouldClose()) running = false;
		ResfreshWindow();

	}
	CloseWindow();
}
