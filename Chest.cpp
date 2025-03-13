#include "Chest.hpp"

Chest::Chest() {
    // Load the chest texture
    setTexture("assets/texture/Interactibles/chest.png");  // Change path to your actual chest texture
    sprite.setScale(1.0f, 1.0f);  // Optional: Resize the chest sprite
}


//void Chest::interact(Player& player) {
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
//        if (isPlayerNear) {
//            if (requireKey && !player.getHasKey()) {
//                std::cout << "Chest is locked! You need a key." << std::endl;
//            }
//            else {
//                std::cout << "You opened the chest and found " << contentAmount << " " << chestContent << "!" << std::endl;
//            }
//        }
//    }
//}

void Chest::setPosPos(float x, float y) {
    sprite.setPosition({ x,y });
}