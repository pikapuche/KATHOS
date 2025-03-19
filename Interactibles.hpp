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
    virtual bool isDoor() const { return false; }  // Default to false for other objects

    bool playerTryInteract();
    // Check if player is near
    virtual void updateProximity(const std::shared_ptr<Player>& player);
    // Getter
    bool getIsPlayerNear();

    // Define a virtual function for unique interactions
    virtual void interact(const std::shared_ptr<Player>& player) = 0;
    // Draw the interactible (optional)
    virtual void draw(sf::RenderWindow& window) = 0;

    void setTexture(const std::string& filePath);
};