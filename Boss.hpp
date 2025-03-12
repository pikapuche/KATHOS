#pragma once
#include "stdafx.hpp"
#include "Entity.hpp"
#include "Player.hpp"

class Boss : public Entity {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    Player& target;
    float detectionRange;

private:
    bool isJumping = false;
    bool isFalling = false;
    float jumpSpeed = -8.0f;
    float gravity = 0.4f;
    float groundY;
    sf::Clock jumpTimer;
    sf::Time jumpDuration = sf::seconds(1.5f);

public:
    Boss(Player& target);

    void update(float deltatime) override;
    void draw(RenderWindow& window) override;
    void checkCollision(int mapWidth);
    void chasePlayer();
    bool canSeePlayer();
    void startJump();

    Vector2f getPos();
    Vector2f setPos(float x, float y);

    RectangleShape getShape();
};