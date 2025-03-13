#include "NuageTox.hpp"

NuageTox::NuageTox() : Entity(position.x, position.y) { //constructeur du boss
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(Color(0, 90, 0, 150));
}

//bool NuageTox::isInside()
//{
//
//}

void NuageTox::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void NuageTox::update(float deltaTime) { //déplacements
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

sf::RectangleShape NuageTox::getShape() { //prend la shape du joueur
    return shape;
}