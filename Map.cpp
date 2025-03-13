#include "Map.hpp"

Map::~Map() {
    for (auto players : vector_player) {
        delete players;
    }
    vector_player.clear();

    for (auto bosses : vector_boss) {
        delete bosses;
    }
    vector_boss.clear();

    for (auto nuages : vector_nuage) {
        delete nuages;
    }
    vector_nuage.clear();
}

bool Map::loadFromFile(string filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Impossible d'ouvrir le fichier de la carte." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        vector_Map.push_back(line);
    }

    if (!font.loadFromFile("Assets/Minecraft.ttf"))
    {
        cout << "error font" << endl << endl;
    }
}

void Map::initAll() {
    if (vector_Map.empty()) return;
    sf::RectangleShape tile(sf::Vector2f(40, 40));

    for (size_t i = 0; i < vector_Map.size(); i++) { // gros code qui permet de parcourir la map
        for (size_t j = 0; j < vector_Map[i].size(); j++) {
            tile.setPosition(j * 40.f, i * 40.f);
            switch (vector_Map[i][j]) {
            case '=': // player
            {
                Player* players = new Player(100.f, 50.f);
                vector_player.push_back(players);
                for (auto& player : vector_player) { // set la position de départ du player
                    player->setPosPos(j * 40.f, i * 40.f);
                }
                break;
            }
            case 'B': // boss
            {
                if (!vector_player.empty()) {
                    Boss* boss = new Boss(*vector_player[0]); // Prend le premier joueur
                    boss->setPos(j * 40.f, i * 40.f - 50);
                    vector_boss.push_back(boss);
                }
                break;
            }
            case 'T': // nuage
            {
                NuageTox* nuage = new NuageTox();
                nuage->setPos(j * 40.f, i * 40.f);
                vector_nuage.push_back(nuage);
                break;
            }
            default:  tile.setFillColor(sf::Color::Black); break;
            }
        }
    }
}

void Map::update(float deltaTime) {
    if (isGameOver) return;

    for (auto& boss : vector_boss) {
        boss->update(deltaTime);
        boss->checkCollision(vector_Map[0].size() * 70);
    }

    for (auto& nuage : vector_nuage) {
        nuage->update(deltaTime);
    }

    checkPlayerBossCollision();
    checkPlayerNuageCollision();
}

void Map::drawMap(sf::RenderWindow& window) {
    if (vector_Map.empty()) return;
    sf::RectangleShape tile(sf::Vector2f(40, 40));

    for (size_t i = 0; i < vector_Map.size(); i++) { // gros code qui permet de parcourir la map
        for (size_t j = 0; j < vector_Map[i].size(); j++) {
            tile.setPosition(j * 40.f, i * 40.f);
            switch (vector_Map[i][j]) {
            case '!': { // sol
                tile.setFillColor(sf::Color::Red); // permet de set le sol de couleur rouge 
                break;
            }

            case '#': {
                tile.setFillColor(sf::Color::Cyan);
                break;
            }

            default:  tile.setFillColor(sf::Color::Black); break;
            }
            window.draw(tile);
        }
    }

    if (isGameOver) {
        sf::RectangleShape gameOverScreen(sf::Vector2f(window.getSize().x, window.getSize().y));
        gameOverScreen.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(gameOverScreen);

        sf::Font font;
        if (!font.loadFromFile("Assets/Fonts/Minecraft.ttf")) {
            cout << "Erreur chargement police !" << endl;
        }

        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER");
        gameOverText.setCharacterSize(80);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setStyle(sf::Text::Bold);
        gameOverText.setPosition((window.getSize().x - gameOverText.getGlobalBounds().width) / 2, (window.getSize().y - gameOverText.getGlobalBounds().height) / 2);

        window.draw(gameOverText);
        return;
    }
}

