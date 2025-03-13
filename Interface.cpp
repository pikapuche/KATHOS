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

    // Highlight rectangle for selection
    if (!highlightTexture.loadFromFile("assets/texture/UI/interfaceButton.png")) {
        std::cerr << "Failed to load interface button texture!" << std::endl;
    }
	highlightRect.setScale(0.82f, 0.82f);
    highlightRect.setTexture(highlightTexture);
    highlightRect.setColor(sf::Color(255, 255, 255, 255)); // Semi-transparent overlay
	highlightRect.setOrigin(highlightRect.getGlobalBounds().width / 2, highlightRect.getGlobalBounds().height / 2);
}
void Interface::updateInterface(sf::RenderWindow& window) {
    detectControllerInput(); // Detect controller usage
    handleMenuNavigation();  // Handle button navigation

    if (isPaused) { // Only if paused
        pauseOverlay.draw(window);

        for (size_t i = 0; i < buttons.size(); ++i) {
            if (isUsingController) {
                // If using controller, highlight only the selected button
                buttons[i].setTexture(false);
			}
            else {
                // If using mouse, highlight hovered button
                buttons[i].setTexture(buttons[i].isHovered(window));
            }
        }

        // Handle button selection when pressing Enter / A button
        if (isUsingController) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Joystick::isButtonPressed(0, 0)) {
                switch (buttons[selectedButtonIndex].getType()) {
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
        else if (!isUsingController) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                for (auto& button : buttons) {
                    if (button.isHovered(window)) {
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
            }
        }

        // Draw all buttons
        for (auto& button : buttons) {
            button.draw(window);
        }
        if (isUsingController) {
            // Draw highlight rectangle on selected button
            highlightRect.setPosition(buttons[selectedButtonIndex].getPosition().x + 50, buttons[selectedButtonIndex].getPosition().y + 25);
            window.draw(highlightRect);
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

void Interface::detectControllerInput() {

    //DEBUG
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        setUsingController(true);
	}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        setUsingController(true);
    }
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        setUsingController(false);
	}

    // Check if any joystick is connected
    for (unsigned int i = 0; i < sf::Joystick::Count; ++i) {
        if (sf::Joystick::isConnected(i)) {
            // Check if any button is pressed
            for (unsigned int j = 0; j < sf::Joystick::getButtonCount(i); ++j) {
                if (sf::Joystick::isButtonPressed(i, j)) {
                    setUsingController(true);
                    break;
                }
            }

            // Check if any joystick axis is moved significantly
            for (int axis = sf::Joystick::X; axis <= sf::Joystick::PovY; ++axis) {
                if (std::abs(sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(axis))) > 10) {
                    setUsingController(true);
                    break;
                }
            }
        }
    }
}

void Interface::handleMenuNavigation() {
    static bool upPressed = false;
    static bool downPressed = false;

    bool moveUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Joystick::isButtonPressed(0, 11);
    bool moveDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Joystick::isButtonPressed(0, 12);

    // Navigate up
    if (moveUp && !upPressed) {
        selectedButtonIndex = (selectedButtonIndex - 1 + buttons.size()) % buttons.size();
        upPressed = true;
    }
    if (!moveUp) upPressed = false;

    // Navigate down
    if (moveDown && !downPressed) {
        selectedButtonIndex = (selectedButtonIndex + 1) % buttons.size();
        downPressed = true;
    }
    if (!moveDown) downPressed = false;

    // Move highlight rectangle
    highlightRect.setPosition(buttons[selectedButtonIndex].getPosition());
}
