#include "Ennemies.hpp"

Enemy::Enemy() : Entity(position.x, position.y)
{
    DEBUG = false;
    if (DEBUG) {
        rectangleDetect.setFillColor(Color(255, 0, 0, 50));
        circleOne.setFillColor(Color::Yellow);
        circleTwo.setFillColor(Color::Blue);
        circleLastPos.setFillColor(Color::Cyan);
        attackDetect.setFillColor(Color(0, 255, 0, 50));
        attackShape.setFillColor(Color::Yellow);
    }
    rectangleDetect.setOrigin(318, 11); // 150 (radius) - 64 (taille sprite) + 32 (moitiï¿½ taille sprite pour centrer) 
    rectangleDetect.setSize(Vector2f(700, 75));
    currentState = PATROL;
    circleOne.setRadius(10.0f); // point de patrouille 1
    circleTwo.setRadius(10.0f); // point de patrouille 2
    texture.loadFromFile("Assets/Ennemies/walk.png");
    textureAttackMove.loadFromFile("Assets/Ennemies/Shoot.png");
    sprite.setTexture(texture);
    boxCol1 = 64; // valeur qui permet de gï¿½rer les collisions (distances entre plateformes)
    boxCol2 = 64; // 
    circleLastPos.setRadius(20.f); // point de derniere position du player
    attackDetect.setSize(Vector2f(75.f, 20.f));
    attackShape.setSize(Vector2f(nuage, 20.f));
    life = 50;
    lifeBar.setSize(Vector2f(life, 10));
    lifeBar.setFillColor(Color::Green);
    rectBar.setSize(Vector2f(life, 10));
    rectBar.setFillColor(Color::Transparent);
    rectBar.setOutlineColor(Color::White);
    rectBar.setOutlineThickness(2);
    directionState = LEFT;
}

void Enemy::detectPlayer(Player& player) 
{
    if (enemyState == CHASER) {
        if (rectangleDetect.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()) && currentState != CHASE) { // si l'ennemi est un chasseur et que le perso entre dans le cercle de detection
            currentState = CHASE;
            // texture course
        }
        else if (!rectangleDetect.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()) && currentState == CHASE) {
            lastPlayerPosition = player.getSprite().getPosition().x;
            currentState = SEARCH;
            coolDownSearch.restart(); 
        }
    }
}

void Enemy::movementManager(float pos, float pos2, float deltaTime) { // permet de gerer le mouvement de l'ennemi
    if (position.x < pos && directionState != RIGHT) {
        directionState = RIGHT;
        sprite.setTextureRect(IntRect(0, 0, 64, 64));
    }
    else if (position.x > pos2 && directionState != LEFT) {
        directionState = LEFT;
        sprite.setTextureRect(IntRect(64, 0, -64, 64));
    }

    if (directionState == RIGHT) {
        position.x += SPEED * deltaTime;
        attackDetect.setRotation(0);
        attackDetect.setPosition(position.x + 64, position.y + 23);
        attackShape.setRotation(0);
        attackShape.setPosition(position.x + 64, position.y + 23);
    }
    else {
        position.x -= SPEED * deltaTime;
        attackDetect.setRotation(180);
        attackDetect.setPosition(position.x, position.y + 43);
        attackShape.setRotation(180);
        attackShape.setPosition(position.x, position.y + 43);
    }

    velocity.y += gravity * deltaTime;  // Appliquer la gravitï¿½
    position.y += velocity.y * deltaTime;

    sprite.setPosition(position);
    if (enemyState == CHASER) {
        rectangleDetect.setPosition(position);
        circleLastPos.setPosition(lastPlayerPosition, sprite.getPosition().y);
    }
    circleOne.setPosition(waypointOne);
    circleTwo.setPosition(waypointTwo);
    attackShape.setSize(Vector2f(nuage, 20.f));
    lifeBar.setPosition(position.x + 5, position.y - 26);
    rectBar.setPosition(position.x + 5, position.y - 26);

    if (sprite.getPosition().y < 0) { // haut de l'ï¿½cran
        sprite.setPosition(position.x, position.y = 64);
    }
    if (sprite.getPosition().y > 1016) { // bas de l'ï¿½cran 
        sprite.setPosition(position.x, position.y = 1016);
    }
    if (sprite.getPosition().x < 0) { // gauche de l'ï¿½cran
        sprite.setPosition(position.x = 0, position.y);
    }
    if (sprite.getPosition().x > 1856) { // droite de l'ï¿½cran
        sprite.setPosition(position.x = 1856, position.y);
    }
}

