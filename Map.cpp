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

    for (size_t i = 0; i < vector_Map.size(); i++) {
        for (size_t j = 0; j < vector_Map[i].size(); j++) {
            switch (vector_Map[i][j]) {
            case '=':
            {
                Player* players = new Player(j * 40.f, i * 40.f, 100.f, 50.f);
                vector_player.push_back(players);
                break;
            }

            default:  tile.setFillColor(sf::Color::Black); break;
            }
            tile.setPosition(j * 40.f, i * 40.f);
        }
    }
}

void Map::drawMap(sf::RenderWindow& window) {
    if (vector_Map.empty()) return;
    sf::RectangleShape tile(sf::Vector2f(40, 40));

    for (size_t i = 0; i < vector_Map.size(); i++) {
        for (size_t j = 0; j < vector_Map[i].size(); j++) {
            switch (vector_Map[i][j]) {
            case '!': {
                tile.setFillColor(sf::Color::Red);
                break;
            }

            case '#': {
                tile.setFillColor(sf::Color::Cyan);
                break;
            }

            default:  tile.setFillColor(sf::Color::Black); break;
            }
            tile.setPosition(j * 40.f, i * 40.f);
            window.draw(tile);
            if (winGame) {
                this_thread::sleep_for(std::chrono::seconds(3));
                window.close();
            }
        }
    }
}

void Map::collisionMap(sf::RenderWindow& window, Player& player, float deltaTime) {
    if (vector_Map.empty()) return;
    sf::RectangleShape tile(sf::Vector2f(40, 40));

    for (size_t i = 0; i < vector_Map.size(); i++) {
        for (size_t j = 0; j < vector_Map[i].size(); j++) {
            switch (vector_Map[i][j]) {
            case '!':
                if (tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) {
                    cout << "collision" << endl;
                    player.setPosPos(player.getPosPos().x, tile.getPosition().y - 40);
                    player.setIsJumping(false);
                    player.setVelocity(player.getVelocity().x, 0);
                }
                if (!player.getIsJumping() && !tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) {
                    //player.setVelocity(player.getVelocity().x, player.getGravity() * deltaTime);
                    player.setVelocity(player.getVelocity().x, player.getJumpForce() * deltaTime * 18);
                }
                break;
            case '#':
                break;
            default:  tile.setFillColor(sf::Color::Black); break;
            }
            tile.setPosition(j * 40.f, i * 40.f);
        }
    }
}
