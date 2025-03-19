#pragma once
#include "Button.hpp"
#include "Player.hpp"

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
    sf::Time totalElapsedTime; // Store total elapsed time
    Texture keyGUItexture;
    Sprite keyGUI;

    bool gameStarted = false;
    bool isPaused;
    PauseOverlay pauseOverlay; // Store the overlay as a member
    vector<Button> buttons;
    bool shouldRestart = false; // Track restart state
    bool isUsingController;
    int selectedButtonIndex = 0; // Track the currently highlighted button
    Sprite highlightRect; // Overlay to show selection
	Texture highlightTexture;

    sf::Clock timeClock;
    sf::Text timeText;
    sf::Font timeFont;


public:
    void initInterface();
	bool getIsPaused();
	void setIsPaused(bool paused);
    void updateInterface(RenderWindow& window, Player& player);
    bool getShouldRestart() const;
    void resetRestartFlag();
	void setUsingController(bool usingController);
	bool getUsingController();
	void detectControllerInput();
    void handleMenuNavigation(); // New function for input

    void updateTimer(RenderWindow& window);
    void resetTime();

    void setGameStarted(bool started);
    bool getGameStarted() const;
};
