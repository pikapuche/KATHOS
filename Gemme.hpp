#pragma once
#include "stdafx.hpp"
#include "Player.hpp"

class Gemme : public Player {
protected:
	sf::Vector2f position;
	RectangleShape speedGemmeShape;
	RectangleShape dashGemmeShape;
	Texture gemmeTexture;
	Sprite gemmeSprite;
	Clock clockGemme;

public:
	Gemme();

	sf::Vector2f setPosition(float x, float y);
	void movementManager(float deltaTime);
	void update(float deltaTime);
	void interact(Player& player);
	void draw(RenderWindow& window, Player& player);
};