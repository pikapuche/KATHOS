#include "Interactibles.hpp"

void Interactible::setTexture(const std::string& filePath) {
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Error loading texture from " << filePath << std::endl;
    }
    else {
        sprite.setTexture(texture);
    }
}

//void Interactible::updateProximity(Player& player) {
//    sf::Vector2f playerPos = player.getPosPos();
//    sf::Vector2f spritePos = sprite.getPosition();
//
//    float distance = std::sqrt(std::pow(playerPos.x - spritePos.x, 2) + std::pow(playerPos.y - spritePos.y, 2));
//
//    // Define a threshold for "close enough"
//    isPlayerNear = (distance < 100.0f); // Adjust the range as needed
//}

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