#include "MainScreen.hpp"

bool MainScreen::getIsInMenu() {
    return isInMenu;
}

void MainScreen::setIsInMenu(bool menu) {
    isInMenu = menu;
}

void MainScreen::initMenu(RenderWindow& window) {
    if (!backgroundTexture.loadFromFile("assets/texture/titlescreen/background.png")) {
        cerr << "Failed to load background texture!" << endl;
    }

    background.setScale(Vector2f(1.0f,1.0f));
    background.setTexture(backgroundTexture);

    buttons.push_back(Button(
        window.getSize().x / 2 - 100, window.getSize().y / 2 - 200,
		200, 100, ButtonType::Play, false,
        "assets/texture/titlescreen/buttons/playButton.png",
        "assets/texture/titlescreen/buttons/playButtonHover.png"
    ));

    buttons.push_back(Button(
        window.getSize().x / 2 - 100, window.getSize().y / 2 + 200,
        200, 100, ButtonType::Exit, false,
        "assets/texture/titlescreen/buttons/ExitButton.png",
        "assets/texture/titlescreen/buttons/ExitButtonHover.png"
    ));

    buttons.push_back(Button(
        window.getSize().x / 2 - 100, window.getSize().y / 2,
        200, 100, ButtonType::Settings, false,
        "assets/texture/titlescreen/buttons/SettingsButton.png",
        "assets/texture/titlescreen/buttons/SettingsButtonHover.png"
    ));

    buttons.push_back(Button(
        window.getSize().x / 2 - 100, window.getSize().y / 2 + -100,
        200, 100, ButtonType::Sound, true,
        "assets/texture/titlescreen/buttons/settings/soundButton.png",
        "assets/texture/titlescreen/buttons/settings/soundButtonHover.png"
    ));

    buttons.push_back(Button(
        window.getSize().x / 2 - 100, window.getSize().y / 2 + 300,
        200, 100, ButtonType::Return, true,
        "assets/texture/titlescreen/buttons/settings/returnButton.png",
        "assets/texture/titlescreen/buttons/settings/returnButtonHover.png"
    ));

    if (!highlightTexture.loadFromFile("assets/texture/UI/interfaceButton.png")) {
        cerr << "Failed to load highlight texture!" << endl;
    }

    highlightRect.setTexture(highlightTexture);
    highlightRect.setColor(Color(255, 255, 255, 255)); // Normal opacity
    highlightRect.setScale(0.82f, 0.82f);
    highlightRect.setOrigin(highlightTexture.getSize().x / 2, highlightTexture.getSize().y / 2);



    soundTilterTexture.loadFromFile("assets/texture/titlescreen/sound/gem.png");
    soundTilterControllerTexture.loadFromFile("assets/texture/titlescreen/sound/gemController.png");
    soundBarTexture.loadFromFile("assets/texture/titlescreen/sound/bar.png");

    soundTilter.setTexture(soundTilterTexture);
    soundBar.setTexture(soundBarTexture);
    soundTilter.setOrigin(soundTilter.getGlobalBounds().width / 2, soundTilter.getGlobalBounds().height / 2);
    soundBar.setOrigin(soundBar.getGlobalBounds().width / 2, soundBar.getGlobalBounds().height / 2);
    soundBar.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    soundTilter.setPosition(soundBar.getGlobalBounds().width/2, soundBar.getPosition().y);
        
}

void MainScreen::handleSound(RenderWindow& window) {

}

void MainScreen::handleButtonPress(Button& button) {
    if (!button.getisHidden()) {
        switch (button.getType()) {
        case ButtonType::Play:
            interfaceuh.resetTime();
            isInMenu = false; //Start Game
            interfaceuh.setGameStarted(true);
            break;
        case ButtonType::Exit:
            if (clickCooldown.getElapsedTime().asSeconds() > cooldownTime) {
                exit(0); // Use exit(0) instead of window.close()
            }
            break;
        case ButtonType::Settings:
            isInSettings = true;
			selectedButtonIndex = 3; // Set selected button to first in settings
            break;
        case ButtonType::Return:
            clickCooldown.restart();
            selectedButtonIndex = 2;
            if (settingSound)
                settingSound = false;
            else if (!settingSound)
                isInSettings = false;
            break;
        }
    }
}



