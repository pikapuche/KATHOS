#pragma once
#include "Player.hpp"

class Enemy : public Entity {
protected : 

	enum CurrentState { PATROL, CHASE, SEARCH }; // permet de connaitre l'etat dans lequel se trouve l'ennemi
	CurrentState currentState;

	enum StateDirection { LEFT, RIGHT }; // permet de connaitre la direction de l'ennemi
	StateDirection directionState;

	CircleShape circleOne; // cercle 1 de patrouille (DEBUG)
	CircleShape circleTwo; // cercle 2 de patrouille (DEBUG)
	CircleShape circleLastPos; // cercle de derniere position du joueur (DEBUG)
	//CircleShape circleDetect; // cercle de detection du joueur 
	RectangleShape rectangleDetect;
	RectangleShape attackDetect;
	RectangleShape attackShape;

	float detectionRadius; // rayon cercle de detection
	float lastPlayerPosition = - 100; // pour eviter qu'en mode debug le cercle s'affiche en 0,0;
	float SPEED = 175.f; 
	float nuage = 0.f;

	bool isGrounded = false;
	bool lastState; // dernier etat de l'ennemi (DEBUG)
	bool searching = false;
	bool attack = false;
	bool slow = false;

	Clock coolDownSearch;
	Clock clockAttack;
	Clock coolDownSlow;

public :

	enum StateEnemy { PATROLLER, CHASER };
	StateEnemy enemyState;

	Vector2f waypointOne;
	Vector2f waypointTwo;

	Enemy();

	void detectPlayer(Player& player); 

	void movementManager(float pos, float pos2, float deltaTime);

	void attackPlayer(Player& player);

	void patrol(float deltaTime, Player& player);

	void chase(Player& player, float deltaTime);

	void search(float lastPlayerPosition, float deltaTime, Player& player);

	Vector2f setPosPos(float x, float y); // modifie la position

	Vector2f getPosPos(); // retourne la position

	bool setIsGrounded(bool is); // modifie s'il touche le sol

	bool getIsGrounded(); // retourne s'il touche le sol

	void update(float deltaTime) override; // existe pas mais c'est pas grave

	void updateReal(float deltaTime, Player& player);

	void draw(RenderWindow& window) override;
};