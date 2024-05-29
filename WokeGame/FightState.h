#ifndef FIGHTSTATE_H
#define FIGHTSTATE_H

#include <SFML/Graphics.hpp>

#include "State.h"
#include "GameState.h"
#include "StateManager.h"
#include "Player.h"
#include "Enemy.h"
#include <SFML/System.hpp>


class FightState : public State {
public:
    FightState(sf::RenderWindow& window, Player& player, Enemy& enemy, StateManager& stateManager);
    FightState(sf::RenderWindow& window, Player& player, BossEnemy& enemy, StateManager& stateManager);
    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    bool isEnemyDead();

    void setPlayerDead(bool playerD);

    void setEnemyDead(bool enemyD);

    bool isPlayerDead();

    std::string getStateName() const override;

    bool getBossState() const;


private:

    bool heavyAttackUsed = false;
    bool poisonAttackUsed = false;
    bool isBleeding = false;
    sf::RenderWindow& m_window;
    Player& m_player;
    Enemy& m_enemy;
    BossEnemy m_bossEnemy;
    GameState* m_gameState;
    StateManager m_stateManager;
    bool enemyDied = false;
    bool playerDied = false;  
    bool playerTurn;
    int maxHealthEnemy = m_enemy.getHp();
    int currentHealthEnemy;
    int contador = 0;
    int maxHealth = m_player.getHp();
    int currentHealthPlayer;
    sf::Vector2f initialPosition = m_player.getPosition();
    sf::Vector2f barSize;
    sf::RectangleShape healthBar, healthBarPlayer;
    sf::Font font;
    sf::Texture allBackground, plant;
    sf::Sprite grass, stone;
    bool isBoss = false;

    sf::Text playerActionText;
    sf::Text enemyActionText;
    sf::Text infoText;

    const int rows = 8;
    const int cols = 6;
    const int tileWidth = 48;
    const int tileHeight = 48;
    const int separation = 5;


    void playerAttack();
    void enemyAttack();
    void bossEnemyAttack();
};

#endif // FIGHTSTATE_H
