#pragma once
#include "stdafx.hpp"
#include "Entity.hpp"
#include "Player.hpp"

class NuageTox : public Entity {
private:
    RectangleShape shape;
    Vector2f position;

public:
    NuageTox();

    void update(float deltatime);
    void draw(RenderWindow& window) override;

    Vector2f getPos();
    Vector2f setPos(float x, float y);

    RectangleShape getShape();
};