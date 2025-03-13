#include "Map.hpp"

Map::Map() : statePlaying(StatePlaying::Practice) {
	groundYellowLeftTexture.loadFromFile("Assets/Map/groundYellowLeft.png");
	groundYellowMidTexture.loadFromFile("Assets/Map/groundYellowMid.png");
	groundYellowRightTexture.loadFromFile("Assets/Map/groundYellowRight.png");
	groundRedLeftTexture.loadFromFile("Assets/Map/groundRedLeft.png");
	groundRedMidTexture.loadFromFile("Assets/Map/groundRedMid.png");
	groundRedRightTexture.loadFromFile("Assets/Map/groundRedRight.png");
	groundGreenLeftTexture.loadFromFile("Assets/Map/groundGreenLeft.png");
	groundGreenMidTexture.loadFromFile("Assets/Map/groundGreenMid.png");
	groundGreenRightTexture.loadFromFile("Assets/Map/groundGreenRight.png");

}

void Map::update(Player& player) {
	collision(player);
}

void Map::collision(Player& player) {
	player.getShape().getGlobalBounds();
	//for (auto& monde1 : monde1Vector )  Si touche la sortie donc clear pointeur

	// mettre les collisions

}

void Map::monSwitch(ifstream& _Map, string _line, int _z, Player& _player) {
	
	while (getline(_Map, _line)) {
        for (int i = 0; i < _line.size(); i++) {
            switch (_line[i]) {
                cout << _line[i] << endl;
            case '1':
            {
                Sprite* gGL = new Sprite;
                gGL->setTexture(groundGreenLeftTexture);
                gGL->setPosition({ (float)i * 32,(float)_z * 32 });
                groundGLVector.push_back(gGL);
                break;
            }
			case '2':
			{
				Sprite* gGM = new Sprite;
				gGM->setTexture(groundGreenMidTexture);
				gGM->setPosition({ (float)i * 32,(float)_z * 32 });
				groundGMVector.push_back(gGM);
				break;
			}
			case '3':
			{
				Sprite* gGR = new Sprite;
				gGR->setTexture(groundGreenRightTexture);
				gGR->setPosition({ (float)i * 32,(float)_z * 32 });
				groundGMVector.push_back(gGR);
				break;
			}
			case 'P':
			{
				Player* player = new Player;
				_player.setPosPos((float)i * 32,(float)_z * 32);
				playerVector.push_back(player);
				break;
			}

            }
        }
		_z++;
    }
}

void Map::loadMap(Player& player) {
	if (statePlaying == StatePlaying::Practice) {
		ifstream Map0("Assets/Map/Practice.txt");
		maps.push_back(&Map0);
		string line;
		float z = 0;

		for (auto& mapPractice : maps) {
			monSwitch(*mapPractice, line, z, *playerVector[0]);
		}
	}

	if (statePlaying == StatePlaying::Monde1) {
		ifstream Map1("Assets/Map/Monde1.txt");
		maps.push_back(&Map1);
		string line;
		float z = 0;

		for (auto& mapMonde1 : maps) {
			monSwitch(*mapMonde1, line, z, player);
		}
	}


}

void Map::draw(RenderWindow& window,Player& player) {
	for (auto& groundGL : groundGLVector) {
		window.draw(*groundGL);
	}
	for (auto& groundGM : groundGMVector) {
		window.draw(*groundGM);
	}
	for (auto& groundGR : groundGRVector) {
		window.draw(*groundGR);
	}
	for (auto& playerv : playerVector) {
		playerv->draw(window);
	}
}