void Enemy::animationManager(float deltaTime) {
    if (attack) {
        sprite.setTexture(textureAttackMove);
        animAttackTimeDecr += deltaTime;
        anim_attack.y = 0;
        if (animAttackTimeDecr > 0.08f) {
            anim_attack.x++;
            animAttackTimeDecr = 0;
        }
        if (directionState == LEFT) {
            if (anim_attack.x > 6) {
                anim_attack.x = 1;
            }
            sprite.setTextureRect(IntRect(anim_attack.x * 64, 0, -64, 64));
            sprite.setPosition(sprite.getPosition().x + 64, sprite.getPosition().y);
        }
        else if (directionState == RIGHT) {
            if (anim_attack.x > 5) {
                anim_attack.x = 0;
            }
            sprite.setTextureRect(IntRect(anim_attack.x * 64, 0, 64, 64));
        }
    }
    else {
        sprite.setTexture(texture);
        animIdleTimeDecr += deltaTime;
        anim_idle.y = 0;
        if (animIdleTimeDecr > 0.08f) {
            anim_idle.x++;
            animIdleTimeDecr = 0;
        }
        if (directionState == LEFT) {
            if (anim_idle.x > 6) {
                anim_idle.x = 1;
            }
            sprite.setTextureRect(IntRect(anim_idle.x * 64, 0, -64, 64));
            sprite.setPosition(sprite.getPosition().x + 64, sprite.getPosition().y);
        }
        else if (directionState == RIGHT) {
            if (anim_idle.x > 5) {
                anim_idle.x = 0;
            }
            sprite.setTextureRect(IntRect(anim_idle.x * 64, 0, 64, 64));
        }
    }
}

void Enemy::attackPlayer(Player& player) {
    if (attackDetect.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) { // si la zone d'attaque touche le joueur
        // anim qui fait pop le nuage et au moment oï¿½ le nuage touche le perso alors paf
        if (!attack) {
            clockAttack.restart();
        }
        attack = true;
    }

    if (clockAttack.getElapsedTime().asMilliseconds() > 2 && attack) { // toute les 2 millisecondes le nuage grandi
        nuage++;
    }
    if (nuage == 75.f) {
        nuage = 0;
        if(!attackDetect.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) attack = false;
    }

    if (attackShape.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) { // si le nuage touche le perso sa vitesse ralentie
        if (!slow) {
            coolDownSlow.restart();
        }
        slow = true;
    }

    if (clockAttack.getElapsedTime().asSeconds() < 2 && slow) { // slow pendant 2 secondes
        player.setSPEED(100.f);
    }
}

void Enemy::patrol(float deltaTime, Player& player) // fait simplement des gauche droite entre 2 points
{
    movementManager(circleOne.getPosition().x, circleTwo.getPosition().x, deltaTime);
    attackPlayer(player);
}

void Enemy::chase(Player& player, float deltaTime) // suit le perso tant qu'il est dans la zone de detection
{
    movementManager(player.getSprite().getPosition().x, player.getSprite().getPosition().x, deltaTime);
    attackPlayer(player);
}

void Enemy::search(float lastPlayerPosition, float deltaTime, Player& player) // quand le perso sort de la zone il va jusqu'a sa derniere position et effectue des gauche droite pour le chercher
{
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
    attackPlayer(player);
}

void Enemy::takeDamage(Player& player)
{
    if (life > 35) {
        lifeBar.setFillColor(Color::Green);
    }
    else if (life < 15) {
        lifeBar.setFillColor(Color::Red);
    }
    else if (life < 35) {
        lifeBar.setFillColor(Color::Yellow);
    }
    if (player.getAttackShape().getGlobalBounds().intersects(sprite.getGlobalBounds()) && player.stateWeapon == player.SPAWN) {
        setLife(-2);
        lifeBar.setSize(Vector2f(life, 10));
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

void Enemy::update(float deltaTime, Player& player)
{
    switch (currentState) {
    case PATROL:
        animationManager(deltaTime);
        detectPlayer(player);
        patrol(deltaTime, player);
        break;

    case CHASE:
        animationManager(deltaTime);
        detectPlayer(player);
        chase(player, deltaTime);
        break;

    case SEARCH:
        animationManager(deltaTime);
        detectPlayer(player);
        search(lastPlayerPosition, deltaTime, player);
        break;
    }
    takeDamage(player);
}

void Enemy::draw(RenderWindow& window)
{
    if (DEBUG) {
        window.draw(circleOne);
        window.draw(circleTwo);
        if (enemyState == CHASER) {
            window.draw(rectangleDetect);
            window.draw(circleLastPos);
        }
    }
    window.draw(attackDetect);
    window.draw(attackShape);
    window.draw(lifeBar);
    window.draw(rectBar);
    window.draw(sprite);
}