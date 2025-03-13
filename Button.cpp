#include "Button.hpp"
#include <iostream>

// Button constructor
Button::Button(float x, float y, float width, float height, ButtonType type, bool SettingsMenu,
    const string& texturePath, const string& texturePath2)
    : type(type), SettingsMenu(SettingsMenu) {
    if (!texture.loadFromFile(texturePath)) {
        cerr << "Failed to load texture: " << texturePath << endl;
    }

    if (!hoverTexture.loadFromFile(texturePath2)) {
        cerr << "Failed to load hover texture: " << texturePath2 << endl;
    }

    button.setScale(Vector2f(0.8f, 0.8f));
    button.setPosition(x, y);
    button.setTexture(texture);
    button.setOrigin(width / 2, height / 2);

}

void Button::draw(RenderWindow& window) {
    window.draw(button);
}

bool Button::isHovered(RenderWindow& window) {
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
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

Vector2f Button::getPosition() {
	return button.getPosition();
}

float Button::getHeight() {
    return button.getGlobalBounds().height;
}

float Button::getWidth() {
    return button.getGlobalBounds().width;
}