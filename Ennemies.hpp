#pragma once
#include "Player.hpp"

class Enemy : public Entity {
protected : 

	enum CurrentState { PATROL, CHASE, SEARCH };
	CurrentState currentState;

	bool lastState;

	enum StateDirection { LEFT, RIGHT };
	StateDirection directionState;

	float detectionRadius;
	sf::CircleShape circleDetect;
	float lastPlayerPosition = - 100;

	bool isGrounded = false;

	float SPEED = 175.f;

	CircleShape circleOne;
	CircleShape circleTwo;
	CircleShape circleLastPos;

	bool searching = false;

	Clock coolDownSearch;

public :

	enum StateEnemy { PATROLLER, CHASER };
	StateEnemy enemyState;

	Vector2f waypointOne;
	Vector2f waypointTwo;

	Enemy();

	void detectPlayer(Player& player);

	void movementManager(float pos, float pos2, float deltaTime);

	void patrol(float deltaTime);

	void chase(Player& player, float deltaTime);

	void search(float lastPlayerPosition, float deltaTime);

	Vector2f setPosPos(float x, float y);

	Vector2f getPosPos();

	bool setIsGrounded(bool is);

	bool getIsGrounded();

	void update(float deltaTime) override;

	void updateReal(float deltaTime, Player& player);

	void draw(RenderWindow& window) override;
};