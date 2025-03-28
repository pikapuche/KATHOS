#include "Interactibles.hpp"

Interactible::Interactible(){
    inspectGUITexture.loadFromFile("Assets/texture/UI/inspect.png");
    inspectGUIxboxTexture.loadFromFile("Assets/texture/UI/inspect_xbox.png");
    inspectGUI.setTexture(inspectGUITexture);
}

bool Interactible::getIsPlayerNear()
{
    return isPlayerNear; 
}

void Interactible::setTexture(const string& filePath) {
    if (!texture.loadFromFile(filePath)) {
        cerr << "Error loading texture from " << filePath << endl;
    }
    else {
        sprite.setTexture(texture);
    }
}

void Interactible::updateProximity(const std::shared_ptr<Player>& player, sf::RenderWindow& window, Controller& controller)
{
    if (controller.getUsingController())
        inspectGUI.setTexture(inspectGUIxboxTexture);
    else
        inspectGUI.setTexture(inspectGUITexture);
        

    float distance = sqrt(
        pow(sprite.getPosition().x - player->getSprite().getPosition().x, 2) +
        pow(sprite.getPosition().y - player->getSprite().getPosition().y, 2)
    );


    isPlayerNear = (distance < PROXIMITY_RANGE);
    //std::cout << "updateProximity called! Distance: " << distance << " PlayerNear: " << isPlayerNear << std::endl;

    if (player->stateLook == 0) //Looking right
        inspectGUI.setPosition(player->getPosPos().x + guiPos.x, player->getPosPos().y - guiPos.y);
    else if (player->stateLook == 1) //looking left
        inspectGUI.setPosition(player->getPosPos().x - guiPos.x, player->getPosPos().y - guiPos.y);
}

bool Interactible::playerTryInteract() {
    if (isPlayerNear) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || Joystick::isButtonPressed(0, 3)) {
            return true;
        }
        return false;
    }
    else {
        return false;
    }
}

void Interactible::drawInspectGUI(sf::RenderWindow& window) {
    if (!shouldHide && isPlayerNear) {
        window.draw(inspectGUI);
    }
}