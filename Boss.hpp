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

    Texture textureIdle;
    Texture textureAttack;
    float animDecrIdle;
    float animDecrAttack;

    float jumpForce = 600.f;
    Clock jumpClock;

    RectangleShape detectionRect;

    RectangleShape healthBar;
    int health = 180;
    int life;
    float enleverLife;

    bool canJump = false;

public:
    Boss();

    int onestla;

    enum StateDirection { LEFT, RIGHT }; // permet de connaitre la direction du boss
    StateDirection directionState;

    void jump();
    void takeDamage(Player& player);
    float getJumpForce();
    float setJumpForce(float force);
    float getGravity();

    void update(float deltatime, Player& player);
    void draw(RenderWindow& window) override;
    void movementManager(float pos, float pos2, float deltaTime);
    void animationManager(float deltaTime);
    int getHealth();
    int getLife();

    void setLife(int amount);

    Vector2f getPos();
    Vector2f setPos(float x, float y);

    Vector2f getVelocity();
    Vector2f setVelocity(float veloX, float veloY);
};