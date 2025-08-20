#include "../include/Entity.hpp"

/*
 *	WALL CLASS
 */
Wall::Wall(){
	typeId = WALL;
}

void Wall::Update(){
	texture.Render(rect);
}
