#pragma once
#include "Entity.hpp"

class Player : public Entity {
protected:
    Texture textureSprint;
    RectangleShape attackShape;

    enum StateLook { LOOK_RIGHT, LOOK_LEFT };
    StateLook stateLook;

    enum StateMove { RUN, IDLE };
    StateMove stateMove;

    int jumpCount = 0;

    float SPEED = 300.0f;  // Vitesse de déplacement horizontal
    float jumpForce = 600.f;  // Force initiale du saut

    float animTimeDecr;
    float animRunTimeDecr;

    float rotaRight = 220;
    float rotaLeft = -20;

    float gachetteValue;
    float joystickValue;

    bool isJumping = false;
    bool isAttacking = false;

    bool isGrounded = false;

    bool isTakeDash = false;
    bool isDashing = false;
    bool isTakeSpeed = false;

    bool hasKey = false;

    bool isMoving = false;

    Clock jumpClock;
    Clock coolDownDash;
    Clock clock;

public:

    Player();

    void movementManager(float deltaTime);

    void animationManager(float deltaTime);

    void jump();

    void attack(float deltaTime);

    void dash(float deltaTime);

    Vector2f setPosPos(float x, float y);

    Vector2f getPosPos();

    Vector2f getVelocity();

    Vector2f setVelocity(float veloX, float veloY);

    //RectangleShape getShape();

    bool getIsJumping();

    bool setIsJumping(bool jump);

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

    float setSPEED(float speed);

    int setJumpCount(float count);

    int getJumpCount();

    bool getHasKey();

    bool setHasKey(bool key);

    void update(float deltaTime);

    void draw(RenderWindow& window);
};