void Map::collisionMap(sf::RenderWindow& window, Player& player, float deltaTime) {
    if (vector_Map.empty()) return;
    sf::RectangleShape tile(sf::Vector2f(40, 40));

    for (size_t i = 0; i < vector_Map.size(); i++) { // gros code qui permet de parcourir la map 
        for (size_t j = 0; j < vector_Map[i].size(); j++) {
            tile.setPosition(j * 40.f, i * 40.f); // set la position des différentes tiles sur la map
            switch (vector_Map[i][j]) {
            case '!': // plateformes
                if (tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds()) && tile.getPosition().y > player.getPosPos().y) { // si le joueur entre en collision avec la plateforme mais qu'il est plus bas alors on set sa pos en dessous de la plateforme pour pas qu'il la traverse
                    player.setPosPos(player.getPosPos().x, tile.getPosition().y + 40);
                    player.setIsJumping(true);
                    //player.setVelocity(player.getVelocity().x, player.getJumpForce() * deltaTime * 18);
                }
                else if (tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds()) && tile.getPosition().y < player.getPosPos().y) { // si le joueur entre en collision avec une plateforme alors il set sa position en haut de celle ci
                    cout << "collision plateforme" << endl;
                    player.setPosPos(player.getPosPos().x, tile.getPosition().y - 40);
                    player.setIsJumping(false);
                    player.setVelocity(player.getVelocity().x, 0);
                }
                else if (!player.getIsJumping() && !tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) { // si le joueur ne saute pas et qu'il n'est pas en collision alors il applique la gravité
                    player.setVelocity(player.getVelocity().x, player.getJumpForce() * deltaTime * 18);
                }
                break;
            case '#': // sol 
                if (tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) { // si le joueur entre en collision avec une plateforme alors il set sa position en haut de celle ci
                    cout << "collision sol" << endl;
                    player.setPosPos(player.getPosPos().x, tile.getPosition().y - 40);
                    player.setIsJumping(false);
                    player.setVelocity(player.getVelocity().x, 0);
                }
                if (!player.getIsJumping() && !tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) { // si le joueur ne saute pas et qu'il n'est pas en collision alors il applique la gravité
                    player.setVelocity(player.getVelocity().x, player.getJumpForce() * deltaTime * 18);
                }
                if (tile.getPosition().y < player.getPosPos().y) {
                    player.setPosPos(player.getPosPos().x, tile.getPosition().y - 40);
                }
                break;
            default:  tile.setFillColor(sf::Color::Black); break;
            }
        }
    }
}

void Map::checkPlayerBossCollision() {
    if (vector_player.empty() || vector_boss.empty() || isGameOver) return;

    for (auto& player : vector_player) 
    {
        for (auto& boss : vector_boss)
        {
            if (player->getShape().getGlobalBounds().intersects(boss->getSprite().getGlobalBounds()))
            {
                cout << "Collision entre le joueur et le boss" << endl;
                isGameOver = true;
            }
        }
    }
}

void Map::checkPlayerNuageCollision() {
    if (vector_player.empty() || vector_nuage.empty() || isGameOver) return;

    for (auto& player : vector_player)
    {
        for (auto& nuage : vector_nuage)
        {
            if (player->getShape().getGlobalBounds().intersects(nuage->getShape().getGlobalBounds()))
            {
                cout << "Collision entre le joueur et le nuage" << endl;
                isGameOver = true;
            }
        }
    }
}

bool Map::getIsGameOver()
{
    return isGameOver;
}

/*void Map::collisionMap(sf::RenderWindow& window, Player& player, float deltaTime) {
    if (vector_Map.empty()) return;
    sf::RectangleShape tile(sf::Vector2f(40, 40));

    for (size_t i = 0; i < vector_Map.size(); i++) {
        for (size_t j = 0; j < vector_Map[i].size(); j++) {
            tile.setPosition(j * 40.f, i * 40.f); // met à jour la position de la tuile

            bool isColliding = tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds());

            switch (vector_Map[i][j]) {
            case '!': // plateformes
                if (isColliding) {
                    if (tile.getPosition().y > player.getPosPos().y) {
                        player.setPosPos(player.getPosPos().x, tile.getPosition().y + 40);
                        player.setIsJumping(true);
                    }
                    else {
                        player.setPosPos(player.getPosPos().x, tile.getPosition().y - 40);
                        player.setIsJumping(false);
                        player.setVelocity(player.getVelocity().x, 0);
                    }
                }
                break;
            case '#': // sol
                if (isColliding) {
                    player.setPosPos(player.getPosPos().x, tile.getPosition().y - 40);
                    player.setIsJumping(false);
                    player.setVelocity(player.getVelocity().x, 0);
                }
                break;
            default:
                tile.setFillColor(sf::Color::Black);
                break;
            }

            // Appliquer la gravité si le joueur n'est pas en train de sauter
            if (!player.getIsJumping() && !isColliding) {
                player.setVelocity(player.getVelocity().x, player.getJumpForce() * deltaTime * 18);
            }
        }
    }
}*/
