#pragma once
#include "stdafx.hpp"

class Entity {
protected : 

	Sprite sprite;

	// état d'anim avec les enums

public : 

	Vector2f direction;
	Vector2f velocity;
	Vector2f baseDirection;

	Entity(float posX, float posY);

	virtual void update(float deltaTime) = 0;
	virtual void draw(RenderWindow& window) = 0;

	Sprite& getSprite();
};