#include "Key.hpp"

Key::Key(){
    // Load the Key texture
    texture.loadFromFile("assets/texture/Interactibles/key.png");
    sprite.setTexture(texture);
}

void Key::setPosPos(float x, float y) {
    sprite.setPosition({ x, y });
}

void Key::interact(Player& player) {
    if (!player.getHasKey()) {
        if (this->playerTryInteract()) {
            player.setHasKey(true);
        }
    }
    else if (player.getHasKey()) {
        if (this->playerTryInteract()) {
            std::cout << "Already have a key!" << std::endl;
        }
    }
}

void Key::draw(RenderWindow& window)
{
    window.draw(sprite);
}