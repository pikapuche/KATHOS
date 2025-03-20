#pragma once
#include "stdafx.hpp"
#include "Button.hpp"



class Controller{
private:
	
	int joystickY;
	int currentJoystickIndex = 0;
	bool isUsingController;
	int visibleButtons;
	vector<Button> buttons;
	Sprite highlightRect; // Highlight for selected button
	Texture highlightTexture; // Texture for the highlight

	sf::Clock timeClock;
	float cooldown = 0.25f;

public:


	enum CheckAxis { UP, DOWN };
	CheckAxis Axis;



	Controller();
	void setUsingController(bool usingController);
	bool getUsingController();
	void detectControllerInput();
	void updateAxis();
	int getCurrentJoystickIndex();
	void setCurrentJoystickIndex(int value);
	Sprite getHighlight();
	void updateHighlight(sf::RenderWindow& window, bool inPause);
};