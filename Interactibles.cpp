#include "Interactibles.hpp"

Interactible::Interactible(){
    inspectGUITexture.loadFromFile("Assets/texture/UI/inspect.png");
    inspectGUI.setTexture(inspectGUITexture);
}

bool Interactible::getIsPlayerNear()
{
    return isPlayerNear; 
}

void Interactible::setTexture(const std::string& filePath) {
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Error loading texture from " << filePath << std::endl;
    }
    else {
        sprite.setTexture(texture);
    }
}

void Interactible::updateProximity(const std::shared_ptr<Player>& player, sf::RenderWindow& window)
{
    float distance = std::sqrt(
        std::pow(sprite.getPosition().x - player->getSprite().getPosition().x, 2) +
        std::pow(sprite.getPosition().y - player->getSprite().getPosition().y, 2)
    );


    isPlayerNear = (distance < PROXIMITY_RANGE);
    std::cout << "updateProximity called! Distance: " << distance << " PlayerNear: " << isPlayerNear << std::endl;

    inspectGUI.setPosition(player->getPosPos().x + guiPos.x, player->getPosPos().y - guiPos.y);

    if (isPlayerNear && !shouldHide) {
        window.draw(inspectGUI);
    }
}

bool Interactible::playerTryInteract() {
    if (isPlayerNear) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            return true;
        }
        return false;
    }
    else {
        return false;
    }
}