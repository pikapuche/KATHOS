#pragma once
#include "stdafx.hpp"
#include "Entity.hpp"
#include "Player.hpp"

class Boss : public Entity {
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    Player& target;
    float detectionRange;

    Texture texture;

    bool isJumping;
    float jumpTimer;
    float jumpHeight;
    float gravity;
    float timeInAir;

public:
    Boss(Player& target);

    void update(float deltatime) override;
    void draw(RenderWindow& window) override;
    void checkCollision(int mapWidth, int mapHeight);
    void chasePlayer();
    bool canSeePlayer();

    void jumpToPlatform();
    void fallBackDown();

    Vector2f getPos();
    Vector2f setPos(float x, float y);
};