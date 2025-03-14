#include "Chest.hpp"
#include "Player.hpp"

Chest::Chest(bool containsKey) : containsKey(containsKey) {
    // Load the chest texture
    setTexture("assets/texture/Interactibles/chest.png");  // Change path to your actual chest texture
    sprite.setScale(1.0f, 1.0f);  // Optional: Resize the chest sprite
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