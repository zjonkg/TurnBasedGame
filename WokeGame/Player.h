#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int hp);
    Player() : hp(0), isDied(false) {}
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
    const sf::Sprite& getSprite() const;
    int receiveDamage(int damage);
    sf::Vector2f getPosition();
    sf::Vector2f getInitialPosition() const;
    int getHp();
    void setInitialPosition(sf::Vector2f position);
    void setPosition(float x, float y);
    void setScale(int x, int y);

    void setPoisoned();

    bool getPoisonedStatus();
    void setRow(int _row);

    bool getDeadStatus();

    void setDead();

    

private: 
    sf::Vector2f initialPosition;
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f movement;
    int hp;
    bool isPoisoned;
    float speed = 100.0f;
    int row;
    bool faceRight;
    int positionX;
    int positionY;
    bool isDied = false;
    Animation animation;

    bool moved = false;
    float moveAmountX = 55.0f; 
    float moveAmountY = 53.2f;

    void HandleInput();
};

