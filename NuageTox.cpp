#include "NuageTox.hpp"

NuageTox::NuageTox(float width, float height) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color(0, 255, 0, 100)); // Vert transparent
}

void NuageTox::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void NuageTox::checkCollisionWithPlayer(Player& player) {
    if (shape.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) {
        cout << "Collision avec le joueur!" << endl;
        isGameOver = true;
    }
}

Vector2f NuageTox::getPos()
{
    return position;
}

Vector2f NuageTox::setPos(float(x), float(y))
{
    position.x = x;
    position.y = y;
    return position;
}
