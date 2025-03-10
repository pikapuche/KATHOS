#include "Boss.hpp"

Boss::Boss(float startX, float startY) {
    shape.setSize(sf::Vector2f(50.0f, 50.0f)); // Taille du boss
    shape.setFillColor(sf::Color::Red); // Couleur rouge
    position = { startX, startY };
    shape.setPosition(position);
    speed = 200.0f; // Vitesse du boss
    velocity = { -speed, 0.0f }; // Déplacement initial vers la gauche
}

void Boss::update(float deltaTime) {
    position += velocity * deltaTime;
    shape.setPosition(position);
}

void Boss::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Boss::checkCollision(int mapWidth) {
    if (position.x <= 0) { // Collision avec le bord gauche
        position.x = 0;
        velocity.x = speed; // Change de direction
    }
    else if (position.x + shape.getSize().x >= mapWidth) { // Collision avec le bord droit
        position.x = mapWidth - shape.getSize().x;
        velocity.x = -speed; // Change de direction
    }
}

sf::RectangleShape Boss::getShape() {
    return shape;
}