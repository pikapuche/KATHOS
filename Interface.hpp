#pragma once
#include "Button.hpp"
#include "Player.hpp"
#include "controllerManager.hpp"

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

    bool gameStarted = false;
    bool isPaused;
    PauseOverlay pauseOverlay; // Store the overlay as a member
    vector<Button> buttons;
    bool shouldRestart = false; // Track restart state
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
    void updateInterface(RenderWindow& window, Player& player, Controller& controller);
    bool getShouldRestart() const;
    void resetRestartFlag();

    void updateTimer(RenderWindow& window);
    void resetTime();

    Time getFinalTime() const;
    void setWinCondition(bool win);

    void setGameStarted(bool started);
    bool getGameStarted() const;

    void updateGameOver(sf::RenderWindow& window, Controller& controller);
};