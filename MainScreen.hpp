#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "Button.hpp"  // Include the Button header

class MainScreen {
private:
    bool isInMenu = true;
    bool isInSettings = false;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    std::vector<Button> buttons;

public:
    bool getIsInMenu();
    void setIsInMenu(bool menu);
    void initMenu(sf::RenderWindow& window);
    void updateMenu(sf::RenderWindow& window);
};
