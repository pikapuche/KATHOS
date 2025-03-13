#pragma once
#include "stdafx.hpp"
#include "Ennemis.hpp"
#include "Gemme.hpp"

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

    Vector2f waypoint1;
    Vector2f waypoint2;

    bool winGame = false;

public:

    vector<Player*> vector_player;

    vector<Gemme*> vector_gemme;

    vector<Enemy*> vector_enemy;

    ~Map();

    vector<string> vector_Map;

    bool loadFromFile(string filename);

    void initAll();

    void drawMap(sf::RenderWindow& window);

    void collisionMap(Player& player, Enemy& enemy, float deltaTime);
};