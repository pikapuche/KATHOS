//#pragma once
//#include "SFML/Graphics.hpp"
//#include <vector>
//#include "Button.hpp"  // Include the Button header
//#include "Interface.hpp"
//
//class MainScreen {
//private:
//    bool isInMenu = true;
//    bool isInSettings = false;
//    Sprite background;
//    Texture backgroundTexture;
//    vector<Button> buttons;
//    Clock clickCooldown;  // Cooldown timer
//    float cooldownTime = 0.5f; // 0.5 seconds
//
//    //Controller Inputs
//    Interface interfaceuh; // Add Interface object
//    int selectedButtonIndex = 0; // Tracks selected button
//    Sprite highlightRect; // Highlight for selected button
//    Texture highlightTexture; // Texture for the highlight
//    
//public:
//    bool getIsInMenu();
//    void setIsInMenu(bool menu);
//    void initMenu(RenderWindow& window);
//    void updateMenu(RenderWindow& window);
//    void destroyAll();
//    void handleControllerNavigation();
//	void handleButtonPress(Button& button);
//};
