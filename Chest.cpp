#include "Chest.hpp"

Chest::Chest(/*bool containsKey) : containsKey(containsKey)*/) {
    // Load the chest texture
    texture.loadFromFile("assets/texture/Interactibles/chest.png");
    sprite.setTexture(texture);
}

void Chest::interact(Player& player) {
    if (this->playerTryInteract()) {
        if (!containsKey)
            std::cout << "Chest opens" << std::endl;
        else if (containsKey) {
            std::cout << "Chest opens, key obtained" << std::endl;
            player.setHasKey(true);
        }
    }
}

void Chest::setPosPos(float x, float y) {
    sprite.setPosition({ x,y });
}

void Chest::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}