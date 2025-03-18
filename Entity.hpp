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

	Vector2i anim_move; // sert aux animations du perso et ennemis
	Vector2i anim_idle;
	Vector2i anim_jump;
	Vector2i anim_attack;

	RectangleShape lifeBar;
	RectangleShape rectBar;
	float life;

	float boxCol1;
	float boxCol2;

	bool DEBUG = false; // sert pour voir si y'a des bugs / afficher les hitbox etc

public:

	enum State { NONE, GROUNDED, JUMP };
	State state;

	Entity(float posX, float posY);

	virtual void collision(Sprite& tile, float deltaTime);
	virtual void draw(RenderWindow& window) = 0;

	Sprite& getSprite();

	int getLife();

	void setLife(float l);
};