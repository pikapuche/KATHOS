#include "Map.hpp"

Map::~Map() {
    for (auto players : vector_player) {
        delete players;
    }
    vector_player.clear();
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
                Player* players = new Player();
                vector_player.push_back(players);
                for (auto& player : vector_player) { // set la position de dï¿½part du player
                    player->setPosPos(j * 40.f, i * 40.f);
                }
                break;
            }
            case '*': 
            {
                Gemme* gemmes = new Gemme();
                vector_gemme.push_back(gemmes);
                for (auto& gemme : vector_gemme) { // set la position de départ de la gemme
                    gemme->setPosition(j * 40.f, i * 40.f);
                }
                break;
            }

            default:  tile.setFillColor(sf::Color::Black); break;
            }
        }
    }
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
            case 'K': {

                break;
            }

            default:  tile.setFillColor(sf::Color::Black); break;
            }
            window.draw(tile);
        }
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
                    player.setIsGrounded(false);
                }
                else if (tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds()) && tile.getPosition().y < player.getPosPos().y) { // si le joueur entre en collision avec une plateforme alors il set sa position en haut de celle ci
                    player.setPosPos(player.getPosPos().x, tile.getPosition().y - 40);
                    player.setIsJumping(false);
                    player.setIsGrounded(true);
                    player.setVelocity(player.getVelocity().x, 0);
                } 
                break;
            case '#': // sol 
                if (tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) { // si le joueur entre en collision avec le sol alors il set sa position en haut du sol
                    player.setPosPos(player.getPosPos().x, tile.getPosition().y - 40);
                    player.setIsJumping(false);
                    player.setIsGrounded(true);
                    player.setVelocity(player.getVelocity().x, 0);
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