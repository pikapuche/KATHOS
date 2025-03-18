#pragma once
#include "Player.hpp"
#include "Boss.hpp"
#include "NuageTox.hpp"
#include "Ennemies.hpp"
#include "Gemme.hpp"
#include "Interactibles.hpp"
#include "Chest.hpp"
#include "Key.hpp"
#include "Door.hpp"


class Map {
public:

    bool isGameOver = false;
    bool isWin = false;
    bool bossZone = false;

    Texture groundYellowLeftTexture, groundYellowMidTexture, groundYellowRightTexture;
    Texture groundRedLeftTexture, groundRedMidTexture, groundRedRightTexture;
    Texture groundGreenLeftTexture, groundGreenMidTexture, groundGreenRightTexture;

    vector<unique_ptr<Sprite>> groundSprites;
    vector<unique_ptr<Gemme>> gemmeSprites;

    shared_ptr<Player> player = make_shared<Player>();

    vector<unique_ptr<Boss>> bosses;

    vector<unique_ptr<Enemy>> enemies;

    vector<unique_ptr<NuageTox>> clouds;

    vector<ifstream*> maps;

    std::vector<std::shared_ptr<Interactible>> interactiblesVector;


    //Text win;
    //Font font;

    enum class StatePlaying {
        Practice,
        Monde1,
        Monde2,
        Monde3,
        Boss
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
    
    void resetAll();

    void Win(RenderWindow& window);

};