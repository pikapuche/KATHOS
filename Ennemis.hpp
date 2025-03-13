#pragma once
#include "Player.hpp"

class Enemy : public Entity {
protected : 

	enum State { PATROL, CHASE, SEARCH };
	State currentState;

	float detectionRadius;
	sf::CircleShape circle;
	sf::Vector2f lastPlayerPosition;

	bool isGrounded = false;

	float SPEED = 250.f;

	Vector2f waypointOne;
	Vector2f waypointTwo;

	CircleShape circleOne;
	CircleShape circleTwo;

public : 

	Enemy(Vector2f wayOne, Vector2f wayTwo);

	bool detectPlayer(Player& player);

	void patrol(float deltaTime);

	void chase(Player& player);

	void search(sf::Vector2f lastPlayerPos, float deltaTime);

	Vector2f setPosPos(float x, float y);

	Vector2f getPosPos();

	RectangleShape getShape();

	bool setIsGrounded(bool is);

	bool getIsGrounded();

	void update(float deltaTime) override;

	void updateReal(float deltaTime, Player& player);

	void draw(RenderWindow& window) override;
};