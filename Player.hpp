#pragma once
#include "Entity.hpp"

class Player : public Entity {
protected:
    sf::Vector2f position;
    sf::Vector2f velocity;
    RectangleShape shape;

    const float gravity = 981.0f;  // Gravité en pixels par seconde carrée (simulation)
    float SPEED = 300.0f;  // Vitesse de déplacement horizontal
    float jumpForce = 600.f;  // Force initiale du saut
    bool isJumping;
    bool isAttacking;

    float animTimeDecr;
    float rotaLeft;

    RectangleShape attackShape;

public:

    Player(float s, float jForce);

    void movementManager(float deltaTime);

    void jump();

    void attack(float deltaTime);

    Vector2f getPosPos();

    Vector2f setPosPos(float(x), float(y));

    Vector2f getVelocity();

    Vector2f setVelocity(float veloX, float veloY);

    RectangleShape getShape();

    bool getIsJumping();

    bool setIsJumping(bool jump);

    float getJumpForce();

    float setJumpForce(float force);

    float getGravity();

    float getSPEED();

    float setSPEED(float speed);

    void update(float deltaTime);

    void draw(RenderWindow& window);
};