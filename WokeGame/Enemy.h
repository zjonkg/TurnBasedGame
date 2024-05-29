#pragma once
#include  <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"


class Enemy
{
protected:
	int hp;
	std::string name;
	int attack;
	sf::Sprite body;
	Animation animation;
	bool isTouched = false;
	bool isDied = false;

public:

	Enemy() : hp(0), attack(0), isTouched(false), isDied(false) {}
	Enemy(int pHp, std::string pName, int pAttack, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position);

	int getHp();

	int randomMultiplier();
	std::string getName();

	int getAttack();

	void setScale(int x, int y);

	bool getIsTouched();
	
	void setIsTouched(bool touched);

	void setHp(int php);

	void setName(std::string pname);

	void setAttack(int pattack);

	void Draw(sf::RenderWindow& window);

	void Update(float deltaTime);
	
	void setPosition(float x, float y);
	
	sf::Vector2f getPosition();

	void setDead();
	bool getDeadStatus();

	int receiveDamage(int damage);

	const sf::Sprite& getSprite() const;
};

