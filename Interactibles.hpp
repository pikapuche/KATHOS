#pragma once
#include "stdafx.hpp"
#include <iostream>
#include <vector>
#include <string>

class Player;


class Interactible {
private:
    float PROXIMITY_RANGE = 50.0f;

protected:
    sf::Sprite sprite;
    sf::Texture texture;
    bool isPlayerNear = false; // True if player is close

public:
    virtual ~Interactible() {}

    bool playerTryInteract();

    // Check if player is near
    virtual void updateProximity(Player& player);

    // Define a virtual function for unique interactions
    virtual void interact(Player& player) = 0;

    // Getter
    bool getIsPlayerNear() const { return isPlayerNear; }

    // Draw the interactible (optional)
    virtual void draw(sf::RenderWindow& window) { window.draw(sprite); }

    void setTexture(const std::string& filePath);
};