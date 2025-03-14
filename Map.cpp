#include "Map.hpp"

Map::Map() : statePlaying(StatePlaying::Practice) {
	groundYellowLeftTexture.loadFromFile("Assets/texture/Map/groundYellowLeft.png");
	groundYellowMidTexture.loadFromFile("Assets/texture/Map/groundYellowMid.png");
	groundYellowRightTexture.loadFromFile("Assets/texture/Map/groundYellowRight.png");
	groundRedLeftTexture.loadFromFile("Assets/texture/Map/groundRedLeft.png");
	groundRedMidTexture.loadFromFile("Assets/texture/Map/groundRedMid.png");
	groundRedRightTexture.loadFromFile("Assets/texture/Map/groundRedRight.png");
	groundGreenLeftTexture.loadFromFile("Assets/texture/Map/groundGreenLeft.png");
	groundGreenMidTexture.loadFromFile("Assets/texture/Map/groundGreenMid.png");
	groundGreenRightTexture.loadFromFile("Assets/texture/Map/groundGreenRight.png");

}

void Map::update() {
	collision();
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
			case 'C':
			{
				Chest* chest = new Chest(true);
				chest->setPosPos((float)i * 32, (float)_z * 32 - 17);
				interactiblesVector.push_back(chest);
				break;
			}

			case 'K':
				Key * key = new Key();
				key->setPosPos((float)i * 32, (float)_z * 32 - 25);
				interactiblesVector.push_back(key);
				break;
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
	for (auto& interactv : interactiblesVector) {
		interactv->draw(window);
	}
}

void Map::gameOver(RenderWindow& window)
{
	if (isGameOver) {
		sf::RectangleShape gameOverScreen(sf::Vector2f(window.getSize().x, window.getSize().y));
		gameOverScreen.setFillColor(sf::Color(0, 0, 0, 150));
		window.draw(gameOverScreen);

		sf::Font font;
		if (!font.loadFromFile("Assets/Fonts/Minecraft.ttf")) {
			cout << "Erreur chargement police !" << endl;
		}

		sf::Text gameOverText;
		gameOverText.setFont(font);
		gameOverText.setString("GAME OVER");
		gameOverText.setCharacterSize(80);
		gameOverText.setFillColor(sf::Color::Red);
		gameOverText.setStyle(sf::Text::Bold);
		gameOverText.setPosition((window.getSize().x - gameOverText.getGlobalBounds().width) / 2, (window.getSize().y - gameOverText.getGlobalBounds().height) / 2);

		window.draw(gameOverText);
		return;
	}
}
