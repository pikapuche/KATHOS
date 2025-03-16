#pragma once
#include "stdafx.hpp"

class Entity {
protected:

	Sprite sprite;
	Texture texture;
	sf::Vector2f position;
	sf::Vector2f velocity;
	RectangleShape attackShape;
	const float gravity = 981.0f;  // Gravité en pixels par seconde carrée (simulation)

	Vector2i anim_move;
	Vector2i anim_idle;

	float boxCol1;
	float boxCol2;

public:

	enum State { NONE, GROUNDED, JUMP };
	State state;

	Entity(float posX, float posY);

	virtual void collision(Sprite& tile, float deltaTime);
	virtual void update(float deltaTime) = 0;
	virtual void draw(RenderWindow& window) = 0;

	Sprite& getSprite();
};