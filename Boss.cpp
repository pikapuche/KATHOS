#include "Boss.hpp"

Boss::Boss(float posX, float posY, Player& target) : target(target) { //constructeur du boss
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::Red);
    position = { posX, posY };
    shape.setPosition(position);
    speed = 200.0f;
    velocity = { -speed, 0.0f };
}

void Boss::update(float deltaTime) { //déplacements
    position += velocity * deltaTime;
    shape.setPosition(position);
}

//void Boss::update(float deltaTime)
//{
//    Vector2f direction = target.getPosPos() - position;
//    float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
//
//    if (magnitude > 0)
//    {
//        direction /= magnitude;
//    }
//
//    Vector2f newPosition = position + direction * speed * deltaTime;
//
//    shape.setPosition(position);
//}

void Boss::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Boss::checkCollision(int mapWidth) { //check les collisions et empêche le boss de partir hors de la map sinon c'est pas ouf
    if (position.x <= 0) {
        position.x = 0;
        velocity.x = speed; 
    }
    else if (position.x + shape.getSize().x >= mapWidth) {
        position.x = mapWidth - shape.getSize().x;
        velocity.x = -speed;
    }
}

sf::RectangleShape Boss::getShape() { //prend la shape du joueur
    return shape;
}