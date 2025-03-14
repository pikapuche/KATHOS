#pragma once
#include "stdafx.hpp"
#include "Player.hpp"

class Gemme {
protected:
	sf::Vector2f position;
	RectangleShape shape;
	//RectangleShape speedGemmeShape;
	//RectangleShape dashGemmeShape;

public:

	Gemme();

	//sf::Vector2f setPosition(float x, float y);
	virtual void interact(Player& player) = 0;
	virtual void draw(RenderWindow& window, Player& player) = 0;
};