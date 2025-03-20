#include "MainScreen.hpp"

MainScreen::MainScreen(sf::Music& musicRef) : music(musicRef) {

} // Pass music reference


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
        window.getSize().x / 2 - 100, window.getSize().y / 2 + -200,
        200, 100, ButtonType::Sound, true,
        "assets/texture/titlescreen/buttons/settings/soundButton.png",
        "assets/texture/titlescreen/buttons/settings/soundButtonHover.png"
    ));

    buttons.push_back(Button(
        window.getSize().x / 2 - 100, window.getSize().y / 2 + 200,
        200, 100, ButtonType::Return, true,
        "assets/texture/titlescreen/buttons/settings/returnButton.png",
        "assets/texture/titlescreen/buttons/settings/returnButtonHover.png"
    ));


    soundTilterTexture.loadFromFile("assets/texture/titlescreen/sound/gem.png");
    soundTilterControllerTexture.loadFromFile("assets/texture/titlescreen/sound/gemController.png");
    soundBarTexture.loadFromFile("assets/texture/titlescreen/sound/bar.png");

    soundTilter.setTexture(soundTilterTexture);
    soundBar.setTexture(soundBarTexture);
    soundTilter.setOrigin(soundTilter.getLocalBounds().width / 2, soundTilter.getLocalBounds().height / 2);
    soundBar.setOrigin(soundBar.getGlobalBounds().width / 2, soundBar.getGlobalBounds().height / 2);
    soundBar.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    soundTilter.setPosition(soundBar.getPosition().x, soundBar.getPosition().y-5);


    soundBarFiller.setSize(Vector2f(0, soundBar.getGlobalBounds().height));
    soundBarFiller.setFillColor(Color(100, 255, 100, 255));
    soundBarFiller.setPosition(soundBar.getPosition().x+35 - soundBar.getGlobalBounds().width / 2,
        soundBar.getPosition().y - soundBar.getGlobalBounds().height / 2+15);

    soundBarFillerBG.setSize(Vector2f(0, soundBar.getGlobalBounds().height));
    soundBarFillerBG.setFillColor(Color(37, 37, 37, 255));
    soundBarFillerBG.setPosition(soundBar.getPosition().x+35 - soundBar.getGlobalBounds().width / 2,
        soundBar.getPosition().y - soundBar.getGlobalBounds().height / 2 + 15);
    soundBarFillerBG.setSize(Vector2f(soundBar.getGlobalBounds().width-65 , soundBar.getGlobalBounds().height - 40));

        
}

void MainScreen::handleSound(RenderWindow& window, Controller& controller) {
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    bool hoveredTilter = soundTilter.getGlobalBounds().contains(mousePos);

    static bool dragging = false;
    if (hoveredTilter && Mouse::isButtonPressed(Mouse::Left)) {
        dragging = true;
    }
    else {
        dragging = false;
    }

    if (controller.getUsingController()) {
        soundTilter.setTexture(soundTilterControllerTexture);
    }
    else {
        soundTilter.setTexture(soundTilterTexture);
    }
    if (dragging) {
        float barLeft = soundBar.getPosition().x + 35 - soundBar.getGlobalBounds().width / 2;
        float barRight = soundBar.getPosition().x - 35 + soundBar.getGlobalBounds().width / 2;

        float newX = mousePos.x;
        newX = std::max(barLeft, std::min(newX, barRight));

        soundTilter.setPosition(newX, soundBar.getPosition().y - 5);

        float volumePercent = ((newX - barLeft) / (barRight - barLeft)) * 100.0f;
        music.setVolume(volumePercent);

        float fillerWidth = ((newX - barLeft) / (barRight - barLeft)) * (soundBar.getGlobalBounds().width - 65);
        soundBarFiller.setSize(Vector2f(fillerWidth, soundBar.getGlobalBounds().height - 40));
    }

    if (controller.getUsingController()) {
        float barLeft = soundBar.getPosition().x + 35 - soundBar.getGlobalBounds().width / 2;
        float barRight = soundBar.getPosition().x - 35 + soundBar.getGlobalBounds().width / 2;

        if (Joystick::getAxisPosition(0, Joystick::X) > 50 || Keyboard::isKeyPressed(Keyboard::Right)) {
            soundTilter.move(5.f, 0);
        }
        if (Joystick::getAxisPosition(0, Joystick::X) < -50 || Keyboard::isKeyPressed(Keyboard::Left)) {
            soundTilter.move(-5.f, 0);
        }

        float newX = std::max(barLeft, std::min(soundTilter.getPosition().x, barRight));
        soundTilter.setPosition(newX, soundBar.getPosition().y - 5);

        float volumePercent = ((newX - barLeft) / (barRight - barLeft)) * 100.0f;
        music.setVolume(volumePercent);

        float fillerWidth = ((newX - barLeft) / (barRight - barLeft)) * (soundBar.getGlobalBounds().width - 65);
        soundBarFiller.setSize(Vector2f(fillerWidth, soundBar.getGlobalBounds().height - 40));
    }

}

