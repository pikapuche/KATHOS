#include "Map.hpp"

Map::Map() : statePlaying(StatePlaying::Boss) {
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

Map::~Map() {}

void Map::update(float deltaTime) {
    collision(deltaTime);

    for (auto& interactv : interactiblesVector) {
        interactv->updateProximity(player);
		if (interactv->getIsPlayerNear()) {
			interactv->interact(player);
		}
		//Interactibles Animation
		auto chest = std::dynamic_pointer_cast<Chest>(interactv);
		if (chest) {
			chest->updateAnimation(deltaTime);
		}
		auto key = std::dynamic_pointer_cast<Key>(interactv);
		if (key) {
			key->updateAnimation(deltaTime);
		}
    }

	collision(deltaTime);
}


void Map::collision(float deltaTime) {
	for (auto& ground : groundSprites) {
		//for(auto& player : players) 
		player->collision(*ground, deltaTime);

	//for (auto& door : interactiblesVector){
	// player->collision(*door, deltaTime);
	//}
		for(auto& enemy : enemies)
		enemy->collision(*ground, deltaTime);
		for(auto& boss : bosses)
		boss->collision(*ground, deltaTime);
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
			case 'P':
			{
				//auto player = std::make_unique<Player>();  // La bonne fa�on de cr�er un unique_ptr
				player->setPosPos((float)i * 32, (float)_z * 20);
				//players.push_back(move(player));
				break;
			}
			case 'G': //DASH GEM
			{
				auto gemme = std::make_unique<Gemme>((float)i * 32, (float)_z * 20, Gemme::GemmeState::DASH);
				gemmeSprites.push_back(std::move(gemme));
				break;
			}
			case 'S': //SPEED GEM
			{
				auto gemme = std::make_unique<Gemme>((float)i * 32, (float)_z * 20, Gemme::GemmeState::SPEED);
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
			case 'B':
			{
				auto boss = make_unique<Boss>();
				//boss = make_shared<Boss>();
				boss->setPos((float)i * 32, (float)_z * 20);
				bosses.push_back(move(boss));
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
				auto newCloud = make_unique<NuageTox>();
				newCloud->setPos((float)i * 32, (float)_z * 20 - 10);
				clouds.push_back(move(newCloud));
				break;
			}

			//INTERACTIBLES
			case 'K':
			{
				auto key = std::make_shared<Key>();  // Change to shared_ptrw Key();
				key->setPosPos((float)i * 32, (float)_z * 20 - 15);
				interactiblesVector.push_back(move(key));
				break;
			}
			case 'C':
			{
				auto chest = std::make_shared<Chest>();  // Change to shared_ptr
				chest->setPosPos((float)i * 32, (float)_z * 20 - 40);
				interactiblesVector.push_back(chest);
				break;
			}
			//DOOR WITHOUT BUTTON
			case 'D':
			{
				auto door = std::make_shared<Door>(false);
				door->setPosPos((float)i * 32, (float)_z * 20 - 45);
				interactiblesVector.push_back(door);
				break;
			}


			//DOOR WITH BUTTON
			case 'd':
			{
				auto door = std::make_shared<Door>(true);  // Change to shared_ptr
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
	if (statePlaying == StatePlaying::Boss) {
		ifstream Mapb("Assets/Map/Practice.txt");
		maps.push_back(&Mapb);
		string line;
		float z = 0;

		for (auto& mapBoss : maps) {
			monSwitch(*mapBoss, line, z);
		}
	}
}

void Map::draw(RenderWindow& window) {

	for (auto& ground : groundSprites) {
		window.draw(*ground);
	}
	for (auto& gemme : gemmeSprites) {
		if (!gemme->getGemTaken()) {
			window.draw(gemme->gemmeSprite);
		}
	}
	//for (auto& player : players)
		player->draw(window);

  for(auto& enemy : enemies)
		enemy->draw(window);

	for (auto& interactv : interactiblesVector) {
		if (!interactv->isDoor()) {  // Check if the object is NOT a door
			interactv->draw(window);
		}
	}

	for (auto& boss : bosses)
		boss->draw(window);

	for (auto& cloud : clouds)
		cloud->draw(window);
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

void Map::resetAll() {
	interactiblesVector.clear();
	gemmeSprites.clear();
	enemies.clear();
}

void Map::Win(RenderWindow& window)
{
	if (isWin) {
		RectangleShape winScreen(Vector2f(window.getSize().x, window.getSize().y));
		winScreen.setFillColor(Color(0, 0, 0, 150));
		window.draw(winScreen);

		Font font;
		if (!font.loadFromFile("Assets/Fonts/Minecraft.ttf")) {
			cout << "Erreur chargement police !" << endl;
		}

		Text winText;
		winText.setFont(font);
		winText.setString("WIN");
		winText.setCharacterSize(80);
		winText.setFillColor(Color::Yellow);
		winText.setStyle(Text::Bold);
		winText.setPosition((window.getSize().x - winText.getGlobalBounds().width) / 2, (window.getSize().y - winText.getGlobalBounds().height) / 2);

		window.draw(winText);
		return;
	}
}