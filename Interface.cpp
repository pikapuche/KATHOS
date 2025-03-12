#include "Interface.hpp"
#include <iostream>

PauseOverlay::PauseOverlay() {
    //overlay.setColor(sf::Color(255, 255, 255, 150)); // Slight transparency
}

void PauseOverlay::setTexture(const std::string& texturePath) {
    if (!overlayTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load pause overlay texture from: " << texturePath << std::endl;
    }
    else {
        overlay.setTexture(overlayTexture);
    }
}

void PauseOverlay::draw(sf::RenderWindow& window) {
    window.draw(overlay);
}

bool Interface::getIsPaused() {
	return isPaused;
}

void Interface::setIsPaused(bool paused) {
	isPaused = paused;
}

void Interface::initInterface() {
    pauseOverlay.setTexture("assets/texture/UI/pausedOverlay.png");

    buttons.push_back(Button(
        1920 / 2 - 100, 1080 / 2 - 100,
        200, 100, ButtonType::Resume, false,
        "assets/texture/UI/resumeButton.png",
        "assets/texture/UI/resumeButtonHover.png"
    ));

    buttons.push_back(Button(
        1920 / 2 - 100, 1080 / 2 + 100,
        200, 100, ButtonType::Restart, false,
        "assets/texture/UI/RestartButton.png",
        "assets/texture/UI/RestartButtonHover.png"
    ));

    buttons.push_back(Button(
        1920 / 2 - 100, 1080 / 2 + 300,
        200, 100, ButtonType::Exit, false,
        "assets/texture/titlescreen/buttons/ExitButton.png",
        "assets/texture/titlescreen/buttons/ExitButtonHover.png"
    ));
}

void Interface::updateInterface(sf::RenderWindow& window) {
    if (isPaused) { //Only if paused
        pauseOverlay.draw(window);

        for (auto& button : buttons) {
            if (button.isHovered(window)) {
                button.setTexture(true);
            }
            else {
                button.setTexture(false);
            }

            // FIX: Only trigger when the mouse button is released
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (button.isHovered(window)) {  // Ensure the mouse is over the button
                    switch (button.getType()) {
                    case ButtonType::Resume:
                        isPaused = false;
                        return;
                    case ButtonType::Exit:
                        window.close();
                        return;
                    case ButtonType::Restart:
                        shouldRestart = true; // New flag to signal a restart
                        isPaused = false; // Unpause when restarting
                        return;
                    }
                }
            }

            button.draw(window);
        }
    }
}

bool Interface::getShouldRestart() const{
    return shouldRestart;
}
void Interface::resetRestartFlag() {
    shouldRestart = false;
}

void Interface::setUsingController(bool usingController) {
	isUsingController = usingController;
}

bool Interface::getUsingController() {
	return isUsingController;
}