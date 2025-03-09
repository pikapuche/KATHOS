#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

class MainScreen {
private:
    bool isInMenu = true;
    sf::RectangleShape background;
    sf::Texture backgroundTexture;

    struct Button {
        sf::RectangleShape shape;
        sf::Texture texture;

        Button(float x, float y, float width, float height, const std::string& texturePath);
        void draw(sf::RenderWindow& window);
        bool isHovered(sf::Vector2f mousePos);
        bool isClicked(sf::Event event, sf::Vector2f mousePos);
    };

    std::vector<Button> buttons;

public:
    bool getIsInMenu();
    void setIsInMenu(bool menu);
    void initMenu(sf::RenderWindow& window);
    void updateMenu(sf::RenderWindow& window);
    void handleMenuInput(sf::RenderWindow& window, sf::Event event);
};
