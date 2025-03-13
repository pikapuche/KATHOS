#pragma once
#include "Player.hpp"
#include <iostream>
#include <vector>
#include <string>

class Interactible {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    bool isPlayerNear = false; // True if player is close

public:
    virtual ~Interactible() {}

    // Check if player is near
    //virtual void updateProximity(Player& player);

    // Define a virtual function for unique interactions
    //virtual void interact(Player& player) = 0;

    // Getter
    bool getIsPlayerNear() const { return isPlayerNear; }

    // Draw the interactible (optional)
    virtual void draw(sf::RenderWindow& window) { window.draw(sprite); }

    void setTexture(const std::string& filePath);
};

class Chest : public Interactible {
private:
    std::string chestContent;
    int contentAmount;
    bool requireKey;

public:
    Chest();

    //void interact(Player& player) override; // Define interaction
    void setPosPos(float x, float y);
};