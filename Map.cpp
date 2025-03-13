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

Map::~Map()
{
	
}

void Map::update(float deltaTime) {
	collision(deltaTime);
}

void Map::collision(float deltaTime) {
	for (auto& ground : groundSprites) {
		player->collisionPlatform(*ground, deltaTime);
	}
}

void Map::monSwitch(ifstream& _Map, string _line, int _z) {
	
	while (getline(_Map, _line)) {
		for (int i = 0; i < _line.size(); i++) {
			switch (_line[i]) {
				cout << _line[i] << endl;
			case '1':
			{
				auto left = std::make_unique<Sprite>();  // La bonne façon de créer un unique_ptr
				left->setTexture(groundGreenLeftTexture);
				left->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(std::move(left));  // Utilise std::move pour transférer la propriété
				break;
			}
			case '2':
			{
				auto mid = std::make_unique<Sprite>();  // La bonne façon de créer un unique_ptr
				mid->setTexture(groundGreenMidTexture);
				mid->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(std::move(mid));  // Utilise std::move pour transférer la propriété
				break;
			}
			case '3':
			{
				auto right = std::make_unique<Sprite>();  // La bonne façon de créer un unique_ptr
				right->setTexture(groundGreenRightTexture);
				right->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(std::move(right));  // Utilise std::move pour transférer la propriété
				break;
			}
			case 'P':
			{
				player->setPosPos((float)i * 32, (float)_z * 20);
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
	for (auto& ground : groundSprites) {
		window.draw(*ground);
	}
	player->draw(window);
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
