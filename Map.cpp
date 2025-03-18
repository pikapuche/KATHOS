#include "Map.hpp"

Map::Map() : mapState(MapState::PRACTICE) {
	groundYellowLeftTexture.loadFromFile("Assets/texture/Map/groundYellowLeft.png");
	groundYellowMidTexture.loadFromFile("Assets/texture/Map/groundYellowMid.png");
	groundYellowRightTexture.loadFromFile("Assets/texture/Map/groundYellowRight.png");
	groundRedLeftTexture.loadFromFile("Assets/texture/Map/groundRedLeft.png");
	groundRedMidTexture.loadFromFile("Assets/texture/Map/groundRedMid.png");
	groundRedRightTexture.loadFromFile("Assets/texture/Map/groundRedRight.png");
	groundGreenLeftTexture.loadFromFile("Assets/texture/Map/groundGreenLeft.png");
	groundGreenMidTexture.loadFromFile("Assets/texture/Map/groundGreenMid.png");
	groundGreenRightTexture.loadFromFile("Assets/texture/Map/groundGreenRight.png");

	//practiceTexture.loadFromFile("Assets/Map/practice.png");
	salle1Texture.loadFromFile("Assets/Map/salle1.png");
	salle2Texture.loadFromFile("Assets/Map/salle2.png");
	salle3Texture.loadFromFile("Assets/Map/salle3.png");
	salle4Texture.loadFromFile("Assets/Map/salle4.png");
	salle5Texture.loadFromFile("Assets/Map/salle5.png");
	salle6Texture.loadFromFile("Assets/Map/salle6.png");

	//practiceSprite.setTexture(practiceTexture);
	salle1Sprite.setTexture(salle1Texture);
	salle2Sprite.setTexture(salle2Texture);
	salle3Sprite.setTexture(salle3Texture);
	salle4Sprite.setTexture(salle4Texture);
	salle5Sprite.setTexture(salle5Texture);
	salle6Sprite.setTexture(salle6Texture);

}

Map::~Map() {}

void Map::update(float deltaTime) {
	collision(deltaTime);
}

void Map::clearMap() {
	maps.clear();
	groundSprites.clear();
	gemmeSprites.clear();
	enemies.clear();
	interactiblesVector.clear();
	tpShapeA.clear();
	tpShapeB.clear();
}

void Map::collision(float deltaTime) {
	for (auto& ground : groundSprites) {
		player->collision(*ground, deltaTime);
		for(auto& enemy : enemies)
		enemy->collision(*ground, deltaTime);
		boss->collision(*ground, deltaTime);
	}
	for (auto& tpA : tpShapeA) {
		if (player->getSprite().getGlobalBounds().intersects(tpA->getGlobalBounds())) {
			clearMap();
			switch (mapState)
			{	
			case Map::MapState::PRACTICE:
				mapState = MapState::SALLE1;
				break;
			case Map::MapState::SALLE1:
				mapState = MapState::SALLE2;
				break;
			case Map::MapState::SALLE2:
				mapState = MapState::SALLE3;
				break;
			case Map::MapState::SALLE3:
				mapState = MapState::SALLE4;
				break;
			case Map::MapState::SALLE4:
				mapState = MapState::SALLE5;
				break;
			case Map::MapState::SALLE5:
				mapState = MapState::SALLE6;
				break;
			default:
				break;
			}
			loadMap();
		}
	}
	for (auto& tpB : tpShapeB) {
		if (player->getSprite().getGlobalBounds().intersects(tpB->getGlobalBounds())) {
			clearMap();
			switch (mapState)
			{
			case Map::MapState::SALLE1:
				mapState = MapState::PRACTICE;
				break;
			case Map::MapState::SALLE2:
				mapState = MapState::SALLE1;
				break;
			case Map::MapState::SALLE3:
				mapState = MapState::SALLE2;
				break;
			case Map::MapState::SALLE4:
				mapState = MapState::SALLE3;
				break;
			case Map::MapState::SALLE5:
				mapState = MapState::SALLE4;
				break;
			case Map::MapState::SALLE6:
				mapState = MapState::SALLE5;
				break;
			default:
				break;
			}
			loadMap();
		}
	}
}

