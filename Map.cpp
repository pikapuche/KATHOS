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

	practiceTexture.loadFromFile("Assets/Map/Practice.png");
	salle1Texture.loadFromFile("Assets/Map/Salle1.jpg");
	salle2Texture.loadFromFile("Assets/Map/Salle2.jpg");
	salle3Texture.loadFromFile("Assets/Map/Salle3.jpg");
	salle4Texture.loadFromFile("Assets/Map/Salle2.jpg"); 
	salle5Texture.loadFromFile("Assets/Map/Salle5.jpg"); 
	salle6Texture.loadFromFile("Assets/Map/Salle6.png");
	salle62Texture.loadFromFile("Assets/Map/Salle62.png");

	//practiceSprite.setTexture(practiceTexture);
	salle1Sprite.setTexture(salle1Texture);
	salle2Sprite.setTexture(salle2Texture);
	salle3Sprite.setTexture(salle3Texture);
	salle4Sprite.setTexture(salle4Texture); salle4Sprite.setScale(-1.f, 1.f); salle4Sprite.setPosition(1940, 0);
	salle5Sprite.setTexture(salle5Texture);
	salle6Sprite.setTexture(salle6Texture);
	salle62Sprite.setTexture(salle62Texture);
}

Map::~Map() {}

void Map::update(float deltaTime, sf::RenderWindow& window, Controller& controller) {
    for (auto& interactv : interactiblesVector) {
        interactv->updateProximity(player, window, controller);
		if (interactv->getIsPlayerNear()) {
			interactv->interact(player);
		}
		//Interactibles Animation
		auto chest = dynamic_pointer_cast<Chest>(interactv);
		if (chest) {
			chest->updateAnimation(deltaTime);
		}
		auto key = dynamic_pointer_cast<Key>(interactv);
		if (key) {
			key->updateAnimation(deltaTime);
		}
	}

	collision(deltaTime);
}

void Map::clearMap() {
	tpShapeB.clear();
	tpShapeA.clear();
	interactiblesVector.clear();
	gemmeSprites.clear();
	enemies.clear();
	bosses.clear();
	maps.clear();
	clouds.clear();
	groundSprites.clear();
	reinitilisePlayer();
}

void Map::reinitilisePlayer() {
	player->setIsTakeDash(false);
	player->setIsTakeJump(false);
	player->setIsTakeSpeed(false);
}

