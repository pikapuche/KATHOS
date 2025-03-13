#pragma once
#include "stdafx.hpp"
#include "Player.hpp"



class Map {

public:
    Texture groundYellowLeftTexture, groundYellowMidTexture, groundYellowRightTexture;
    Texture groundRedLeftTexture, groundRedMidTexture, groundRedRightTexture;
    Texture groundGreenLeftTexture, groundGreenMidTexture, groundGreenRightTexture;

    //Texture wallTexture;

    vector<Sprite*> groundYLVector, groundYMVector, groundYRVector;
    vector<Sprite*> groundRLVector, groundRMVector, groundRRVector;
    vector<Sprite*> groundGLVector, groundGMVector, groundGRVector;

    vector<ifstream*> maps;

    vector<Player*> playerVector;

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

    void update(Player& player); 

    void collision(Player& player);

    void loadMap(Player& player);

    void monSwitch(ifstream& _Map, string line, int z, Player& player);

    void draw(RenderWindow& window, Player& player);

};