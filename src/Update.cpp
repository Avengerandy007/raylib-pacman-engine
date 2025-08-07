#include "../include/Update.hpp"
#include "../include/Tile.hpp"

void ResfreshWindow(){
	BeginDrawing();

	ClearBackground(BLACK);

	EndDrawing();
}

void Update(){
	bool running = true;
	while (running){
		if (WindowShouldClose()) running = false;
		ResfreshWindow();
		Tile::tileSet.matrix[0][0].m_containedEntity->Update();
	}
}
