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
    Time totalElapsedTime; // Store total elapsed time
    Texture keyGUItexture;
    Sprite keyGUI;

    bool isPaused;
    PauseOverlay pauseOverlay; // Store the overlay as a member
    vector<Button> buttons;
    bool shouldRestart = false; // Track restart state
    bool isUsingController;
    int selectedButtonIndex = 0; // Track the currently highlighted button
    Sprite highlightRect; // Overlay to show selection
	Texture highlightTexture;

    Clock timeClock;
    Text timeText;
    Font timeFont;

    Time finalTime;

    bool hasWon = false;
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

    Time getFinalTime() const;
    void setWinCondition(bool win);
};
