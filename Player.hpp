#pragma once
#include "Entity.hpp"
#include "Interactibles.hpp"
class Player : public Entity {
protected:
    Texture textureSprint;
    Texture textureIdle;
    RectangleShape attackShape;

    enum StateLook { LOOK_RIGHT, LOOK_LEFT };
    StateLook stateLook;

    enum StateMove { IDLE, RUN };
    StateMove stateMove;

    int jumpCount = 0;

    float SPEED = 300.0f;  // Vitesse de déplacement horizontal
    float jumpForce = 600.f;  // Force initiale du saut

    float animTimeDecr;
    float animRunTimeDecr;
    float animIdleTimeDecr;

    float rotaRight = 220;
    float rotaLeft = 120;

    float gachetteValue;
    float joystickValue;

    bool isAttacking = false;

    bool isTakeDash = false;
    bool isDashing = false;
    bool isTakeSpeed = false;

    bool hasKey = false;

    Clock jumpClock;
    Clock coolDownDash;
    Clock clock;

public:

    enum State { NONE, GROUNDED, JUMP };
    State state;

    bool floor = true;

    Player();

    void movementManager(float deltaTime);

    void animationManager(float deltaTime);

    void jump();

    void attack(float deltaTime);

    void dash(float deltaTime);

    void collisionPlatform(Sprite& tile, float deltaTime);

    void collisionFloor(Sprite& tile);

    Vector2f setPosPos(float x, float y);

    Vector2f getPosPos();

    Vector2f getVelocity();

    Vector2f setVelocity(float veloX, float veloY);

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