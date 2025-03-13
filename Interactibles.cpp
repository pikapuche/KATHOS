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

