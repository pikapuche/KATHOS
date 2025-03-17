#include "Interface.hpp"

PauseOverlay::PauseOverlay() {
    //overlay.setColor(Color(255, 255, 255, 150)); // Slight transparency
}

void PauseOverlay::setTexture(const string& texturePath) {
    if (!overlayTexture.loadFromFile(texturePath)) {
        cerr << "Failed to load pause overlay texture from: " << texturePath << endl;
    }
    else {
        overlay.setTexture(overlayTexture);
    }
}

void PauseOverlay::draw(RenderWindow& window) {
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
        cerr << "Failed to load interface button texture!" << endl;
    }
	highlightRect.setScale(0.82f, 0.82f);
    highlightRect.setTexture(highlightTexture);
    highlightRect.setColor(Color(255, 255, 255, 255)); // Semi-transparent overlay
	highlightRect.setOrigin(highlightRect.getGlobalBounds().width / 2, highlightRect.getGlobalBounds().height / 2);
}
void Interface::updateInterface(RenderWindow& window) {
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
            if (Keyboard::isKeyPressed(Keyboard::Enter) || Joystick::isButtonPressed(0, 0)) {
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
            if (Mouse::isButtonPressed(Mouse::Left)) {
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
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
        setUsingController(true);
	}
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        setUsingController(true);
    }
	if (Mouse::isButtonPressed(Mouse::Left)) {
        setUsingController(false);
	}

    // Check if any joystick is connected
    for (unsigned int i = 0; i < Joystick::Count; ++i) {
        if (Joystick::isConnected(i)) {
            // Check if any button is pressed
            for (unsigned int j = 0; j < Joystick::getButtonCount(i); ++j) {
                if (Joystick::isButtonPressed(i, j)) {
                    setUsingController(true);
                    break;
                }
            }

            // Check if any joystick axis is moved significantly
            for (int axis = Joystick::X; axis <= Joystick::PovY; ++axis) {
                if (abs(Joystick::getAxisPosition(i, static_cast<Joystick::Axis>(axis))) > 10) {
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

    bool moveUp = Keyboard::isKeyPressed(Keyboard::Up) || Joystick::isButtonPressed(0, 11);
    bool moveDown = Keyboard::isKeyPressed(Keyboard::Down) || Joystick::isButtonPressed(0, 12);

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
