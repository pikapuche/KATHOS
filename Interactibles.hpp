#pragma once
#include "Player.hpp"
#include "controllerManager.hpp"

class Interactible {
private:
    float PROXIMITY_RANGE = 50.0f;
    sf::Vector2f guiPos = { 20.0f, 70.0f };


protected:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Sprite inspectGUI;
    sf::Texture inspectGUITexture;
    sf::Texture inspectGUIxboxTexture;
    bool isPlayerNear = false; // True if player is close
    bool shouldHide = false;

public:
    Interactible();

    virtual bool isDoor() const { return false; }  // Default to false for other objects

    bool playerTryInteract();
    // Check if player is near
    virtual void updateProximity(const std::shared_ptr<Player>& player, RenderWindow& window, Controller& controller);
    // Getter
    bool getIsPlayerNear();

    // Define a virtual function for unique interactions
    virtual void interact(const shared_ptr<Player>& player) = 0;
    // Draw the interactible (optional)
    virtual void draw(RenderWindow& window) = 0;
    void setTexture(const std::string& filePath);
    void drawInspectGUI(sf::RenderWindow& window);
};