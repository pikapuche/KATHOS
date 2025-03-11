#pragma once
#include "stdafx.hpp"
#include "Entity.hpp"
#include "Player.hpp"

class Boss {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    Player& target;

public:
    Boss(Player& target);

    void update(float deltatime);
    void draw(RenderWindow& window);
    void checkCollision(int mapWidth);

    Vector2f getPos();
    Vector2f setPos(float(x), float(y));

    RectangleShape getShape();
};