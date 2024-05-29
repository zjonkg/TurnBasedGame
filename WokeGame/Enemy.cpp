#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Enemy.h"
#include <cstdlib>
#include <ctime>


Enemy::Enemy(int pHp, std::string pName, int pAttack, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position) :
    hp(pHp), name(pName), attack(pAttack), animation(texture, imageCount, switchTime)
{
    body.setTexture(*texture); 
    body.setPosition(position); 
}

int Enemy::getHp() {
    return hp;
}

int Enemy::randomMultiplier() {
    int multiplier = rand() % 3 + 1;
    return multiplier;
}


std::string Enemy::getName() {
    return name;
}

int Enemy::getAttack() {
    return attack;
}

void Enemy::setScale(int x, int y)
{
    body.setScale(x, y);
}

bool Enemy::getIsTouched()
{
    return isTouched;
}

void Enemy::setIsTouched(bool touched)
{
    isTouched = touched;
}

void Enemy::setHp(int php) {
    hp = php;
}

void Enemy::setName(std::string pname) {
    name = pname;
}

void Enemy::setAttack(int pattack) {
    attack = pattack;
}

void Enemy::Draw(sf::RenderWindow& window) {
    window.draw(body); 
}

void Enemy::Update(float deltaTime) {
    animation.Update(0, deltaTime); 
    body.setTextureRect(animation.uvRect); 
}

void Enemy::setPosition(float x, float y) {
    body.setPosition(x, y); 
}

int Enemy::receiveDamage(int damage)
 {
    hp -= damage;
    return hp;

}

sf::Vector2f Enemy::getPosition()
{
    return body.getPosition();
}

void Enemy::setDead()
{
    isDied = true;
}

bool Enemy::getDeadStatus()
{

    return isDied;
}

const sf::Sprite& Enemy::getSprite() const {
    return body; 
}

