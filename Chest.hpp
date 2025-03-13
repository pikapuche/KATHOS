#pragma once
#include "Interactibles.hpp"

class Chest : public Interactible {
private:
    std::string chestContent;
    int contentAmount;
    bool requireKey;

public:
    Chest();

    //void interact(Player& player) override; // Define interaction
    void setPosPos(float x, float y);
};