#pragma once
#include "Player.hpp"
#include "Boss.hpp"
#include "NuageTox.hpp"
#include "Ennemies.hpp"
#include "Gemme.hpp"
#include "Interactibles.hpp"
#include "Chest.hpp"
#include "Key.hpp"


class Map {
public:

    bool isGameOver = false;
    bool bossZone = false;

    Texture groundYellowLeftTexture, groundYellowMidTexture, groundYellowRightTexture;
    Texture groundRedLeftTexture, groundRedMidTexture, groundRedRightTexture;
    Texture groundGreenLeftTexture, groundGreenMidTexture, groundGreenRightTexture;

    //Texture wallTexture;

    vector<unique_ptr<Sprite>> groundSprites;

    shared_ptr<Player> player = make_shared<Player>();

    shared_ptr<Boss> boss = make_shared<Boss>(*player);

    shared_ptr<NuageTox> nuage = make_shared<NuageTox>();

    vector<unique_ptr<Enemy>> enemies;

    vector<ifstream*> maps;

    vector<Interactible*> interactiblesVector; // Vector of all Interacts


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