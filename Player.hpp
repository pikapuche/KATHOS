#pragma once
#include "Entity.hpp"

class Player : public Entity {
protected:
    sf::Vector2f position;
    sf::Vector2f velocity;
    RectangleShape shape;

    enum State { LOOK_LEFT, LOOK_RIGHT };
    State state;

    const float gravity = 981.0f;  // Gravité en pixels par seconde carrée (simulation)
    float SPEED = 300.0f;  // Vitesse de déplacement horizontal
    float jumpForce = 600.f;  // Force initiale du saut
    bool isJumping = false;
    bool isJumping2 = false;
    bool isAttacking = false;
    bool canJump = false;
    bool canJump2 = false;
    bool isGrounded = false;
    bool isTakeDash = false;
    bool isDashing = false;
    bool isTakeSpeed = false;
    bool hasKey = false;

    float animTimeDecr;
    float rotaRight = 220;
    float rotaLeft = -20;

    float gachetteValue;

    int jumpCount = 0;

    int buttonCount = sf::Joystick::getButtonCount(0);
    float joystickValue;

    RectangleShape attackShape;

    Clock jumpClock;
    Clock coolDownDash;
    Clock clock;

public:

    Player();

    void movementManager(float deltaTime);

    void jump();

    void attack(float deltaTime);

    void dash();

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

    bool getIsTakeDash();

    bool setIsTakeDash(bool dash);

    bool getIsDashing();

    bool setIsDashing(bool dash);

    bool getIsTakeSpeed();

    bool setIsTakeSpeed(bool speed);

    float getJumpForce();

    float setJumpForce(float force);

    float getGravity();

    float getSPEED();

    int setJumpCount(float count);

    int getJumpCount();

    float setSPEED(float speed);

    bool getHasKey();

    bool setHasKey(bool key);

    void update(float deltaTime);

    void draw(RenderWindow& window);
};