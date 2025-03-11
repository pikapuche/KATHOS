#include "MainScreen.hpp"
#include <iostream>

bool MainScreen::getIsInMenu() {
    return isInMenu;
}

void MainScreen::setIsInMenu(bool menu) {
    isInMenu = menu;
}

void MainScreen::initMenu(sf::RenderWindow& window) {
    if (!backgroundTexture.loadFromFile("assets/texture/titlescreen/background.png")) {
        std::cerr << "Failed to load background texture!" << std::endl;
    }

    background.setScale(sf::Vector2f(1.0f,1.0f));
    background.setTexture(backgroundTexture);

    buttons.push_back(Button(
        window.getSize().x / 2 - 100, window.getSize().y / 2 - 100,
		200, 100, ButtonType::Play, false,
        "assets/texture/titlescreen/buttons/playButton.png",
        "assets/texture/titlescreen/buttons/playButtonHover.png"
    ));

    buttons.push_back(Button(
        window.getSize().x / 2 - 100, window.getSize().y / 2 + 300,
        200, 100, ButtonType::Exit, false,
        "assets/texture/titlescreen/buttons/ExitButton.png",
        "assets/texture/titlescreen/buttons/ExitButtonHover.png"
    ));

    buttons.push_back(Button(
        window.getSize().x / 2 - 100, window.getSize().y / 2 + 100,
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
}

void MainScreen::updateMenu(sf::RenderWindow& window) {
    window.clear();
    window.draw(background);

    for (auto& button : buttons) {
        if (button.isHovered(window)) {
            button.setTexture(true);

            //Check when button click
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!button.getisHidden()) {
                    std::cout << "Button clicked" << std::endl;
                    switch (button.getType()) { //Check button type in Menu
                    case ButtonType::Play:
                        isInMenu = false; //Start Game
                        break;
                    case ButtonType::Exit:
                        if(clickCooldown.getElapsedTime().asSeconds() > cooldownTime)
                        window.close(); //Exit Game
                        break;

                    case ButtonType::Settings:
                        isInSettings = true; //Settings Menu
                        break;
                    case ButtonType::Return:
                        clickCooldown.restart();
                        isInSettings = false; //Return to Main Menu
                        break;
                    }
                }
            }
        }
        
        else {
            button.setTexture(false);   

        }


        if (isInSettings) {
            if (button.isInSettings()) {
				button.setHidden(false);
                button.draw(window);
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
    window.display();
}

void MainScreen::destroyAll() {
	buttons.clear();
}
