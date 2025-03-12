#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "Button.hpp"  // Include the Button header
#include "Interface.hpp"

class MainScreen {
private:
    bool isInMenu = true;
    bool isInSettings = false;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    std::vector<Button> buttons;
    sf::Clock clickCooldown;  // Cooldown timer
    float cooldownTime = 0.5f; // 0.5 seconds

public:
    bool getIsInMenu();
    void setIsInMenu(bool menu);
    void initMenu(sf::RenderWindow& window);
    void updateMenu(sf::RenderWindow& window);
    void destroyAll();
};
