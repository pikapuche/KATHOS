#include "Interactibles.hpp"
#include "Player.hpp"


void Interactible::setTexture(const std::string& filePath) {
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Error loading texture from " << filePath << std::endl;
    }
    else {
        sprite.setTexture(texture);
    }
}

void Interactible::updateProximity(Player& player) {
    float distance = std::sqrt(
        std::pow(sprite.getPosition().x - player.getSprite().getPosition().x, 2) +
        std::pow(sprite.getPosition().y - player.getSprite().getPosition().y, 2)
    );

    isPlayerNear = (distance < PROXIMITY_RANGE); // Adjust range for proximity
}

bool Interactible::playerTryInteract() {
    if (isPlayerNear) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            return true;
        }
    }
    else {
        return false;
    }
}
