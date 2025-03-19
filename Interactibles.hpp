#pragma once
#include "Player.hpp"

class Interactible {
private:
    float PROXIMITY_RANGE = 50.0f;

protected:
    Sprite sprite;
    Texture texture;
    bool isPlayerNear = false; // True if player is close

public:
    virtual bool isDoor() const { return false; }  // Default to false for other objects

    bool playerTryInteract();
    // Check if player is near
    virtual void updateProximity(const shared_ptr<Player>& player);
    // Getter
    bool getIsPlayerNear();

    // Define a virtual function for unique interactions
    virtual void interact(const shared_ptr<Player>& player) = 0;
    // Draw the interactible (optional)
    virtual void draw(RenderWindow& window) = 0;

    void setTexture(const string& filePath);
};