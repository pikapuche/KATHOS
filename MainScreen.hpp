#pragma once
#include "Interface.hpp"
#include "Game.hpp"
#include "controllerManager.hpp"

class MainScreen {
private:
    //Game game;
    bool isInMenu = true;
    bool isInSettings = false;
    bool settingSound = false;
    Sprite background;
    Texture backgroundTexture;
    vector<Button> buttons;
    Clock clickCooldown;  // Cooldown timer
    float cooldownTime = 0.5f; // 0.5 seconds

    //Controller Inputs
    Interface interfaceuh; // Add Interface object


    //Sound Related
    Sprite soundTilter;
    Texture soundTilterTexture;
    Texture soundTilterControllerTexture;
    Sprite soundBar;
    Texture soundBarTexture;
    RectangleShape soundBarFiller;
    RectangleShape soundBarFillerBG;

    sf::Music& music;
public:
    MainScreen(Music& music);
    bool getIsInMenu();
    void setIsInMenu(bool menu);
    void initMenu(RenderWindow& window);
    void updateMenu(RenderWindow& window, Controller& controller);
    void destroyAll();
    void handleSound(RenderWindow& window, Controller& controller);
};
