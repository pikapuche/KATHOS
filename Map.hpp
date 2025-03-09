#include "stdafx.hpp"
#include "Player.hpp"

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 15;
const int CELL_SIZE = 40;

class Map {
protected:
    sf::Texture groundTexture;
    sf::Texture wallTexture;

    float playerHeight = 70.0f;

    sf::Text win;
    sf::Font font;

    bool winGame = false;

public:

    vector<Player*> vector_player;

    ~Map();

    vector<string> vector_Map;

    bool loadFromFile(string filename);

    void initAll();

    void drawMap(sf::RenderWindow& window);

    void collisionMap(sf::RenderWindow& window, Player& player, float deltaTime);
};