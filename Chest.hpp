#pragma once
#include "Interactibles.hpp"

class Player;

class Chest : public Interactible {
private:
    bool containsKey;

public:
    Chest(bool containKey);

    void interact(Player& player) override;
    void setPosPos(float x, float y);
};
