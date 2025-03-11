#pragma once
#include "SFML/Graphics.hpp"

enum class ButtonType {
    Play,
    Exit,
    Settings,
    Sound,
    Return,
    Resume,
    Restart
};

class Button {
private:
    sf::Sprite button;
    sf::Texture texture;
    sf::Texture hoverTexture;
    ButtonType type;
    bool SettingsMenu;
    bool isHidden;

public:
    Button(float x, float y, float width, float height, ButtonType type, bool SettingsMenu, const std::string& texturePath, const std::string& texturePath2);
    void draw(sf::RenderWindow& window);
    bool isHovered(sf::RenderWindow& window);
    void setTexture(bool apply);
    ButtonType getType();  // Getter for type
    bool isInSettings();
	bool getisHidden();
	void setHidden(bool hidden);
};
