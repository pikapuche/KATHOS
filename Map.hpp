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

    vector<Sprite*> groundYLVector, groundYMVector, groundYRVector;
    vector<Sprite*> groundRLVector, groundRMVector, groundRRVector;
    vector<Sprite*> groundGLVector, groundGMVector, groundGRVector;

    vector<ifstream*> maps;

    vector<Player*> playerVector;
    vector<Boss*> bossVector;

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

    void update(); 

    void collision();

    void loadMap();

    void monSwitch(ifstream& _Map, string line, int z);

    void draw(RenderWindow& window);

    void gameOver(RenderWindow& window);

};