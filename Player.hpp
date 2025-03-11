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
    bool isJumping2;
    bool isAttacking;
    bool canJump = false;
    bool canJump2 = false;
    bool isGrounded = false;

    float animTimeDecr;
    float rotaLeft = 220;

    int jumpCount = 0;

    int buttonCount = sf::Joystick::getButtonCount(0);
    float joystickValue;

    RectangleShape attackShape;

    Clock jumpClock;

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

    bool getIsJumping2();

    bool setIsJumping2(bool jump);

    bool getCanJump();

    bool setcanJump(bool can);

    bool getCanJump2();

    bool setcanJump2(bool can);

    bool setIsGrounded(bool is);

    bool getIsGrounded();

    float getJumpForce();

    float setJumpForce(float force);

    float getGravity();

    float getSPEED();

    int setJumpCount(float count);

    int getJumpCount();

    float setSPEED(float speed);

    void update(float deltaTime);

    void draw(RenderWindow& window);
};