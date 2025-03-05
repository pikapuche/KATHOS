#include <iostream>
#include "SFML/Graphics.hpp"
#include <fstream>
#include <vector>
#include <windows.h>
#include <thread>

using namespace std;
using namespace sf;

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 15;
const int CELL_SIZE = 40;

class Player {
protected : 
    sf::Vector2f position;
    sf::Vector2f velocity;
    float SPEED = 200.0f;  // Vitesse de d�placement horizontal
    const float gravity = 981.0f;  // Gravit� en pixels par seconde carr�e (simulation)
    float jumpForce = 550.f;  // Force initiale du saut
    bool isJumping;

public : 

    float groundHeight = 13 * 40.f;  // Hauteur du sol a modif dans le jeu, le but est d'arriver a faire en sorte de remplacer cette valeur par les cases de nos plateformes en soit
    RectangleShape shape;

    Player(float startX, float startY, float s, float jForce) {
        shape.setFillColor(sf::Color::Green);
        shape.setSize(sf::Vector2f(40.f, 40.f));
        position.x = startX;
        position.y = startY;
        velocity.y = 0;  // Pas de mouvement vertical au d�part
        isJumping = false;
    }

    void movementManager(float deltaTime) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { position.x -= SPEED * deltaTime; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { position.x += 1 + SPEED * deltaTime; }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { jump(); }

        // G�rer le saut
        if (isJumping) {
            velocity.y += gravity * deltaTime;  // Appliquer la gravit�
            position.y += velocity.y * deltaTime;

            // V�rifier si le joueur touche le sol
            if (position.y >= groundHeight) { // si le y est sup ou �gal � 500 alors on fixe le y a 500 et on dit que le saut se stop 
                position.y = groundHeight;
                isJumping = false;
                velocity.y = 0;  // Arr�ter le mouvement vertical
            }
        }

        /*sf::Vector2f newPosition = shape.getPosition() + movement;
        sf::FloatRect newBounds(newPosition, shape.getSize());

        auto isWalkable = [&](float x, float y) {
            int gridX = static_cast<int>(x / CELL_SIZE);
            int gridY = static_cast<int>(y / CELL_SIZE);
            return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
            };

        if (isWalkable(newBounds.left - 2, newBounds.top - 2) &&
            isWalkable(newBounds.left + newBounds.width + 2, newBounds.top - 2) &&
            isWalkable(newBounds.left - 2, newBounds.top + newBounds.height + 2) &&
            isWalkable(newBounds.left + newBounds.width + 2, newBounds.top + newBounds.height + 2)) {
            shape.move(movement);
        }*/

        shape.setPosition(position);
    }

    void jump() {
        if (!isJumping) {  // Sauter uniquement si le joueur est sur le sol
            isJumping = true;
            velocity.y = -jumpForce;  // Appliquer une force initiale vers le haut
        }
    }

    void update(float deltaTime) {
        movementManager(deltaTime);
    }

    void draw(RenderWindow& window) {
        window.draw(shape);
    }
};

/*struct Cell {
    bool walkable;
    sf::Vector2f position;
    sf::RectangleShape shape;
};

class Grid {
private:
    std::vector<std::vector<Cell>> cells;

public:
    Grid() {
        cells.resize(GRID_HEIGHT, std::vector<Cell>(GRID_WIDTH, { true, {0, 0}, sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE)) }));
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            for (int x = 0; x < GRID_WIDTH; ++x) {
                cells[y][x].position = sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE);
                cells[y][x].shape.setPosition(cells[y][x].position);
                cells[y][x].shape.setFillColor(sf::Color::Transparent);
                cells[y][x].shape.setOutlineThickness(1);
                cells[y][x].shape.setOutlineColor(sf::Color(50, 50, 50));
            }
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;
            return;
        }

        for (int y = 0; y < GRID_HEIGHT; ++y) {
            std::string line;
            if (!std::getline(file, line)) break;
            for (int x = 0; x < GRID_WIDTH && x < line.size(); ++x) {
                cells[y][x].walkable = (line[x] == '0');
                if (!cells[y][x].walkable) {
                    cells[y][x].shape.setFillColor(sf::Color::White);
                }
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            for (int x = 0; x < GRID_WIDTH; ++x) {
                window.draw(cells[y][x].shape);
            }
        }
    }

    Cell& getCell(int x, int y) {
        return cells[y][x];
    }
};*/

class Map {
protected:
    sf::Texture groundTexture;
    sf::Texture wallTexture;

    sf::Text win;
    sf::Font font;

    bool winGame = false;

public:

    vector<Player*> vector_player;

    ~Map() {
        for (auto players : vector_player) {
            delete players;
        }
        vector_player.clear();
    }

    vector<string> vector_Map;

    bool loadFromFile(string filename) {
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

    void initAll() {
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

    void drawMap(sf::RenderWindow& window) {
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

    void collisionMap(sf::RenderWindow& window, Player& player) {
        if (vector_Map.empty()) return;
        sf::RectangleShape tile(sf::Vector2f(40, 40));
        
        for (size_t i = 0; i < vector_Map.size(); i++) {
            for (size_t j = 0; j < vector_Map[i].size(); j++) {
                switch (vector_Map[i][j]) {
                case '!':
                    if (tile.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
                        cout << "collision" << endl;
                        // ici on met le bidule
                    }
                    else {
                        player.groundHeight = 13 * 40.f;
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
};

int main() {
    // Cr�ation de la fen�tre
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test mini studio 2D");
    window.setFramerateLimit(60);

    Map map;
    //Grid grid;

    map.loadFromFile("C:\\Users\\quent\\OneDrive\\Documents\\Cours C++\\Mini studio\\mapV1.txt");
    map.initAll();

    //Player player(50, 500, 100.f, 50.f);
    
    Clock clock;

    // Boucle principale
    while (window.isOpen()) {
        sf::Time deltaT = clock.restart();
        float deltaTime = deltaT.asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Fermer la fen�tre
        }

        // Effacer la fen�tre
        window.clear();

        map.drawMap(window);

        for (auto& players : map.vector_player) {
            players->update(deltaTime);
            players->draw(window);
            map.collisionMap(window, *players);
        }

        //player.update(deltaTime);

        //player.draw(window);

        // Afficher le contenu
        window.display();
    }

    return 0;
}