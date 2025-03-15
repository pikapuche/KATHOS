#include "NuageTox.hpp"

NuageTox::NuageTox() : Entity(position.x, position.y) { //constructeur du boss
    shape.setSize(Vector2f(50.0f, 50.0f));
    shape.setFillColor(Color(0, 90, 0, 150));
}

void NuageTox::draw(RenderWindow& window) {
    window.draw(shape);
}

void NuageTox::update(float deltaTime) { //d�placements
    shape.setPosition(position);
}

Vector2f NuageTox::getPos() {
    return position;
}

Vector2f NuageTox::setPos(float x, float y) {
    position.x = x;
    position.y = y;
    return position;
}

RectangleShape NuageTox::getShape() { //prend la shape du nuage
    return shape;
}