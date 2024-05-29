#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int hp) :
    animation(texture, imageCount, switchTime), speed(speed), row(0), faceRight(true), moved(false), hp(hp)
{
    sprite.setTexture(*texture); 
    sprite.setScale(2.0f, 2.0f); 
    sprite.setPosition(230.0f, 80.0f);
    isDied = false;
}

void Player::HandleInput() {
    movement = sf::Vector2f(0.0f, 0.0f);

    if (!moved) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movement.x -= moveAmountX;
            row = 2;
            moved = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movement.x += moveAmountX;
            row = 3;
            moved = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            movement.y += moveAmountY;
            row = 0;
            moved = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            movement.y -= moveAmountY;
            row = 1;
            moved = true;
        }
    }
}
bool Player::getPoisonedStatus()
{
    return isPoisoned;
}
void Player::setRow(int _row) {
    row = _row;
}

bool Player::getDeadStatus()
{
    return isDied;
}

void Player::setDead()
{
    isDied = true;
}

void Player::Update(float deltaTime) {
    HandleInput();
    animation.Update(row, deltaTime); 
    sprite.setTextureRect(animation.uvRect); 
    positionX = std::round(sprite.getPosition().x);
    positionY = std::round(sprite.getPosition().y);

    if (positionX + movement.x < 220) {
        movement.x = 220 - positionX;
    }
    else if (positionX + movement.x > 500) {
        movement.x = 500 - positionX;
    }

    if (positionY + movement.y < 80) {
        movement.y = 80 - positionY;
    }
    else if (positionY + movement.y > 458) {
        movement.y = 458 - positionY;
    }

    sprite.move(movement); 

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        moved = false;
    }
}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(sprite); 
}

const sf::Sprite& Player::getSprite() const {
    return sprite; 
}

int Player::receiveDamage(int damage)
{
    hp -= damage;
    return hp;
}


sf::Vector2f Player::getPosition()
{
    return sprite.getPosition();
}

sf::Vector2f Player::getInitialPosition() const
{
    return initialPosition;
}

int Player::getHp()
{
    return hp;
}

void Player::setInitialPosition(sf::Vector2f position)
{
    initialPosition = position;
}


void Player::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void Player::setScale(int x, int y)
{
    sprite.setScale(x, y);
}

void Player::setPoisoned()
{
	isPoisoned = true;
}
