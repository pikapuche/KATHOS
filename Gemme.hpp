#pragma once
#include "stdafx.hpp" // ??? - (amy)
#include "Player.hpp"
#include "Interactibles.hpp"

class Gemme : Interactible {
public:

	sf::Vector2f position;
	Texture gemmeTexture;
	Sprite gemmeSprite;

	float animGemmeTime;
	float animGemme;

	Clock gemmeClock;
	//Time animGemmeTime;

	Vector2i anim;

	enum class  GemmeState { SPEED, DASH };

	GemmeState gemmeState;
	
	Gemme(float _x, float _y);

	void animationGemme(float _deltaTime);
	Vector2f setPosition(float x, float y);
	void interact(const std::shared_ptr<Player>& player);
	void updateGemme(float _deltaTime);
};