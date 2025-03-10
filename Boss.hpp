#pragma once
#ifndef BOSS_HPP
#define BOSS_HPP

#include "stdafx.hpp"

class Boss {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;

public:
    Boss(float startX, float startY);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void checkCollision(int mapWidth);

    sf::RectangleShape getShape();
};

#endif