void Map::collision(float deltaTime) {
	for (auto& ground : groundSprites) {
		player->collision(*ground, deltaTime);

		for (auto& enemy : enemies)
			enemy->collision(*ground, deltaTime);
		for (auto& boss : bosses)
			boss->collision(*ground, deltaTime);
	}
	for (auto& tpA : tpShapeA) {
		if (player->getSprite().getGlobalBounds().intersects(tpA->getGlobalBounds())) {
			clearMap();
			reinitilisePlayer();
			switch (mapState)
			{
			case Map::MapState::PRACTICE:
				mapState = MapState::SALLE1;
				//reinitialiser le joueur
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
			reinitilisePlayer();
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
				//cout << _line[i] << endl;
			case '1': {
				auto left = make_unique<Sprite>();  // La bonne fa on de cr er un unique_ptr
				left->setTexture(groundGreenLeftTexture);
				left->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(move(left));  // Utilise move pour transf rer la propri t 
				break;
			}
			case '2': {
				auto mid = make_unique<Sprite>();  // La bonne fa on de cr er un unique_ptr
				mid->setTexture(groundGreenMidTexture);
				mid->setPosition({ (float)i * 32, (float)_z * 20 });
				if (mapState == MapState::SALLE6) {
					mid->setColor(Color::Transparent);
				}
				groundSprites.push_back(move(mid));  // Utilise move pour transf rer la propri t 
				break;
			}
			case '3': {
				auto right = make_unique<Sprite>();  // La bonne fa on de cr er un unique_ptr
				right->setTexture(groundGreenRightTexture);
				right->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(move(right));  // Utilise move pour transf rer la propri t 
				break;
			}
			case '4': {
				auto left = make_unique<Sprite>();  // La bonne fa on de cr er un unique_ptr
				left->setTexture(groundYellowLeftTexture);
				left->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(move(left));  // Utilise move pour transf rer la propri t 
				break;
			}
			case '5': {
				auto mid = make_unique<Sprite>();  // La bonne fa on de cr er un unique_ptr
				mid->setTexture(groundYellowMidTexture);
				mid->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(move(mid));  // Utilise move pour transf rer la propri t 
				break;
			}
			case '6': {
				auto right = make_unique<Sprite>();  // La bonne fa on de cr er un unique_ptr
				right->setTexture(groundYellowRightTexture);
				right->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(move(right));  // Utilise move pour transf rer la propri t 
				break;
			}
			case '7': {
				auto left = make_unique<Sprite>();  // La bonne fa on de cr er un unique_ptr
				left->setTexture(groundRedLeftTexture);
				left->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(move(left));  // Utilise move pour transf rer la propri t 
				break;
			}
			case '8': {
				auto mid = make_unique<Sprite>();  // La bonne fa on de cr er un unique_ptr
				mid->setTexture(groundRedMidTexture);
				mid->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(move(mid));  // Utilise move pour transf rer la propri t 
				break;
			}
			case '9': {
				auto right = make_unique<Sprite>();  // La bonne fa on de cr er un unique_ptr
				right->setTexture(groundRedRightTexture);
				right->setPosition({ (float)i * 32, (float)_z * 20 });
				groundSprites.push_back(move(right));  // Utilise move pour transf rer la propri t 
				break;
			}
			case'+': {
				auto tpA = make_unique<RectangleShape>();
				tpA->setSize({ 32, 20 });
				tpA->setFillColor(Color::White);
				tpA->setPosition({ (float)i * 32, (float)_z * 20 });
				tpShapeA.push_back(move(tpA));
				break;
			}
			case'-': {
				auto tpB = make_unique<RectangleShape>();
				tpB->setSize({ 32, 20 });
				tpB->setFillColor(Color::White);
				tpB->setPosition({ (float)i * 32, (float)_z * 20 });
				tpShapeB.push_back(move(tpB));
				break;
			}
			case 'P': {
				player->setPosPos((float)i * 32, (float)_z * 20);
				break;
			}
			case 'G': {
				auto gemme = make_unique<Gemme>((float)i * 32, (float)_z * 20, Gemme::GemmeState::DASH);
				gemmeSprites.push_back(move(gemme));
				break;
			}
			case 'S': {
				auto gemme = make_unique<Gemme>((float)i * 32, (float)_z * 20, Gemme::GemmeState::SPEED);
				gemmeSprites.push_back(move(gemme));
				break;
			}
			case 'J': //JUMP GEM
			{
				auto gemme = make_unique<Gemme>((float)i * 32, (float)_z * 20, Gemme::GemmeState::DOUBLEJUMP);
				gemmeSprites.push_back(move(gemme));
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
			case 'A': {
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
			case 'B': {
				auto boss = make_unique<Boss>();
				boss->setPos((float)i * 32, (float)_z * 20);
				bosses.push_back(move(boss));
				break;
			}
			case 'Q': {
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
			case 'T': {
				auto newCloud = make_unique<NuageTox>();
				newCloud->setPos((float)i * 32, (float)_z * 20 - 10);
				clouds.push_back(move(newCloud));
				break;
			}

					//INTERACTIBLES
			case 'K': {
				auto key = make_shared<Key>();  // Change to shared_ptrw Key();
				key->setPosPos((float)i * 32, (float)_z * 20 - 15);
				interactiblesVector.push_back(move(key));
				break;
			}
			case 'C': {
				auto chest = make_shared<Chest>();  // Change to shared_ptr
				chest->setPosPos((float)i * 32, (float)_z * 20 - 40);
				interactiblesVector.push_back(chest);
				break;
			}
					//DOOR WITHOUT BUTTON
			case 'D': {
				auto door = make_shared<Door>(false);
				door->setPosPos((float)i * 32, (float)_z * 20 - 45);
				interactiblesVector.push_back(door);
				break;
			}
					//DOOR WITH BUTTON
			case 'd': {
				auto door = make_shared<Door>(true);  // Change to shared_ptr
				door->setPosPos((float)i * 32, (float)_z * 20 - 40);
				interactiblesVector.push_back(door);
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
		player->setColliderMap(30, 1805);
		mapBoss = true;
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
		if (!gemme->getGemTaken()) {
			window.draw(gemme->gemmeSprite);
		}
	}

	player->draw(window);

	for (auto& enemy : enemies)
		enemy->draw(window);

	for (auto& boss : bosses)
		boss->draw(window);

	for (auto& cloud : clouds)
		cloud->draw(window);

	/////////////////////////////////////////////////////// c'est quoi la diff ??? ca sert a quoi ???

	if (mapState == MapState::SALLE6){window.draw(salle62Sprite);}

	for (auto& interactv : interactiblesVector) {
		if (!interactv->isDoor()) {  // Check if the object is NOT a door
			interactv->draw(window);
			interactv->drawInspectGUI(window);
		}
	}
	for (auto& interactv : interactiblesVector) {
		if (interactv->isDoor()) {  // Check if the object is a door
			interactv->draw(window);
			interactv->drawInspectGUI(window);
		}
	}
}