void Map::monSwitch(ifstream& _Map, string _line, int _z) {
	
	while (getline(_Map, _line)) {
		for (int i = 0; i < _line.size(); i++) {
			switch (_line[i]) { // tileValue
				cout << _line[i] << endl;
			case '1':
			{
				auto left = make_unique<Sprite>();  // La bonne fa�on de cr�er un unique_ptr
				left->setTexture(groundGreenLeftTexture);
				left->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(move(left));  // Utilise move pour transf�rer la propri�t�
				break;
			}
			case '2':
			{
				auto mid = make_unique<Sprite>();  // La bonne fa�on de cr�er un unique_ptr
				mid->setTexture(groundGreenMidTexture);
				mid->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(move(mid));  // Utilise move pour transf�rer la propri�t�
				break;
			}
			case '3':
			{
				auto right = std::make_unique<Sprite>();  // La bonne fa�on de cr�er un unique_ptr
				right->setTexture(groundGreenRightTexture);
				right->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(std::move(right));  // Utilise std::move pour transf�rer la propri�t�
				break;
			}
			case '4':
			{
				auto left = std::make_unique<Sprite>();  // La bonne fa�on de cr�er un unique_ptr
				left->setTexture(groundYellowLeftTexture);
				left->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(std::move(left));  // Utilise std::move pour transf�rer la propri�t�
				break;
			}
			case '5':
			{
				auto mid = std::make_unique<Sprite>();  // La bonne fa�on de cr�er un unique_ptr
				mid->setTexture(groundYellowMidTexture);
				mid->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(std::move(mid));  // Utilise std::move pour transf�rer la propri�t�
				break;
			}
			case '6':
			{
				auto right = std::make_unique<Sprite>();  // La bonne fa�on de cr�er un unique_ptr
				right->setTexture(groundYellowRightTexture);
				right->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(std::move(right));  // Utilise std::move pour transf�rer la propri�t�
				break;
			}
			case '7':
			{
				auto left = std::make_unique<Sprite>();  // La bonne fa�on de cr�er un unique_ptr
				left->setTexture(groundRedLeftTexture);
				left->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(std::move(left));  // Utilise std::move pour transf�rer la propri�t�
				break;
			}
			case '8':
			{
				auto mid = std::make_unique<Sprite>();  // La bonne fa�on de cr�er un unique_ptr
				mid->setTexture(groundRedMidTexture);
				mid->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(std::move(mid));  // Utilise std::move pour transf�rer la propri�t�
				break;
			}
			case '9':
			{
				auto right = std::make_unique<Sprite>();  // La bonne fa�on de cr�er un unique_ptr
				right->setTexture(groundRedRightTexture);
				right->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(std::move(right));  // Utilise std::move pour transf�rer la propri�t�
				break;
			}
			case'+': 
			{
				auto tpA = std::make_unique<RectangleShape>();
				tpA->setSize({ 32, 20 });
				tpA->setFillColor(Color::White);
				tpA->setPosition({ (float)i * 32, (float)_z * 20 });
				tpShapeA.push_back(std::move(tpA));
				break;
			}
			case'-':
			{
				auto tpB = std::make_unique<RectangleShape>();
				tpB->setSize({ 32, 20 });
				tpB->setFillColor(Color::White);
				tpB->setPosition({ (float)i * 32, (float)_z * 20 });
				tpShapeB.push_back(std::move(tpB));
				break;
			}
			case 'P':
			{
				player->setPosPos((float)i * 32, (float)_z * 20);
				break;
			}
			case 'G':
			{
				auto gemme = std::make_unique<Gemme>((float)i * 32, (float)_z * 20);
				gemme->gemmeSprite.setColor(Color::Green);
				gemmeSprites.push_back(std::move(gemme));
				break;
			}
			case 'g':
			{
				auto gemme = std::make_unique<Gemme>((float)i * 32, (float)_z * 20);
				gemme->gemmeSprite.setColor(Color::Red);
				gemmeSprites.push_back(std::move(gemme));
				break;
			}
			case 'I':
			{
				auto gemme = std::make_unique<Gemme>((float)i * 32, (float)_z * 20);
				gemme->gemmeSprite.setColor(Color::Blue);
				gemmeSprites.push_back(std::move(gemme));
				break;
			}
			case 'E':
			{
				auto newEnemy = make_unique<Enemy>();
				newEnemy->setPosPos((float)i * 32, (float)_z * 20);
				newEnemy->waypointOne.x = newEnemy->getPosPos().x;
				newEnemy->waypointOne.y = newEnemy->getPosPos().y;
				newEnemy->waypointTwo.x = newEnemy->getPosPos().x + 590;
				newEnemy->waypointTwo.y = newEnemy->getPosPos().y;
				newEnemy->enemyState = newEnemy->PATROLLER;
				enemies.push_back(move(newEnemy));
				break;
			}
			case 'A':
			{
				auto newEnemy = make_unique<Enemy>();
				newEnemy->setPosPos((float)i * 32, (float)_z * 20);
				newEnemy->waypointOne.x = newEnemy->getPosPos().x - 30;
				newEnemy->waypointOne.y = newEnemy->getPosPos().y;
				newEnemy->waypointTwo.x = newEnemy->getPosPos().x + 280;
				newEnemy->waypointTwo.y = newEnemy->getPosPos().y;
				newEnemy->enemyState = newEnemy->PATROLLER;
				enemies.push_back(move(newEnemy));
				break;
			}
			case 'C':
			{
				Chest* chest = new Chest();
				chest->setPosPos((float)i * 32, (float)_z * 32 - 25);
				interactiblesVector.push_back(move(chest));
				break;
			}
			case 'K':
			{
				Key* key = new Key();
				key->setPosPos((float)i * 32, (float)_z * 32 - 25);
				interactiblesVector.push_back(move(key));
				break;
			}
			case 'B':
			{
				boss->setPos((float)i * 32, (float)_z * 20);
				break;
			}
			case 'Q':
			{
				auto newEnemy = make_unique<Enemy>();
				newEnemy->setPosPos((float)i * 32, (float)_z * 20);
				newEnemy->waypointOne.x = newEnemy->getPosPos().x - 30;
				newEnemy->waypointOne.y = newEnemy->getPosPos().y;
				newEnemy->waypointTwo.x = newEnemy->getPosPos().x + 500;
				newEnemy->waypointTwo.y = newEnemy->getPosPos().y;
				newEnemy->enemyState = newEnemy->CHASER;
				enemies.push_back(move(newEnemy));
				break;
			}
			case 'T' : 
			{
				nuage->setPos((float)i * 32, (float)_z * 20 - 10);
				break;
			}
			}
		}
		_z++;
	}
}

