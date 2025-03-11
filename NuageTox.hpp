#pragma once
#include "stdafx.hpp"
#include "Player.hpp"

class NuageTox {
public:
    NuageTox(float width, float height);
    void draw(sf::RenderWindow& window);
    void checkCollisionWithPlayer(Player& player);

    Vector2f getPos();

    Vector2f setPos(float(x), float(y));

private:
    sf::RectangleShape shape;
    bool isGameOver = false;
    sf::Vector2f position;
};