#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include "State.h"
#include "Player.h"
#include "Enemy.h"
#include "GameState.h"
#include "StateManager.h"
#include <SFML/System.hpp>
#include "BossEnemy.h"


class GameState : public State {
public:
    GameState(sf::RenderWindow& window);
    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    std::string getStateName() const override;
    bool getFightState() const;
    void setFightState(bool _fightState);

    void setBossState(bool _bossState);

    bool getBossState() const;
    Player& getPlayer();
    Enemy& getEnemy();

    BossEnemy& getBossEnemy();

private:
    void setupPositions();

    void setupBossEnemy();
    void spawnEnemies();
    std::string nameGenerator();

    sf::RenderWindow& m_window;
    bool fightState;
    bool bossState = false;
    sf::Vector2f enemyPosition;
    std::vector<Enemy> enemies;
    Player player;
    BossEnemy bossEnemy;
    Enemy* currentEnemy;  

    sf::Texture allBackground, plant, playerTexture, enemyTexture, bossTexture;
    sf::Sprite tree, treeTwo, grass, stone;
    sf::Vector2f lastPlayerPosition;

    const int rows = 8;
    const int cols = 6;
    const int tileWidth = 48;
    const int tileHeight = 48;
    const int separation = 5;

    struct Position {
        int x;
        int y;
    };

    std::vector<std::vector<Position>> positions;
};

#endif // GAMESTATE_H
