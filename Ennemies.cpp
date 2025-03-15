#include "Ennemies.hpp"

Enemy::Enemy() : Entity(position.x, position.y)
{
    circleDetect.setRadius(150.0f);
    circleDetect.setPosition(position);
    circleDetect.setFillColor(sf::Color(255, 0, 0, 50));
    circleDetect.setOrigin(132.f, 132.f);
    detectionRadius = 25.0f;
    currentState = PATROL;
    circleOne.setFillColor(Color::Yellow);
    circleOne.setRadius(10.0f);
    circleTwo.setFillColor(Color::Blue);
    circleTwo.setRadius(10.0f);
    texture.loadFromFile("assets/Ennemies/R.png");
    sprite.setTexture(texture);
    boxCol1 = 32;
    boxCol2 = 32;
}

bool Enemy::detectPlayer(Player& player)
{
    float distance = std::sqrt(std::pow(player.getPosPos().x - position.x, 2) + std::pow(player.getPosPos().y - position.y, 2));
    return (distance < detectionRadius);
}

void Enemy::patrol(float deltaTime) // a bien restructurer et faire en sorte qu'il se déplace que sur l'axe x et pas sur le y avec le chemin a trouver 
{
    if (position.x < circleOne.getPosition().x && directionState != RIGHT) {
        directionState = RIGHT;
    }
    else if (position.x > circleTwo.getPosition().x && directionState != LEFT) {
        directionState = LEFT;
    }

    if (directionState == RIGHT) {
        position.x += SPEED * deltaTime;
    }
    else {
        position.x -= SPEED * deltaTime;
    }
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

    velocity.y += gravity * deltaTime;  // Appliquer la gravité
    position.y += velocity.y * deltaTime;

    sprite.setPosition(position);
    circleDetect.setPosition(position);
    circleOne.setPosition(waypointOne);
    circleTwo.setPosition(waypointTwo);
}

void Enemy::draw(RenderWindow& window)
{
    window.draw(circleOne);
    window.draw(circleTwo);
    window.draw(circleDetect);
    window.draw(sprite);
}