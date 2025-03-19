#include "Interactibles.hpp"

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

void Interactible::updateProximity(const shared_ptr<Player>& player)
{
    float distance = sqrt(
        pow(sprite.getPosition().x - player->getSprite().getPosition().x, 2) +
        pow(sprite.getPosition().y - player->getSprite().getPosition().y, 2)
    );


    isPlayerNear = (distance < PROXIMITY_RANGE); // Adjust range for proximity
}

bool Interactible::playerTryInteract() {
    if (isPlayerNear) {
        if (Keyboard::isKeyPressed(Keyboard::E)) {
            return true;
        }
        return false;
    }
    else {
        return false;
    }
}