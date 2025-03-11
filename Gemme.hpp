#pragma once
#include "stdafx.hpp"
#include "Player.hpp"

class Gemme : public Player {
protected:
	sf::Vector2f position;
	RectangleShape speedGemmeShape;
	RectangleShape dashGemmeShape;
	bool isTakeSpeed;
	Clock clock;
	Clock coolDownDash;
public:
	Gemme(float s, float jForce);

	sf::Vector2f setPosition(float x, float y);
	void interact(Player& player);
	void draw(RenderWindow& window, Player& player);
};