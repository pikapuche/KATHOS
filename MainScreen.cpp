#include "MainScreen.hpp"
#include <iostream>

// Constructor for Button (No text, only texture)
MainScreen::Button::Button(float x, float y, float width, float height, const std::string& texturePath) {
    std::cout << "Loading: " << texturePath << std::endl;  // Debugging

    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }

    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    shape.setTexture(&texture);
}

void MainScreen::Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool MainScreen::Button::isHovered(sf::Vector2f mousePos) {
    return shape.getGlobalBounds().contains(mousePos);
}

bool MainScreen::Button::isClicked(sf::Event event, sf::Vector2f mousePos) {
    return event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left &&
        isHovered(mousePos);
}

// Getters & Setters
bool MainScreen::getIsInMenu() {
    return isInMenu;
}

void MainScreen::setIsInMenu(bool menu) {
    isInMenu = menu;
}

// Initialize menu with title, background, and buttons
void MainScreen::initMenu(sf::RenderWindow& window) {
    std::cout << "Loading background texture..." << std::endl;

    if (!backgroundTexture.loadFromFile("assets/texture/titlescreen/background.png")) {
        std::cerr << "Failed to load background texture!" << std::endl;
    }

    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setTexture(&backgroundTexture);

    buttons.emplace_back(300, 200, 200, 50, "assets/texture/titlescreen/button1.png");
    buttons.emplace_back(300, 300, 200, 50, "assets/texture/titlescreen/button2.png");
}

// Draw menu elements
void MainScreen::updateMenu(sf::RenderWindow& window) {
    window.clear();
    window.draw(background);

    for (auto& button : buttons) {
        button.draw(window);
    }

    window.display();
}

// Handle button clicks (Fixed: Removed Text)
void MainScreen::handleMenuInput(sf::RenderWindow& window, sf::Event event) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    for (auto& button : buttons) {
        if (button.isClicked(event, mousePos)) {
            if (&button == &buttons[0]) {  // Play button
                std::cout << "Play Clicked!" << std::endl;
                setIsInMenu(false);
            }
            else if (&button == &buttons[1]) {  // Exit button
                std::cout << "Exit Clicked! Closing window." << std::endl;
                window.close();
            }
        }
    }
}
