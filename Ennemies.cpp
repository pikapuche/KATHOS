#include "Ennemies.hpp"

Enemy::Enemy() : Entity(position.x, position.y)
{
    circleDetect.setRadius(150.0f);
    circleDetect.setPosition(position);
    circleDetect.setFillColor(sf::Color(255, 0, 0, 50));
    circleDetect.setOrigin(132.f, 132.f);
    currentState = PATROL;
    circleOne.setFillColor(Color::Yellow);
    circleOne.setRadius(10.0f);
    circleTwo.setFillColor(Color::Blue);
    circleTwo.setRadius(10.0f);
    texture.loadFromFile("assets/Ennemies/R.png");
    sprite.setTexture(texture);
    boxCol1 = 32;
    boxCol2 = 32;
    circleLastPos.setRadius(20.f);
    circleLastPos.setFillColor(Color::Cyan);
}

void Enemy::detectPlayer(Player& player) // calcul la distance avec le theoreme du P
{
    if (enemyState == CHASER) {
        if (circleDetect.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()) && currentState != CHASE) { // si l'ennemi est un chasseur et que le perso entre dans le cercle de detection
            currentState = CHASE;
        }
        else if (!circleDetect.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()) && currentState == CHASE) {
            lastPlayerPosition = player.getSprite().getPosition().x;
            currentState = SEARCH;
        }
    }
}

void Enemy::movementManager(float pos, float pos2, float deltaTime) { // permet de gerer le mouvement de l'ennemi
    if (position.x < pos && directionState != RIGHT) {
        directionState = RIGHT;
    }
    else if (position.x > pos2 && directionState != LEFT) {
        directionState = LEFT;
    }

    if (directionState == RIGHT) {
        position.x += SPEED * deltaTime;
    }
    else {
        position.x -= SPEED * deltaTime;
    }
}

void Enemy::patrol(float deltaTime) // fait simplement des gauche droite entre 2 points
{
    cout << "patrol" << endl;
    sprite.setColor(Color::Blue);
    movementManager(circleOne.getPosition().x, circleTwo.getPosition().x, deltaTime);
}

void Enemy::chase(Player& player, float deltaTime) // suit le perso tant qu'il est dans la zone de detection
{
    cout << "chase" << endl;
    sprite.setColor(Color::Red);
    movementManager(player.getSprite().getPosition().x, player.getSprite().getPosition().x, deltaTime);
}

void Enemy::search(float lastPlayerPosition, float deltaTime) // quand le perso sort de la zone il va jusqu'a sa derniere position et effectue des gauche droite pour le chercher
{
    cout << "search" << endl;
    sprite.setColor(Color::Magenta);
    if (sprite.getGlobalBounds().intersects(circleLastPos.getGlobalBounds()) && !searching) { // si il va a la derniere position du player alors searching = true
        searching = true;
        coolDownSearch.restart();
    }
    else if (!sprite.getGlobalBounds().intersects(circleLastPos.getGlobalBounds()) && !searching) { // si le player sors de la zone de chase il va jusqu'a sa derniere position
        movementManager(lastPlayerPosition, lastPlayerPosition, deltaTime);
    }

    if (searching) { // si searching = true alors l'ennemi va etendre sa zone de recherche a -250 et +250 a partir de la derniere position du player
        movementManager(lastPlayerPosition - 250, lastPlayerPosition + 250, deltaTime);
    }
    if (coolDownSearch.getElapsedTime().asSeconds() > 5 && searching) { // apres 5 secondes de recherche, il revient en patrouille
        searching = false;
        currentState = PATROL;
    }
}

#pragma region Getter / Setter

bool Enemy::setIsGrounded(bool is)
{
    isGrounded = is;
    return isGrounded;
}

bool Enemy::getIsGrounded()
{
    return isGrounded;
}

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

#pragma endregion Getter / Setter

void Enemy::update(float deltaTime) {}

void Enemy::updateReal(float deltaTime, Player& player)
{
    switch (currentState) {
    case PATROL:
        detectPlayer(player);
        patrol(deltaTime);
        break;

    case CHASE:
        detectPlayer(player);
        chase(player, deltaTime);
        break;

    case SEARCH:
        search(lastPlayerPosition, deltaTime);
        detectPlayer(player);
        break;
    }

    velocity.y += gravity * deltaTime;  // Appliquer la gravit�
    position.y += velocity.y * deltaTime;

    sprite.setPosition(position);
    if (enemyState == CHASER) {
        circleDetect.setPosition(position);
        circleLastPos.setPosition(lastPlayerPosition, sprite.getPosition().y);
    }
    circleOne.setPosition(waypointOne);
    circleTwo.setPosition(waypointTwo);
}

void Enemy::draw(RenderWindow& window)
{
    window.draw(circleOne);
    window.draw(circleTwo);
    if (enemyState == CHASER) { 
        window.draw(circleDetect);
        window.draw(circleLastPos);
    }
    window.draw(sprite);
}