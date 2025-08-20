#include "../include/Entity.hpp"

/*
 *	WALL CLASS
 */

void Wall::LoadTextures(){
	texture = ImageTexture("Wall.png");
}

Wall::Wall(){
	typeId = WALL;
}

void Wall::Update(){
	texture.Render(rect);
}
