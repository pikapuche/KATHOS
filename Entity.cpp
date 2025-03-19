#include "Entity.hpp"

Entity::Entity(float posX, float posY) {}

void Entity::collision(Sprite& tile, float deltaTime) {
    if (tile.getGlobalBounds().intersects(sprite.getGlobalBounds()) && tile.getPosition().y < position.y) { // si le perso se trouve sous la plateforme il ne la traverse pas 
        position.y = tile.getPosition().y + boxCol1;
        velocity.y = gravity * deltaTime;
        state = NONE;
    }
    else if (tile.getGlobalBounds().intersects(sprite.getGlobalBounds()) && tile.getPosition().y > position.y) { // collision de base 
        position.y = tile.getPosition().y - boxCol2;
        velocity.y = 0;
        state = GROUNDED;
    }
}

Sprite& Entity::getSprite()
{
    return sprite;
}

int Entity::getLife()
{
    return life;
}

void Entity::setLife(float l) {
    life += l;
    if (life < 0) life = 0;
}
