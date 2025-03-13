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

void Map::update() {
	collision();
	for (auto& bossrv : bossVector) {
		bossrv->checkCollision(1920, 1080);
	}
}

void Map::collision() {
	playerVector[0]->getSprite().getGlobalBounds();
	//for (auto& monde1 : monde1Vector )  Si touche la sortie donc clear pointeur
}

void Map::monSwitch(ifstream& _Map, string _line, int _z) {
	
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
				player->setPosPos((float)i * 32, (float)_z * 32);
				playerVector.push_back(player);
				break;
			}
			case 'B':
			{
				Boss* boss = new Boss(*playerVector[0]);
				boss->setPos((float)i * 32, (float)_z * 32);
				bossVector.push_back(boss);
				break;
			}

			}
		}
		_z++;
	}
}

void Map::loadMap() {
	if (statePlaying == StatePlaying::Practice) {
		ifstream Map0("Assets/Map/Practice.txt");
		maps.push_back(&Map0);
		string line;
		float z = 0;

		for (auto& mapPractice : maps) {
			monSwitch(*mapPractice, line, z);
		}
	}
	if (statePlaying == StatePlaying::Monde1) {
		ifstream Map1("Assets/Map/Monde1.txt");
		maps.push_back(&Map1);
		string line;
		float z = 0;

		for (auto& mapMonde1 : maps) {
			monSwitch(*mapMonde1, line, z);
		}
	}
}

void Map::draw(RenderWindow& window) {
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
	for (auto& bossrv : bossVector) {
		bossrv->draw(window);
	}
}

void Map::gameOver(RenderWindow& window)
{
	if (isGameOver) {
		RectangleShape gameOverScreen(Vector2f(window.getSize().x, window.getSize().y));
		gameOverScreen.setFillColor(Color(0, 0, 0, 150));
		window.draw(gameOverScreen);

		Font font;
		if (!font.loadFromFile("Assets/Fonts/Minecraft.ttf")) {
			cout << "Erreur chargement police !" << endl;
		}

		Text gameOverText;
		gameOverText.setFont(font);
		gameOverText.setString("GAME OVER");
		gameOverText.setCharacterSize(80);
		gameOverText.setFillColor(Color::Red);
		gameOverText.setStyle(Text::Bold);
		gameOverText.setPosition((window.getSize().x - gameOverText.getGlobalBounds().width) / 2, (window.getSize().y - gameOverText.getGlobalBounds().height) / 2);

		window.draw(gameOverText);
		return;
	}
}
