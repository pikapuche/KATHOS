#pragma once
#include "Gemme.hpp"

class GemmeDash : public Gemme {
public:
	GemmeDash();

	//sf::Vector2f setPosition(float x, float y);
	void interact(Player& player) override;
	void draw(RenderWindow& window, Player& player) override;
};