#pragma once
#include "stdafx.hpp"
#include "Player.hpp"
#include "Boss.hpp"
#include "NuageTox.hpp"
#include "Ennemis.hpp"
#include "Gemme.hpp"

class Map {
public:

    bool isGameOver = false;

    Texture groundYellowLeftTexture, groundYellowMidTexture, groundYellowRightTexture;
    Texture groundRedLeftTexture, groundRedMidTexture, groundRedRightTexture;
    Texture groundGreenLeftTexture, groundGreenMidTexture, groundGreenRightTexture;

    vector<unique_ptr<Sprite>> groundSprites;
    vector<unique_ptr<Sprite>> gemmeSprites;

    shared_ptr<Player> player = make_shared<Player>();
    shared_ptr<Player> gemme = make_shared<Gemme>();

    vector<ifstream*> maps;

    Sprite* groundSprite;
    Sprite* gemmeSprite;

    enum class StatePlaying {
        Practice,
        Monde1,
        Monde2,
        Monde3,
    };

    StatePlaying statePlaying;

    Map();

    ~Map();

    void update(float deltaTime);

    void collision(float deltaTime);

    void loadMap();

    void monSwitch(ifstream& _Map, string line, int z);

    void draw(RenderWindow& window);

    void gameOver(RenderWindow& window);

};