void MainScreen::handleControllerNavigation() {
    static bool upPressed = false;
    static bool downPressed = false;
    static bool selectPressed = false;

    bool moveUp = Keyboard::isKeyPressed(Keyboard::Up) || Joystick::isButtonPressed(0, 11);
    bool moveDown = Keyboard::isKeyPressed(Keyboard::Down) || Joystick::isButtonPressed(0, 12);
    bool select = Keyboard::isKeyPressed(Keyboard::Enter) || Joystick::isButtonPressed(0, 0);

    // Get only visible buttons
    vector<int> visibleButtonIndices;
    for (size_t i = 0; i < buttons.size(); ++i) {
        if (!buttons[i].getisHidden()) {
            visibleButtonIndices.push_back(i);
        }
    }

    if (visibleButtonIndices.empty()) return; // No buttons to navigate

    // Ensure selected index is always within the visible buttons
    auto findCurrentIndex = find(visibleButtonIndices.begin(), visibleButtonIndices.end(), selectedButtonIndex);
    int currentIndex = (findCurrentIndex != visibleButtonIndices.end()) ? distance(visibleButtonIndices.begin(), findCurrentIndex) : 0;

    // Navigate up
    if (moveUp && !upPressed) {
        currentIndex = (currentIndex +1 + visibleButtonIndices.size()) % visibleButtonIndices.size();
        selectedButtonIndex = visibleButtonIndices[currentIndex];
        upPressed = true;
    }
    if (!moveUp) upPressed = false;

    // Navigate down
    if (moveDown && !downPressed) {
        currentIndex = (currentIndex -1 + visibleButtonIndices.size()) % visibleButtonIndices.size();
        selectedButtonIndex = visibleButtonIndices[currentIndex];
        downPressed = true;
    }
    if (!moveDown) downPressed = false;

    // Select button
    if (select && !selectPressed) {
        handleButtonPress(buttons[selectedButtonIndex]);
        selectPressed = true;
    }
    if (!select) selectPressed = false;
}




void MainScreen::updateMenu(RenderWindow& window) {
    if (isInMenu) {
        interfaceuh.setGameStarted(false);
        cout << "interface game started" << endl;
    }
    interfaceuh.detectControllerInput();
    bool usingController = interfaceuh.getUsingController();
    if (usingController) {
        handleControllerNavigation();
    }

    window.draw(background);
    if (!interfaceuh.getUsingController()) {
        for (auto& button : buttons) {
            if (button.isHovered(window)) {
                button.setTexture(true);

                //Check when button click
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (!button.getisHidden()) {
                        cout << "Button clicked" << endl;
                        switch (button.getType()) { //Check button type in Menu
                        case ButtonType::Play:
                            interfaceuh.resetTime();
                            isInMenu = false; //Start Game
                            interfaceuh.setGameStarted(true);
                            break;
                        case ButtonType::Exit:
                            if (clickCooldown.getElapsedTime().asSeconds() > cooldownTime)
                                window.close(); //Exit Game
                            break;

                        case ButtonType::Settings:
                            isInSettings = true; //Settings Menu
                            break;
                        case ButtonType::Return:
                            clickCooldown.restart();
                            if (!settingSound)
                                isInSettings = false; //Return to Main Menu
                            else if (settingSound)
                                settingSound = false;
                            break;
                        case ButtonType::Sound:
                            settingSound = true;
                        }
                        
                    }
                }
            }
            else {
                button.setTexture(false);
            }
        }
    }
    for (auto& button : buttons) {
        if (isInSettings) {
            if (button.isInSettings()) {
                if (!settingSound) {
                    button.setHidden(false);
                    button.draw(window);
                }
                else {
                    for (auto& button : buttons) {
                        if (button.getType() == ButtonType::Return) {
                            button.draw(window);
                        }
                    }
                    window.draw(soundTilter);
                    window.draw(soundBar);
                }
            }
			else if (!button.isInSettings()) {
				button.setHidden(true);
			}
        }
        else if (!isInSettings) {
            if (!button.isInSettings()) {
				button.setHidden(false);
                button.draw(window);
            }
			else if (button.isInSettings()) {
				button.setHidden(true);
			}
        }
    }
    if (interfaceuh.getUsingController()) {
        Vector2f buttonPos = buttons[selectedButtonIndex].getPosition();

        // Fix: Center highlight based on button size
        highlightRect.setPosition(buttonPos.x + buttons[selectedButtonIndex].getWidth() / 2 - 80,
            buttonPos.y + buttons[selectedButtonIndex].getHeight() / 2 - 40);

        window.draw(highlightRect);
    }
}

void MainScreen::destroyAll() {
	buttons.clear();
}
