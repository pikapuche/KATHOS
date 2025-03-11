#include "stdafx.hpp"
#include "Player.hpp"

<<<<<<< Updated upstream
const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 15;
const int CELL_SIZE = 16;

class Map {
protected:
    sf::Texture groundTexture;
    sf::Texture wallTexture;

    sf::Text win;
    sf::Font font;

    bool winGame = false;

=======
class Map {
>>>>>>> Stashed changes
public:
    Texture groundYellowLeftTexture, groundYellowMidTexture, groundYellowRightTexture;
    Texture groundRedLeftTexture, groundRedMidTexture, groundRedRightTexture;
    Texture groundGreenLeftTexture, groundGreenMidTexture, groundGreenRightTexture;

    //Texture wallTexture;

<<<<<<< Updated upstream
    ~Map();
=======
    vector<Sprite*> groundYLVector, groundYMVector, groundYRVector;
    vector<Sprite*> groundRLVector, groundRMVector, groundRRVector;
    vector<Sprite*> groundGLVector, groundGMVector, groundGRVector;

    vector<ifstream*> maps;
>>>>>>> Stashed changes

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

    void draw(RenderWindow& window);
};