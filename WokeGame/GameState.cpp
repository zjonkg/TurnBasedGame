#include "GameState.h"
#include <iostream>
#include <ctime> 

GameState::GameState(sf::RenderWindow& window)
    : m_window(window), fightState(false), currentEnemy(nullptr),
    player(&playerTexture, sf::Vector2u(4, 4), 0.3f, 80.0f, 200), bossEnemy(300, nameGenerator(), 10, 15, 3, &bossTexture, sf::Vector2u(6, 1), 0.3f, sf::Vector2f(0.0f, 0.0f)) {
    srand(static_cast<unsigned>(time(NULL)));

    if (!plant.loadFromFile("Assets/Texture/TX Plant.png")) {
        std::cerr << "Error loading plant texture\n";
    }

    if (!allBackground.loadFromFile("Assets/Texture/TX Tileset Grass.png")) {
        std::cerr << "Error loading background texture\n";
    }

    if (!playerTexture.loadFromFile("Assets/Texture/player.png")) {
        std::cerr << "Error loading player texture\n";
    }

    if (!enemyTexture.loadFromFile("Assets/Texture/enemyIdle.png")) {
        std::cerr << "Error loading enemy texture\n";
    }

    if (!bossTexture.loadFromFile("Assets/Texture/bossIdle.png")) {
        std::cerr << "Error loading enemy texture\n";
    }

    player = Player(&playerTexture, sf::Vector2u(4, 4), 0.3f, 80.0f, 200);
    bossEnemy = BossEnemy(300, nameGenerator(), 10, 30, 3, &bossTexture, sf::Vector2u(6, 1), 0.3f, sf::Vector2f(80.0f, 200.0f));

    tree.setTexture(plant);
    tree.setTextureRect(sf::IntRect(0, 0, 144, 172));

    treeTwo.setTexture(plant);
    treeTwo.setTextureRect(sf::IntRect(144, 0, 144, 172));

    grass.setTexture(allBackground);
    grass.setTextureRect(sf::IntRect(0, 0, 4 * 24, 4 * 24));
    grass.setScale(3.0f, 3.0f);

    stone.setTexture(allBackground);
    stone.setTextureRect(sf::IntRect(0, 120, 17, 24));
    stone.setScale(2.0f, 2.0f);

    setupPositions();
    spawnEnemies();
    setupBossEnemy();
}

void GameState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void GameState::update(float deltaTime) {
    player.Update(deltaTime);
    bossEnemy.Update(deltaTime);
    lastPlayerPosition = player.getPosition();

    for (auto& enemy : enemies) {
        enemy.Update(deltaTime);

        sf::FloatRect playerBounds = player.getSprite().getGlobalBounds();
        sf::FloatRect enemyBounds = enemy.getSprite().getGlobalBounds();
        sf::Vector2f playerCenter(playerBounds.left + playerBounds.width / 2, playerBounds.top + playerBounds.height / 2);
        sf::Vector2f enemyCenter(enemyBounds.left + enemyBounds.width / 2, enemyBounds.top + enemyBounds.height / 2);

        if (enemyBounds.contains(playerCenter) && std::abs(playerCenter.y - enemyCenter.y) < playerBounds.height / 2) {
            if (!enemy.getIsTouched()) {
                fightState = true;
                enemy.setIsTouched(true);
                currentEnemy = &enemy;  
                break; 
            }
        }
    }

    sf::FloatRect playerBounds = player.getSprite().getGlobalBounds();
    sf::FloatRect enemyBounds = bossEnemy.getSprite().getGlobalBounds();
    sf::Vector2f playerCenter(playerBounds.left + playerBounds.width / 2, playerBounds.top + playerBounds.height / 2);
    sf::Vector2f enemyCenter(enemyBounds.left + enemyBounds.width / 2, enemyBounds.top + enemyBounds.height / 2);

    if (enemyBounds.contains(playerCenter) && std::abs(playerCenter.y - enemyCenter.y) < playerBounds.height / 2) {
		if (!bossEnemy.getIsTouched()) {
			fightState = true;
            bossState = true;
			bossEnemy.setIsTouched(true);
			currentEnemy = &bossEnemy;
		}
	}


}

void GameState::render(sf::RenderWindow& window) {
    window.clear();

    
    for (int row = 0; row < rows - 5; ++row) {
        for (int col = 0; col < cols; ++col) {
            grass.setPosition(col * (tileWidth * 4), row * (tileHeight * 4));
            window.draw(grass);
        }
    }

   
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            stone.setPosition((col + 5) * (tileWidth + separation), (row + 2) * (tileHeight + separation));
            window.draw(stone);
        }
    }

    
    tree.setPosition(0.0f, 100.0f);
    window.draw(tree);
    treeTwo.setPosition(620.0f, 200.0f);
    window.draw(treeTwo);
    treeTwo.setPosition(120.0f, 300.0f);
    window.draw(treeTwo);
    tree.setPosition(650.0f, 60.0f);
    window.draw(tree);
    bossEnemy.Draw(window);
    
    for (auto& enemy : enemies) {
        enemy.Draw(window);
    }

    
    player.Draw(window);

    window.display();
}

std::string GameState::getStateName() const
{
    return "GameState";
}

bool GameState::getFightState() const {
    return fightState;
}

void GameState::setFightState(bool _fightState)
{
    fightState = _fightState;
}

void GameState::setBossState(bool _bossState)
{
	bossState = _bossState;
}

bool GameState::getBossState() const
{
    return bossState;
}

Player& GameState::getPlayer() {
    return player;
}

Enemy& GameState::getEnemy() {
    if (currentEnemy) {
        return *currentEnemy;
    }
}

BossEnemy& GameState::getBossEnemy()
{
    return bossEnemy;
}

void GameState::setupPositions() {
    positions.resize(rows, std::vector<Position>(cols));
    for (int row = 0; row < rows - 1; ++row) {
        for (int col = 0; col < cols; ++col) {
            int x = (col + 5) * (tileWidth + separation);
            int y = (row + 2) * (tileHeight + separation);
            positions[row][col] = { x, y };
        }
    }
}

void GameState::setupBossEnemy()
{
        int numberRandom = rand() % cols;
        for (int col = 0; col < cols; ++col) {
            if (numberRandom == col) {
                bossEnemy.setPosition(positions[6][col].x, positions[6][col].y + 50);
            }
        }
    }

void GameState::spawnEnemies() {
    for (int row = 1; row < rows; row += 2) {
        int numberRandom = rand() % cols;
        for (int col = 0; col < cols; ++col) {
            if (numberRandom == col ) {
                sf::Vector2f enemyPosition(positions[row][col].x, positions[row][col].y);
                enemies.emplace_back(150, nameGenerator(), 5, &enemyTexture, sf::Vector2u(5, 1), 0.3f, enemyPosition);
            }
        }
    }
    if (!enemies.empty()) {
        enemies.pop_back();
    }
}



std::string GameState::nameGenerator() {
    std::string names[] = { "Ramon", "Javier", "Carmen", "Roberto", "John" };
    int length = sizeof(names) / sizeof(names[0]);
    int number = rand() % length;
    return names[number];
}
