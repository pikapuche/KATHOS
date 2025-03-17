#include "Gemme.hpp"

Gemme::Gemme(float _x, float _y) { 
	gemmeTexture.loadFromFile("Assets/gemme.png");
	gemmeSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	gemmeSprite.setTexture(gemmeTexture);
	gemmeSprite.setPosition(Vector2f(_x,_y));

}

void Gemme::animationGemme(float _deltaTime)
Vector2f Gemme::setPosition(float x, float y)
{
	animGemmeTime += _deltaTime;
	anim.y = 0;
	if (animGemmeTime > 0.12f) {
		anim.x++;
		//animGemmeTime = 0;
	}
	if (anim.x >= 1)
		anim.x = 0;
		gemmeSprite.setTextureRect(sf::IntRect(anim.x * 32, anim.y * 32, 32, 32));
		
	
}

void Gemme::interact(Player& player)
{


}

void Gemme::updateGemme(float _x, float _y, float _deltaTime)
{
	animationGemme(_deltaTime); 
	position.x = _x;
	position.y= _y;
	gemmeSprite.setPosition(position);
};