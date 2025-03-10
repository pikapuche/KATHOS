#pragma once
#include "SFML/Graphics.hpp"
#include "Button.hpp"
using namespace sf;
using namespace std;


class PauseOverlay {
private:
    sf::Sprite overlay;
    sf::Texture overlayTexture;

    


public:
    PauseOverlay();
    void setTexture(const std::string& texturePath);
    void draw(sf::RenderWindow& window);
};

class Interface {
private:
    bool isPaused;
    PauseOverlay pauseOverlay; // Store the overlay as a member
    std::vector<Button> buttons;
public:
    void initInterface();
	bool getIsPaused();
	void setIsPaused(bool paused);
    void updateInterface(sf::RenderWindow& window);
};
