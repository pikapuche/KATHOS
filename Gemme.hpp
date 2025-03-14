#pragma once
#include "stdafx.hpp"
#include "Player.hpp"



class Gemme {
public:

	sf::Vector2f position;
	Texture gemmeTexture;
	Sprite gemmeSprite;

	Clock gemmeClock;
	Time animGemmeTime;

	enum class  GemmeState { SPEED, DASH,};

	GemmeState gemmeState;
	
	Gemme();

	void animationGemme();
	void interact(Player& player);
	void updateGemme(float _x, float _y);
};