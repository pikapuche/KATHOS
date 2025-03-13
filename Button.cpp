#include "Button.hpp"
#include <iostream>

// Button constructor
Button::Button(float x, float y, float width, float height, ButtonType type, bool SettingsMenu,
    const std::string& texturePath, const std::string& texturePath2)
    : type(type), SettingsMenu(SettingsMenu) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }

    if (!hoverTexture.loadFromFile(texturePath2)) {
        std::cerr << "Failed to load hover texture: " << texturePath2 << std::endl;
    }

    button.setScale(sf::Vector2f(0.8f, 0.8f));
    button.setPosition(x, y);
    button.setTexture(texture);
    button.setOrigin(width / 2, height / 2);

}

void Button::draw(sf::RenderWindow& window) {
    window.draw(button);
}

bool Button::isHovered(sf::RenderWindow& window) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return button.getGlobalBounds().contains(mousePos);
}

void Button::setTexture(bool apply) {
    if (apply) {
        button.setTexture(hoverTexture);
    }
    else {
        button.setTexture(texture);
    }
}

ButtonType Button::getType() {
	return type;
}

bool Button::isInSettings() {
	return SettingsMenu;
}

bool Button::getisHidden() {
	return isHidden;
}

void Button::setHidden(bool hidden) {
	isHidden = hidden;
}