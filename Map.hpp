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

    //Texture wallTexture;

    vector<unique_ptr<Sprite>> groundSprites;

    shared_ptr<Player> player = make_shared<Player>();

    vector<ifstream*> maps;

    Sprite* groundSprite;

    //Text win;
    //Font font;

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