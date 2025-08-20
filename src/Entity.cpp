#include "../include/Entity.hpp"

/*
 *	WALL CLASS
 */
Wall::Wall(){
	typeId = 1;
}

void Wall::Update(){
	texture.Render(rect);
}
