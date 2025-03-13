#include "Key.hpp"


Key::Key(){
    // Load the Key texture
    //setTexture("assets/texture/Interactibles/chest.png");
    sprite.setScale(1.0f, 1.0f);
}

keytype Key::getKeyType() {
    return KeyType;
};

void Key::setKeyType(keytype type) {
    KeyType = type;
};

void Key::setPosPos(float x, float y) {
    sprite.setPosition({ x, y });
}