#pragma once
#include "stdafx.hpp"
#include "Entity.hpp"
#include "Player.hpp"

class Boss : public Entity {
private:
    Vector2f position;
    Vector2f velocity;
    float speed;
    Player& target;
    float detectionRange;

    Texture texture;

    float jumpForce = 600.f;
    Clock jumpClock;

    RectangleShape detectionRect;

public:
    Boss(Player& target);

    int onestla;

    enum StateDirection { LEFT, RIGHT }; // permet de connaitre la direction du boss
    StateDirection directionState;

    void jump();
    float getJumpForce();
    float setJumpForce(float force);
    float getGravity();

    void update(float deltatime) override;
    void updateReal(float deltatime, Player& player);
    void draw(RenderWindow& window) override;
    void movementManager(float pos, float pos2, float deltaTime);
    bool canSeePlayer();

    Vector2f getPos();
    Vector2f setPos(float x, float y);

    Vector2f getVelocity();
    Vector2f setVelocity(float veloX, float veloY);
};