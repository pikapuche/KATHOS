#pragma once
#include "Entity.hpp"

class Player : public Entity {
protected:
    Texture textureSprint; 
    Texture textureIdle;
    Texture textureJump;
    Texture textureAttack;
    RectangleShape attackShape;

    enum StateLook { LOOK_RIGHT, LOOK_LEFT }; // permet de connaitre la direction dans laquelle le joueur regarde
    StateLook stateLook;

    enum StateMove { IDLE, RUNNING, ATTACKING, JUMPING }; // etat pour animation de course et d'attente
    StateMove stateMove;

    int jumpCount = 0; // compteur de saut pour double saut

    float SPEED = 300.0f;  // Vitesse de déplacement horizontal
    float jumpForce = 600.f;  // Force initiale du saut

    float animTimeDecr;
    float animRunTimeDecr; // timer pour les anim (temps entre chaque frame)
    float animIdleTimeDecr;
    float animJumpTimeDecr;
    float animAttackTimeDecr;

    float rotaRight = 220; // rotation pour l'attaque
    float rotaLeft = 120;

    float gachetteValue; // valeur pour la manette
    float joystickValue;

    bool isAttacking = false;
    bool isTakeDash = false; // recup la gemme de dash
    bool isDashing = false; // dash
    bool isTakeSpeed = false; // recup la gemme de sprint

    bool hasKey = false;

    Clock jumpClock; // compteur pour le deuxieme saut (evite l'enchainement)
    Clock coolDownDash; 
    Clock clock;

public:

    bool floor = true;

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

    void update(float deltaTime) override;

    void draw(RenderWindow& window) override;
};