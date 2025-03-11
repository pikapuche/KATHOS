#pragma once
#include "stdafx.hpp"
#include "Player.hpp"
#include "Boss.hpp"
#include "NuageTox.hpp"

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 15;
const int CELL_SIZE = 40;

class Map 
{
protected:
    sf::Texture groundTexture;
    sf::Texture wallTexture;

    float playerHeight = 70.0f;

    sf::Text win;
    sf::Font font;

    bool winGame = false;

    bool isGameOver = false;

public:
    vector<Boss*> vector_boss;
    vector<Player*> vector_player;
    vector<NuageTox*> vector_nuageTox;

    ~Map();

    vector<string> vector_Map;

    bool loadFromFile(string filename);

    void initAll();

    void drawMap(sf::RenderWindow& window);

    void update(float deltaTime);

    void collisionMap(sf::RenderWindow& window, Player& player, float deltaTime);

    void checkPlayerBossCollision();

    void checkPlayerNuageCollision();

    bool getIsGameOver();
};