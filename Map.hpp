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

    bool bossZone = false;
    bool mapBoss = false;

    Texture groundYellowLeftTexture, groundYellowMidTexture, groundYellowRightTexture;
    Texture groundRedLeftTexture, groundRedMidTexture, groundRedRightTexture;
    Texture groundGreenLeftTexture, groundGreenMidTexture, groundGreenRightTexture;
    Texture practiceTexture, salle1Texture, salle2Texture, salle3Texture, salle4Texture, salle5Texture, salle6Texture;

    Sprite practiceSprite, salle1Sprite, salle2Sprite, salle3Sprite, salle4Sprite, salle5Sprite, salle6Sprite;

    enum class  GemmeState { NADA, SPRINT, DASH, DOUBLEJUMP };
    GemmeState gemmeState;

    enum class MapState { PRACTICE, SALLE1, SALLE2, SALLE3, SALLE4, SALLE5, SALLE6 };
    MapState mapState;

    vector<unique_ptr<Sprite>> groundSprites;
    vector<unique_ptr<RectangleShape>> tpShapeA;
    vector<unique_ptr<RectangleShape>> tpShapeB;
    vector<unique_ptr<Gemme>> gemmeSprites;

    shared_ptr<Player> player = make_shared<Player>();

    vector<unique_ptr<Boss>> bosses;

    vector<unique_ptr<Enemy>> enemies;

    vector<unique_ptr<NuageTox>> clouds;

    vector<ifstream*> maps;

    vector<shared_ptr<Interactible>> interactiblesVector;

    Map();

    ~Map();

    void update(float deltaTime, RenderWindow& window);

    void reinitilisePlayer();

    void clearMap();

    void collision(float deltaTime);

    void loadMap();

    void monSwitch(ifstream& _Map, string line, int z);

    void draw(RenderWindow& window);

};