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



public:
    Boss(Player& target);

    void update(float deltatime) override;
    void draw(RenderWindow& window) override;
    void checkCollision(int mapWidth, int mapHeight);
    void chasePlayer();
    bool canSeePlayer();

    Vector2f getPos();
    Vector2f setPos(float x, float y);
};