#pragma once
#include "stdafx.hpp"
#include "Entity.hpp"
#include "Player.hpp"

class Boss : public Entity {
private:
    Vector2f position;
    Vector2f velocity;
    float speed;
    float detectionRange;
    bool isJumping = false;

    bool isTired = false;
    Texture textureIdle;
    Texture textureAttack;
    float animDecrIdle;
    float animDecrAttack;

    float jumpForce = 600.f;
    Clock jumpClock;

    Clock coolDownTired;

    RectangleShape detectionRect;

    float enleverLife;

    bool canJump = false;

public:
    Boss();

    int onestla;

    enum StateDirection { LEFT, RIGHT }; // permet de connaitre la direction du boss
    StateDirection directionState;

    void jump();
    void takeDamage(Player& player);
    void doDamage(Player& player);
    void tired();
    void movementManager(float pos, float pos2, float deltaTime);
    void animationManager(float deltaTime);
    void update(float deltatime, Player& player);
    void draw(RenderWindow& window) override;

    float getJumpForce();
    float setJumpForce(float force);
    float getGravity();
    Vector2f getPos();
    Vector2f setPos(float x, float y);
    Vector2f getVelocity();
    Vector2f setVelocity(float veloX, float veloY);
};