void Map::loadMap() {
	if (mapState == MapState::PRACTICE) {
		ifstream Map0("Assets/Map/Practice.txt");
		maps.push_back(&Map0);
		string line;
		float z = 0;

		for (auto& mapPractice : maps) {
			monSwitch(*mapPractice, line, z);
		}
	}
	if (mapState == MapState::SALLE1) {
		ifstream Map1("Assets/Map/Salle1.txt");
		maps.push_back(&Map1);
		string line;
		float z = 0;

		for (auto& mapMonde1 : maps) {
			monSwitch(*mapMonde1, line, z);
		}
	}
	if (mapState == MapState::SALLE2) {
		ifstream Map2("Assets/Map/Salle2.txt");
		maps.push_back(&Map2);
		string line;
		float z = 0;
		for (auto& mapMonde2 : maps) {
			monSwitch(*mapMonde2, line, z);
		}
	}
	if (mapState == MapState::SALLE3) {
		ifstream Map3("Assets/Map/Salle3.txt");
		maps.push_back(&Map3);
		string line;
		float z = 0;
		for (auto& mapMonde3 : maps) {
			monSwitch(*mapMonde3, line, z);
		}
	}
	if (mapState == MapState::SALLE4) {
		ifstream Map4("Assets/Map/Salle4.txt");
		maps.push_back(&Map4);
		string line;
		float z = 0;
		for (auto& mapMonde4 : maps) {
			monSwitch(*mapMonde4, line, z);
		}
	}
	if (mapState == MapState::SALLE5) {
		ifstream Map5("Assets/Map/Salle5.txt");
		maps.push_back(&Map5);
		string line;
		float z = 0;
		for (auto& mapMonde5 : maps) {
			monSwitch(*mapMonde5, line, z);
		}
	}
	if (mapState == MapState::SALLE6) {
		ifstream Map6("Assets/Map/Salle6.txt");
		maps.push_back(&Map6);
		string line;
		float z = 0;
		for (auto& mapMonde6 : maps) {
			monSwitch(*mapMonde6, line, z);
		}
	}
}

void Map::draw(RenderWindow& window) {
	for (auto& tpA : tpShapeA) {
		window.draw(*tpA);
	}
	for (auto& tpB : tpShapeB) {
		window.draw(*tpB);
	}
	switch (mapState)
	{	
	case Map::MapState::PRACTICE:
		window.draw(salle5Sprite);
		break;
	case Map::MapState::SALLE1:
		window.draw(salle1Sprite);
		break;
	case Map::MapState::SALLE2:
		window.draw(salle2Sprite);
		break;
	case Map::MapState::SALLE3:
		window.draw(salle3Sprite);
		break;
	case Map::MapState::SALLE4:
		window.draw(salle4Sprite);
		break;
	case Map::MapState::SALLE5:
		window.draw(salle5Sprite);
		break;
	case Map::MapState::SALLE6:
		window.draw(salle6Sprite);
		break;
	default:
		break;
	}
	for (auto& ground : groundSprites) {
		window.draw(*ground);
	}
	for (auto& gemme : gemmeSprites) {
		window.draw(gemme->gemmeSprite);
	}

	player->draw(window);
	for(auto& enemy : enemies)
	enemy->draw(window);
	for (auto& interactv : interactiblesVector) {
		interactv->draw(window);
	}
	boss->draw(window);
	nuage->draw(window);
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