void MainScreen::updateMenu(RenderWindow& window, Controller& controller) {
    if (settingSound) {
        handleSound(window, controller);
    }
    if (isInMenu) {
        interfaceuh.setGameStarted(false);
    }

    window.draw(background);
        for (auto& button : buttons) {
            if (!controller.getUsingController()) {
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
                                break;
                            }

                        }
                    }
                }
                else {
                    button.setTexture(false);
                }
            }
            else if (controller.getUsingController()) {
                button.setTexture(false);
                controller.updateHighlight(window, false, false);
                if (!settingSound) {
                    if (isInSettings && controller.getCurrentJoystickIndex() == 1)
                        controller.setCurrentJoystickIndex(2);
                    if (isInSettings && controller.Axis == controller.CheckAxis::UP)
                        controller.setCurrentJoystickIndex(0);
                }
                else if (settingSound) {
                    if (controller.getCurrentJoystickIndex() != 2)
                        controller.setCurrentJoystickIndex(2);
                }

                cout << "Current Index : " << controller.getCurrentJoystickIndex() << endl;
                if (Joystick::isButtonPressed(0, 0) || sf::Keyboard::isKeyPressed(Keyboard::Enter)) {
                    if (!isInSettings) {
                        switch (controller.getCurrentJoystickIndex()) {
                        case 0: //PLAY
                            interfaceuh.resetTime();
                            isInMenu = false; //Start Game
                            interfaceuh.setGameStarted(true);
                            break;
                        case 1: //SETTINGS
                            clickCooldown.restart();
                            isInSettings = true;
                            controller.setCurrentJoystickIndex(0);
                            break;
                        case 2: // EXIT
                            if (clickCooldown.getElapsedTime().asSeconds() > cooldownTime) {
                                window.close();
                            }
                            break;
                        }
                    }
                    else if (isInSettings) {
                        switch (controller.getCurrentJoystickIndex()) {
                        case 0:
                            if (clickCooldown.getElapsedTime().asSeconds() > cooldownTime)
                                settingSound = true;
                            clickCooldown.restart();
                            controller.setCurrentJoystickIndex(2);
                            break;

                        case 2:
                            if (settingSound) {
                                if (clickCooldown.getElapsedTime().asSeconds() > cooldownTime) {
                                    settingSound = false;
                                    clickCooldown.restart();
                                }
                            }
                            else {
                                if (clickCooldown.getElapsedTime().asSeconds() > cooldownTime) {
                                    isInSettings = false;
                                    clickCooldown.restart();
                                }
                            }
                            break;
                        }
                    }
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
                    

                    window.draw(soundBarFillerBG);
                    window.draw(soundBarFiller); // Draw filler first
                    window.draw(soundBar);
                    window.draw(soundTilter);
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
    if (controller.getUsingController()) {
        cout << "drawing highlight!" << endl;
        window.draw(controller.getHighlight());
    }
}

void MainScreen::destroyAll() {
	buttons.clear();
}
