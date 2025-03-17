#pragma once
#include "Button.hpp"

class PauseOverlay {
private:
    Sprite overlay;
    Texture overlayTexture;

public:
    PauseOverlay();
    void setTexture(const string& texturePath);
    void draw(RenderWindow& window);
};

class Interface {
private:
    bool isPaused;
    PauseOverlay pauseOverlay; // Store the overlay as a member
    vector<Button> buttons;
    bool shouldRestart = false; // Track restart state
    bool isUsingController;
    int selectedButtonIndex = 0; // Track the currently highlighted button
    Sprite highlightRect; // Overlay to show selection
	Texture highlightTexture;


    sf::Text textTimer;
    sf::Font font;
    sf::Clock clockTimer; // Clock to track time

public:
    void initInterface();
	bool getIsPaused();
	void setIsPaused(bool paused);
    void updateInterface(RenderWindow& window);
    bool getShouldRestart() const;
    void resetRestartFlag();
	void setUsingController(bool usingController);
	bool getUsingController();
	void detectControllerInput();
    void handleMenuNavigation(); // New function for input
    void updateTimer(sf::RenderWindow& window);
};
