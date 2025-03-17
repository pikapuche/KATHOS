#pragma once
#include "stdafx.hpp"
#include "Player.hpp"

class Gemme {
public:

	sf::Vector2f position;
	Texture gemmeTexture;
	Sprite gemmeSprite;

	float animGemmeTime;
	float animGemme;

	Clock gemmeClock;
	//Time animGemmeTime;

	Vector2i anim;
	
	Gemme(float _x, float _y);

	void animationGemme(float _deltaTime);
	//Vector2f setPosition(float x, float y);
	//void interact(Player& player);
	void updateGemme(float _deltaTime);
};