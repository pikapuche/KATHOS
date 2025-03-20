#pragma once
#include "stdafx.hpp"
#include "Entity.hpp"
#include "Player.hpp"

class NuageTox : public Entity {
private:
    Texture texture;
    Vector2f position;
    bool slow = false;

    Clock coolDownSlow;
public:
    NuageTox();

    void update(float deltatime);
    void draw(RenderWindow& window) override;

    void collision(Player& player);

    Vector2f getPos();
    Vector2f setPos(float x, float y);
};