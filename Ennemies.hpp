#pragma once
#include "Player.hpp"

class Enemy : public Entity {
protected : 

	enum CurrentState { PATROL, CHASE, SEARCH };
	CurrentState currentState;

	enum StateDirection { LEFT, RIGHT };
	StateDirection directionState;

	float detectionRadius;
	sf::CircleShape circleDetect;
	sf::Vector2f lastPlayerPosition;

	bool isGrounded = false;

	float SPEED = 250.f;

	CircleShape circleOne;
	CircleShape circleTwo;

public : 

	Vector2f waypointOne;
	Vector2f waypointTwo;

	Enemy();

	bool detectPlayer(Player& player);

	void patrol(float deltaTime);

	void chase(Player& player);

	void search(sf::Vector2f lastPlayerPos, float deltaTime);

	Vector2f setPosPos(float x, float y);

	Vector2f getPosPos();

	bool setIsGrounded(bool is);

	bool getIsGrounded();

	void update(float deltaTime) override;

	void draw(RenderWindow& window) override;
};