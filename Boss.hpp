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

public:
    Boss(Player& target);

    int onestla;

    enum State { NONE, GROUNDED, JUMP };
    State state;
    void jump();
    void getDown();
    float getJumpForce();
    float setJumpForce(float force);
    float getGravity();

    void update(float deltatime) override;
    void draw(RenderWindow& window) override;
    void checkCollision(int mapWidth, int mapHeight);
    void chasePlayer();
    bool canSeePlayer();

    Vector2f getPos();
    Vector2f setPos(float x, float y);

    Vector2f getVelocity();
    Vector2f setVelocity(float veloX, float veloY);
};