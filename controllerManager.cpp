#include "controllerManager.hpp"

Controller::Controller(){
    if (!highlightTexture.loadFromFile("assets/texture/UI/interfaceButton.png")) {
        cerr << "Failed to load highlight texture!" << endl;
    }

    highlightRect.setTexture(highlightTexture);
    highlightRect.setColor(Color(255, 255, 255, 255)); // Normal opacity
    highlightRect.setScale(0.82f, 0.82f);
    highlightRect.setOrigin(highlightTexture.getSize().x / 2, highlightTexture.getSize().y / 2);

}

void Controller::setUsingController(bool usingController) {
    isUsingController = usingController;
}

void Controller::detectControllerInput() {
    updateAxis();

    //DEBUG
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        isUsingController = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        isUsingController = true;
    }
    if (Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::D)) {
        isUsingController = false;
    }

    // Check if any joystick is connected
        for (unsigned int i = 0; i < Joystick::Count; ++i) {
            if (Joystick::isConnected(i)) {
                // Check if any button is pressed
                for (unsigned int j = 0; j < Joystick::getButtonCount(i); ++j) {
                    if (Joystick::isButtonPressed(i, j)) {
                        isUsingController = true;
                        break;
                    }
                }

                // Check if any joystick axis is moved significantly
                for (int axis = Joystick::X; axis <= Joystick::PovY; ++axis) {
                    if (abs(Joystick::getAxisPosition(i, static_cast<Joystick::Axis>(axis))) > 10) {
                        isUsingController = true;
                        break;
                    }
                }
            }
        }
}

bool Controller::getUsingController() {
    return isUsingController;
}

int Controller::getCurrentJoystickIndex() {
    return currentJoystickIndex;
}

void Controller::setCurrentJoystickIndex(int value) {
    currentJoystickIndex = value;
}

void Controller::updateAxis(){
    joystickY = sf::Joystick::getAxisPosition(0, Joystick::Y);
    if (currentJoystickIndex < 0) {
        currentJoystickIndex = 0;
    }
    if (currentJoystickIndex > 2) {
        currentJoystickIndex = 2;
    }


    if (joystickY > 90 || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (timeClock.getElapsedTime().asSeconds() > cooldown) {
            Axis = CheckAxis::DOWN;
            currentJoystickIndex += 1;
            timeClock.restart();
        }
    }
    if (joystickY < -90 || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (timeClock.getElapsedTime().asSeconds() > cooldown) {
            Axis = CheckAxis::UP;
            currentJoystickIndex -= 1;
            timeClock.restart();

        }
    }
}

Sprite Controller::getHighlight() {
    return highlightRect;
}

void Controller::updateHighlight(sf::RenderWindow& window, bool inPause, bool inGameOver) {
    switch (currentJoystickIndex) {
    case 0:
        if (!inGameOver) {
            if (!inPause)
                highlightRect.setPosition(window.getSize().x / 2 - 30, window.getSize().y / 2 - 200 + 20);
            if (inPause)
                highlightRect.setPosition(1920 / 2 - 30, 1080 / 2 - 100 + 20);
        }
        else {
            highlightRect.setPosition(1920 / 2 - 5, 1080 / 2 + 250+20);
        }
        break;
    case 1:
        if (!inGameOver) {
            if (!inPause)
                highlightRect.setPosition(window.getSize().x / 2 - 30, window.getSize().y / 2 + 20);
            if (inPause)
                highlightRect.setPosition(1920 / 2 - 30, 1080 / 2 + 100 + 20);
        }
        else {
            highlightRect.setPosition(1920 / 2 - 5, 1080 / 2 + 400+20);
        }
        break;
    case 2:
        if (!inGameOver) {
            if (!inPause)
                highlightRect.setPosition(window.getSize().x / 2 - 30, window.getSize().y / 2 + 200 + 20);
            if (inPause)
                highlightRect.setPosition(1920 / 2 - 30, 1080 / 2 + 300 + 20);
        }
        else {
            currentJoystickIndex = 0;
        }
        break;

    }
}