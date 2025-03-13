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

    //Controller Inputs
    Interface interfaceuh; // Add Interface object
    int selectedButtonIndex = 0; // Tracks selected button
    sf::Sprite highlightRect; // Highlight for selected button
    sf::Texture highlightTexture; // Texture for the highlight
    
public:
    bool getIsInMenu();
    void setIsInMenu(bool menu);
    void initMenu(sf::RenderWindow& window);
    void updateMenu(sf::RenderWindow& window);
    void destroyAll();
    void handleControllerNavigation();
	void handleButtonPress(Button& button);
};
