#include "../include/Entity.hpp"

Entity::Entity(std::string textureName) : texture(textureName){}

void Entity::Update(){
	texture.Render(rect);
}
