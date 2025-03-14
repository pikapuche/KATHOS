#include "Ennemis.hpp"

Enemy::Enemy() : Entity(position.x, position.y)
{
    circle.setRadius(50.0f);
    circle.setPosition(position);
    circle.setFillColor(sf::Color::Red);
    detectionRadius = 25.0f;
    currentState = PATROL;
    circleOne.setFillColor(Color::Yellow);
    circleOne.setRadius(25.0f);
    circleTwo.setFillColor(Color::Blue);
    circleTwo.setRadius(25.0f);
    texture.loadFromFile("assets/Ennemies/R.png");
    sprite.setTexture(texture);
}

bool Enemy::detectPlayer(Player& player)
{
    float distance = std::sqrt(std::pow(player.getPosPos().x - position.x, 2) + std::pow(player.getPosPos().y - position.y, 2));
    return (distance < detectionRadius);
}

void Enemy::patrol(float deltaTime) // a bien restructurer et faire en sorte qu'il se déplace que sur l'axe x et pas sur le y avec le chemin a trouver 
{
    //if (position.x > circleOne.getPosition().x) {
    //    position.x += SPEED * deltaTime;
    //}
    //else if (position.x > circleOne.getPosition().x && position.x < circleTwo.getPosition().x) {
    //    position.x -= SPEED * deltaTime;
    //}
    //static int currentWaypoint = 0;
    //static sf::Vector2f waypoints[2] = { waypoint1, waypoint2 };
    //sf::Vector2f target = waypoints[currentWaypoint];
    //sf::Vector2f direction = target - position;
    //float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    //if (distance < 5.0f) {
    //    currentWaypoint = (currentWaypoint + 1) % 2;
    //}
    //else {
    //    direction /= distance;
    //    position += direction * SPEED;
    //}
}

//void Enemy::chase(Player& player)
//{
//    return position;
//}
//
//RectangleShape Enemy::getShape() {
//    return shape;
//}
//
//bool Enemy::setIsGrounded(bool is)
//{
//    isGrounded = is;
//    return isGrounded;
//}
//
//bool Enemy::getIsGrounded()
//{
//    return isGrounded;
//}
//
//void Enemy::update(float deltaTime)
//{
//}
//
//void Enemy::updateReal(float deltaTime, Player& player)
//{
//    if (isGrounded) {
//        velocity.y = 0;
//    }
//    else {
//        velocity.y += gravity * deltaTime;  // Appliquer la gravité
//    }
//    position.y += velocity.y * deltaTime;
//
//    switch (currentState) {
//    case PATROL:
//        patrol(deltaTime);
//        //if (detectPlayer(player)) currentState = CHASE;
//        break;
//    }
//    //case CHASE:
//    //    chase(player);
//    //    if (!detectPlayer(player)) {
//    //        currentState = SEARCH;
//    //    }
//    //    break;
//
//    //case SEARCH:
//    //    search(lastPlayerPosition, deltaTime);
//    //    break;
//    //}
//    shape.setPosition(position);
//}

Vector2f Enemy::setPosPos(float x, float y)
{
    position.x = x;
    position.y = y;
    return position;
}

Vector2f Enemy::getPosPos()
{
    return position;
}

bool Enemy::setIsGrounded(bool is)
{
    isGrounded = is;
    return isGrounded;
}

bool Enemy::getIsGrounded()
{
    return isGrounded;
}

void Enemy::update(float deltaTime)
{
    //if (isGrounded) {
    //    velocity.y = 0;
    //}
    //else {
    //    velocity.y += gravity * deltaTime;  // Appliquer la gravité
    //}
    //position.y += velocity.y * deltaTime;

    switch (currentState) {
    case PATROL:
        patrol(deltaTime);
        //if (detectPlayer(player)) currentState = CHASE;
        break;
    }
    //case CHASE:
    //    chase(player);
    //    if (!detectPlayer(player)) {
    //        currentState = SEARCH;
    //    }
    //    break;

    //case SEARCH:
    //    search(lastPlayerPosition, deltaTime);
    //    break;
    //}
    sprite.setPosition(position);
    circleOne.setPosition(waypointOne);
    circleTwo.setPosition(waypointTwo);
}

void Enemy::draw(RenderWindow& window)
{
    window.draw(sprite);
    window.draw(circleOne);
    window.draw(circleTwo);
}