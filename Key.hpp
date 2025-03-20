#pragma once
#include "Interactibles.hpp"

class Key : public Interactible {
private:
    bool isTaken = false;
    Texture textureSheet;
    IntRect frameRect; // Part of the sprite sheet to display
    float animationTime = 0.0f; // Time elapsed
    int frameIndex = 0;
    const float frameDuration = 0.5f; // 100ms per frame
    const int totalFrames = 2; // Total frames in animation
public:
    Key();

    void interact(const shared_ptr<Player>& player) override;
    void setPosPos(float x, float y);
    void draw(RenderWindow& window) override;
    void updateAnimation(float deltaTime);
};