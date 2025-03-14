#pragma once
#include "Interactibles.hpp"

class Player;

class Key : public Interactible {
private:

public:
    Key();

    void interact(Player& player) override;
    void setPosPos(float x, float y);
};