#include "Chest.hpp"

Chest::Chest() {
    // Load the chest sprite sheet (containing all frames)
    if (!textureSheet.loadFromFile("assets/texture/Interactibles/chest_opening.png")) {
        std::cerr << "Error loading chest sprite sheet!" << std::endl;
    }

    // Load final opened texture
    if (!textureOpen.loadFromFile("assets/texture/Interactibles/chest_open.png")) {
        std::cerr << "Error loading open chest texture!" << std::endl;
    }

    // Set initial texture (closed chest)
    sprite.setTexture(textureSheet);

    // Set the first frame (assuming all frames are equal-sized)
    frameRect = sf::IntRect(0, 0, 64, 64); // Adjust size based on your sprite sheet
    sprite.setTextureRect(frameRect);
}

void Chest::updateAnimation(float deltaTime) {
    if (isAnimating) {
        animationTime += deltaTime;

        // Change frame if enough time has passed
        if (animationTime >= frameDuration) {
            animationTime = 0; // Reset timer
            frameIndex++;

            if (frameIndex < totalFrames) {
                // Move to next frame in the sprite sheet
                frameRect.left = frameIndex * 64;
                sprite.setTextureRect(frameRect);
            }
            else {
                // Animation finished
                isAnimating = false;
                isOpen = true;

                // Switch to final opened texture and reset the texture rect
                sprite.setTexture(textureOpen);
                sprite.setTextureRect(sf::IntRect(0, 0, 64, 64)); // Ensure correct display
            }
        }
    }
}


void Chest::interact(const std::shared_ptr<Player>& player) {
    if (!isOpen && !isAnimating) {
        if (this->playerTryInteract()) {
            std::cout << "Chest opening animation starts!" << std::endl;
            isAnimating = true;
            frameIndex = 0;
            animationTime = 0.0f;
        }
    }
}

void Chest::setPosPos(float x, float y) {
    this->sprite.setPosition(x, y);
}


void Chest::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}