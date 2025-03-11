#pragma once
#include "stdafx.hpp"

class Entity {
protected : 

	Sprite sprite;
	sf::Vector2f position;
	sf::Vector2f velocity;
	RectangleShape shape;
	RectangleShape attackShape;

	// etat d'anim avec les enums

public : 

	Entity(/*Texture& texture,*/ float posX, float posY);

	virtual void update(float deltaTime) = 0;
	virtual void draw(RenderWindow& window) = 0;

	Sprite& getSprite();
};