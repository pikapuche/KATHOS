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
    keyGUILocktexture.loadFromFile("assets/texture/UI/keyLock.png");

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

    buttons.push_back(Button(
        1920 / 2 - 75, 1080 / 2 + 250,
        200, 100, ButtonType::Retry, false,
        "assets/texture/UI/retryButton.png",
        "assets/texture/UI/retryButtonHover.png"
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
        cerr << "Error loading font!" << endl;
    }

    // Set up timer text
    timeText.setFont(timeFont);
    timeText.setCharacterSize(40);
    timeText.setFillColor(Color::White);
    timeText.setPosition(1500, 10); // Adjust position (top-right)

    keyGUI.setPosition(0, 10);
    keyGUI.setScale(0.8f, 0.8f);
    keyGUI.setTexture(keyGUItexture);

    SprintTexture.loadFromFile("Assets/texture/UI/icons/emerald.png");
    SprintLockTexture.loadFromFile("Assets/texture/UI/icons/emeraldLock.png");
    DashTexture.loadFromFile("Assets/texture/UI/icons/amethyst.png");
    DashLockTexture.loadFromFile("Assets/texture/UI/icons/amethystLock.png");
    DJumpTexture.loadFromFile("Assets/texture/UI/icons/citrine.png");
    DJumpLockTexture.loadFromFile("Assets/texture/UI/icons/citrineLock.png");

    SprintButtonTexture.loadFromFile("Assets/texture/UI/controls/shift.png");
    SprintButtonControllerTexture.loadFromFile("Assets/texture/UI/controls/RB.png");
    DashButtonTexture.loadFromFile("Assets/texture/UI/controls/A.png");
    DashButtonControllerTexture.loadFromFile("Assets/texture/UI/controls/RT.png");
    DJumpButtonTexture.loadFromFile("Assets/texture/UI/controls/space.png");
    DJumpButtonControllerTexture.loadFromFile("Assets/texture/UI/controls/A_xbox.png");

    Dash.setOrigin(Dash.getGlobalBounds().width / 2, Dash.getGlobalBounds().height / 2);
    Sprint.setOrigin(Sprint.getGlobalBounds().width / 2, Sprint.getGlobalBounds().height / 2);
    DJump.setOrigin(DJump.getGlobalBounds().width / 2, DJump.getGlobalBounds().height / 2);
    DashButton.setOrigin(DashButton.getGlobalBounds().width / 2, DashButton.getGlobalBounds().height / 2);
    SprintButton.setOrigin(SprintButton.getGlobalBounds().width / 2, SprintButton.getGlobalBounds().height / 2);
    DJumpButton.setOrigin(DJumpButton.getGlobalBounds().width / 2, DJumpButton.getGlobalBounds().height / 2);


    Sprint.setPosition(60, 25);
    Dash.setPosition(110, 25);
    DJump.setPosition(160,25);
    SprintButton.setPosition(Sprint.getPosition().x+10, Sprint.getPosition().y + 50);
    DashButton.setPosition(Dash.getPosition().x+10, Dash.getPosition().y + 50);
    DJumpButton.setPosition(DJump.getPosition().x+10, DJump.getPosition().y + 50);
    //Sprint.setScale(1.5f, 1.5f);
    //Dash.setScale(1.5f, 1.5f);
    //DJump.setScale(1.5f, 1.5f);

}
void Interface::updateInterface(RenderWindow& window, Player& player, Controller& controller) {

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
                                totalElapsedTime = Time::Zero; // Reset elapsed time
                                timeClock.restart();  // Restart the timer
                                return;
                            }
                        }
                    }
                }
            }
            else if (controller.getUsingController()) {
                controller.updateHighlight(window, true, false);
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
                if (button.getType() == ButtonType::Exit)
                    button.setPos(1920 / 2 - 100, 1080 / 2 + 300);
                if (button.getType() != ButtonType::Retry)
                    button.draw(window);
            }
            if (controller.getUsingController()) {
                window.draw(controller.getHighlight());
            }
        }
        DJumpButton.setTexture(controller.getUsingController() ? DJumpButtonControllerTexture : DJumpButtonTexture);
        DashButton.setTexture(controller.getUsingController() ? DashButtonControllerTexture : DashButtonTexture);
        SprintButton.setTexture(controller.getUsingController() ? SprintButtonControllerTexture : SprintButtonTexture);
        Sprint.setTexture(player.getIsTakeSpeed() ? SprintTexture : SprintLockTexture);
        DJump.setTexture(player.getIsTakeJump() ? DJumpTexture : DJumpLockTexture);
        keyGUI.setTexture(player.getHasKey() ? keyGUItexture : keyGUILocktexture);

        if (player.getIsTakeDash()) {
            Dash.setTexture(DashTexture);
            if (!isPaused)
            window.draw(DashButton);
        }
        if (player.getIsTakeJump()) {
            DJump.setTexture(DJumpTexture);
            if (!isPaused)
            window.draw(DJumpButton);
        }
        if (player.getIsTakeSpeed()) {
            Sprint.setTexture(SprintTexture);
            if (!isPaused)
            window.draw(SprintButton);
        }
        else if (!player.getIsTakeDash()) {
            Dash.setTexture(DashLockTexture);
        }
        else if (!player.getIsTakeJump()) {
            DJump.setTexture(DJumpLockTexture);
        }
        else if (!player.getIsTakeSpeed()) {
            Sprint.setTexture(SprintLockTexture);
        }
        if (!isPaused) {
            window.draw(Dash);
            window.draw(Sprint);
            window.draw(DJump);
            window.draw(keyGUI);
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
        if (hasWon) {
            timeText.setString("Time: " + to_string(finalTime.asSeconds()));
        }
        else if (isPaused && !wasPaused) {
            totalElapsedTime += timeClock.getElapsedTime();
        }
        else if (wasPaused) {
            timeClock.restart(); // Restart the clock fresh after unpausing
        }

        wasPaused = isPaused;

        sf::Time elapsed = totalElapsedTime;
        if (!isPaused) {
            elapsed += timeClock.getElapsedTime();
        }

        if (hasWon && finalTime.asSeconds() == 0) {
            finalTime = elapsed;
        }

        int minutes = static_cast<int>(elapsed.asSeconds()) / 60;
        int seconds = static_cast<int>(elapsed.asSeconds()) % 60;
        int milliseconds = static_cast<int>(elapsed.asMilliseconds() % 1000);

    // Format time
    timeText.setString("Time: " + to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds) + ":" + to_string(milliseconds));

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

