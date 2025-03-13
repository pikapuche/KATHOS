#pragma once
#include "Interactibles.hpp"

enum keytype {
    DOOR,
    CHEST
};

class Key : public Interactible {

private:
    keytype KeyType;

public:

    Key();
    void setPosPos(float x, float y);
    keytype getKeyType();
    void setKeyType(keytype type);
};