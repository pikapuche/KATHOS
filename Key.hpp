#pragma once
#include "Interactibles.hpp"

class Key : public Interactible {
public:
    Key();

    void interact(Player& player) override;
    void setPosPos(float x, float y);
    void draw(RenderWindow& window) override;
};