Time Interface::getFinalTime() const
{
    return finalTime;
}

void Interface::setWinCondition(bool win)
{
    hasWon = win;
}

bool Interface::getGameStarted()  const {
    return gameStarted;
}

void Interface::updateGameOver(sf::RenderWindow& window, Controller& controller) {
    if (hasWon) {
        for (size_t i = 0; i < buttons.size(); ++i) {
            // If using mouse, highlight hovered button
            buttons[i].setTexture(buttons[i].isHovered(window));
        }
        if (!controller.getUsingController()) {
            if (Mouse::isButtonPressed(Mouse::Left)) {
                for (auto& button : buttons) {
                    if (button.isHovered(window)) {
                        switch (button.getType()) {
                        case ButtonType::Retry:
                            shouldRestart = true; // New flag to signal a restart
                            totalElapsedTime = sf::Time::Zero; // Reset elapsed time
                            hasWon = false;
                            timeClock.restart();  // Restart the timer
                            break;
                        case ButtonType::Exit:
                            window.close();
                            break;
                        }
                    }
                }
            }
        }
        else if (controller.getUsingController()) {
            controller.updateHighlight(window, true, true);
            if (Joystick::isButtonPressed(0, 0) || sf::Keyboard::isKeyPressed(Keyboard::Enter)) {
                switch (controller.getCurrentJoystickIndex()) {
                case 0:
                    for (auto& button : buttons) {
                        if (button.getType() == ButtonType::Exit)
                            button.setPos(1920 / 2 - 100, 1080 / 2 + 300);
                    }
                    shouldRestart = true; // New flag to signal a restart
                    totalElapsedTime = sf::Time::Zero; // Reset elapsed time
                    hasWon = false;
                    timeClock.restart();  // Restart the timer
                    break;
                case 1:
                    window.close();
                    break;
                }
            }
        }

        for (auto& button : buttons) {
            if (button.getType() == ButtonType::Retry || button.getType() == ButtonType::Exit) {
                if (button.getType() == ButtonType::Exit)
                    button.setPos(1920 / 2 - 75, 1080 / 2 + 400);
                button.draw(window);
            }
        }
        if (controller.getUsingController() && !shouldRestart) {
            window.draw(controller.getHighlight());
        }
    }
}