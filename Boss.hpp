#pragma once
#include "stdafx.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Map.hpp"

class Boss {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    Player& target;

public:
    Boss(float posX, float posY, Player& target);

    void update(float deltatime);
    void draw(RenderWindow& window);
    void checkCollision(int mapWidth);

    RectangleShape getShape();
};