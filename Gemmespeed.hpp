#pragma once
#include "Gemme.hpp"

class GemmeSpeed : public Gemme {
public:
	GemmeSpeed();

	//sf::Vector2f setPosition(float x, float y);
	void interact(Player& player);
	void draw(RenderWindow& window, Player& player);
};