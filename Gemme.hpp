#pragma once
#include "Player.hpp"
#include "Interactibles.hpp"

class Gemme {
private:
	bool wasTaken = false;
public:

	Vector2f position;
	Texture gemmeTexture;
	Sprite gemmeSprite;

	float animGemmeTime;
	float animGemme;

	Clock gemmeClock;
	//Time animGemmeTime;

	Vector2i anim;

	enum class  GemmeState { SPEED, DASH, DOUBLEJUMP };

	GemmeState gemmeState;
	
	Gemme(float _x, float _y, GemmeState gemmeState);

	void animationGemme(float _deltaTime);
	//Vector2f setPosition(float x, float y);
	void interact(const shared_ptr<Player>& player);
	void updateGemme(float _deltaTime, const shared_ptr<Player>& player);
	bool getGemTaken();
};