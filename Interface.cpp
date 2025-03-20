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
    keyGUItexture.loadFromFile("assets/texture/UI/key.png");

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

    // Load font
    if (!timeFont.loadFromFile("Assets/Fonts/Minecraft.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    // Set up timer text
    timeText.setFont(timeFont);
    timeText.setCharacterSize(40);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(1500, 10); // Adjust position (top-right)

    keyGUI.setPosition(0, 10);
    keyGUI.setTexture(keyGUItexture);
}
void Interface::updateInterface(RenderWindow& window, Player& player, Controller& controller) {

    if (player.getHasKey()) {
        window.draw(keyGUI);
    }

    if (isPaused) { // Only if paused
        pauseOverlay.draw(window);

        for (size_t i = 0; i < buttons.size(); ++i) {
                // If using mouse, highlight hovered button
                buttons[i].setTexture(buttons[i].isHovered(window));
        }
        if (!controller.getUsingController()) {
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
                            totalElapsedTime = sf::Time::Zero; // Reset elapsed time
                            timeClock.restart();  // Restart the timer
                            return;
                        }
                    }
                }
            }
        }
        else if (controller.getUsingController()) {
            controller.updateHighlight(window, true);
            if (Joystick::isButtonPressed(0, 0) || sf::Keyboard::isKeyPressed(Keyboard::Enter)) {
                switch (controller.getCurrentJoystickIndex()) {
                case 0:
                    isPaused = false;
                    return;
                case 1:
                    shouldRestart = true; // New flag to signal a restart
                    isPaused = false; // Unpause when restarting
                    totalElapsedTime = sf::Time::Zero; // Reset elapsed time
                    timeClock.restart();  // Restart the timer
                    return;
                case 2:
                    window.close();
                    return;
                }
            }
        }

        // Draw all buttons
        for (auto& button : buttons) {
            button.draw(window);
        }
        if (controller.getUsingController()) {
            window.draw(controller.getHighlight());
        }
    }

}



bool Interface::getShouldRestart() const{
    return shouldRestart;
}
void Interface::resetRestartFlag() {
    shouldRestart = false;
}

void Interface::updateTimer(sf::RenderWindow& window) {
    // Only update the timer if the game has started.
    if (!gameStarted) {
        // Option 1: Do nothing (timer stays at 0)
        // Option 2: Reset the timer continuously:
        timeClock.restart();
        totalElapsedTime = sf::Time::Zero;
        return;
    }
    else if (gameStarted) {

        // Timer update code (same as before)
        static bool wasPaused = false;    // Track previous pause state
        if (isPaused) {
            if (!wasPaused) {
                totalElapsedTime += timeClock.getElapsedTime();
            }
        }
        else {
            if (wasPaused) {
                timeClock.restart();
            }
        }
        wasPaused = isPaused;

        sf::Time elapsed = totalElapsedTime;
        if (!isPaused) {
            elapsed += timeClock.getElapsedTime();
        }

        int minutes = static_cast<int>(elapsed.asSeconds()) / 60;
        int seconds = static_cast<int>(elapsed.asSeconds()) % 60;
        int milliseconds = static_cast<int>(elapsed.asMilliseconds() % 1000);

        timeText.setString("Time: " + std::to_string(minutes) + ":" +
            (seconds < 10 ? "0" : "") + std::to_string(seconds) + ":" +
            std::to_string(milliseconds));
        window.draw(timeText);
    }
}

void Interface::resetTime() {
    timeClock.restart();
    totalElapsedTime = sf::Time::Zero;
}

void Interface::setGameStarted(bool started) {
    gameStarted = started;
    if (!gameStarted) {
        // Reset the timer so it stays at 0 while in the menu.
        timeClock.restart();
        totalElapsedTime = sf::Time::Zero;
    }
    //cout << "successfully set" << endl;
}

bool Interface::getGameStarted()  const {
    return gameStarted;
}