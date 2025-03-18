#include "Gemme.hpp"

Gemme::Gemme(float _x, float _y) : gemmeState(GemmeState::NADA) { 
	gemmeTexture.loadFromFile("Assets/gemme.png");
	gemmeSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	gemmeSprite.setTexture(gemmeTexture);
	gemmeSprite.setPosition(Vector2f(_x,_y));
}

void Gemme::animationGemme(float _deltaTime)
{
	animGemmeTime += _deltaTime;
	anim.y = 0;
	if (animGemmeTime > 0.12f) {
		gemmeSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
	}
	if (animGemmeTime >= 0.24f) {
		animGemmeTime = 0;
		gemmeSprite.setTextureRect(sf::IntRect(0,0, 32, 32));
	}

	if (Gemme::gemmeState == Gemme::GemmeState::SPRINT) {
		gemmeSprite.setColor(Color::Green);
	}
	if (Gemme::gemmeState == Gemme::GemmeState::DASH) {
		gemmeSprite.setColor(Color::Blue);
	}
	if (Gemme::gemmeState == Gemme::GemmeState::DOUBLEJUMP){
		gemmeSprite.setColor(Color::Red);
	}
	
}

//void Gemme::interact(Player& player)
//{
//
//}

void Gemme::updateGemme(float _deltaTime)
{
	animationGemme(_deltaTime); 
};