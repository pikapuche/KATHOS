#pragma once
#include "Interactibles.hpp"

class Chest : public Interactible {
private:
    bool isOpen = false;
    bool isAnimating = false;
    bool containsKey;

    Texture textureOpen;
    Texture textureSheet;
    IntRect frameRect; // Part of the sprite sheet to display
    float animationTime = 0.0f; // Time elapsed
    int frameIndex = 0;
    const float frameDuration = 0.1f; // 100ms per frame
    const int totalFrames = 10; // Total frames in animation

public:
    Chest();

    void interact(const shared_ptr<Player>& player) override;
    void setPosPos(float x, float y);
    void updateAnimation(float deltaTime);
    // Draw the interactible (optional)
    void draw(RenderWindow& window) override;
};
