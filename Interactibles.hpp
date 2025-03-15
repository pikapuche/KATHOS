#pragma once
#include "Player.hpp"

class Interactible {
private:
    float PROXIMITY_RANGE = 50.0f;

protected:
    sf::Sprite sprite;
    sf::Texture texture;
    bool isPlayerNear = false; // True if player is close

public:

    bool playerTryInteract();
    // Check if player is near
    virtual void updateProximity(Player& player);
    // Getter
    bool getIsPlayerNear();
    // Define a virtual function for unique interactions
    virtual void interact(Player& player) = 0;
    // Draw the interactible (optional)
    virtual void draw(sf::RenderWindow& window) = 0;

    void setTexture(const std::string& filePath);
};