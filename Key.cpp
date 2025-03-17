#include "Key.hpp"
#include "Player.hpp"

Key::Key(){
    // Load the Key texture
    //setTexture("assets/texture/Interactibles/chest.png");
    sprite.setScale(1.0f, 1.0f);
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