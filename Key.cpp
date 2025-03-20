#include "Key.hpp"

Key::Key() {
    // Load the Key sprite sheet (containing both frames)
    if (!textureSheet.loadFromFile("assets/texture/Interactibles/key.png")) {
        cerr << "Error loading key sprite sheet!" << endl;
    }

    sprite.setTexture(textureSheet); // ✅ Assign the correct texture

    // Set the first frame (assuming 32x32 per frame)
    frameRect = IntRect(0, 0, 32, 32);
    sprite.setTextureRect(frameRect);

    // Initialize animation variables
    frameIndex = 0;
    animationTime = 0.0f;
}

void Key::setPosPos(float x, float y) {
    sprite.setPosition({ x, y });
}

void Key::updateAnimation(float deltaTime) {
    animationTime += deltaTime;

    if (animationTime >= frameDuration) {
        animationTime = 0;
        frameIndex = (frameIndex + 1) % 2; // Toggle between frame 0 and 1
        frameRect.left = frameIndex * 32;
        sprite.setTextureRect(frameRect);
    }
}


void Key::interact(const shared_ptr<Player>& player) {
    if (!player->getHasKey()) {
        if (this->playerTryInteract()) {
            player->setHasKey(true);
            isTaken = true;
            shouldHide = true;
        }
    }
    else {
        if (this->playerTryInteract()) {
            cout << "Already have a key!" << endl;
        }
    }
}

void Key::draw(RenderWindow& window) {
    if (!isTaken) {
        window.draw(sprite);
    }
}
