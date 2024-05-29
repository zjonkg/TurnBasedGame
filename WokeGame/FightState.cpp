#include "FightState.h"

FightState::FightState(sf::RenderWindow& window, Player& player, Enemy& enemy, StateManager& stateManager)
    : m_window(window), m_player(player), m_enemy(enemy), playerTurn(true), m_stateManager(stateManager), playerDied(false), enemyDied(false) {

    if (!plant.loadFromFile("Assets/Texture/TX Plant.png")) {
        std::cerr << "Error loading plant texture\n";
    }

    if (!allBackground.loadFromFile("Assets/Texture/TX Tileset Grass.png")) {
        std::cerr << "Error loading background texture\n";
    }

    currentHealthEnemy = m_enemy.getHp();
    currentHealthPlayer = m_player.getHp();

    barSize = sf::Vector2f(140.f, 10.f);
    healthBar.setSize(barSize);
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setOutlineColor(sf::Color::Black);
    healthBar.setOutlineThickness(2);
    healthBar.setPosition(325, 65);

    healthBarPlayer.setSize(barSize);
    healthBarPlayer.setFillColor(sf::Color::Green);
    healthBarPlayer.setOutlineColor(sf::Color::Black);
    healthBarPlayer.setOutlineThickness(2);
    healthBarPlayer.setPosition(325, 440);

    grass.setTexture(allBackground);
    grass.setTextureRect(sf::IntRect(0, 0, 4 * 24, 4 * 24));
    grass.setScale(3.0f, 3.0f);

    m_enemy.setScale(4.0f, 4.0f);
    m_enemy.setPosition(300, 50);

    stone.setTexture(allBackground);
    stone.setTextureRect(sf::IntRect(0, 120, 17, 24));
    stone.setScale(2.0f, 2.0f);
    font.loadFromFile("Assets/Font/DePixelSchmal.ttf");

    infoText.setFont(font);
    infoText.setCharacterSize(24);
    infoText.setFillColor(sf::Color::Yellow);
    infoText.setPosition(275, 550);


    m_player.setInitialPosition(m_player.getPosition());


}

FightState::FightState(sf::RenderWindow& window, Player& player, BossEnemy& enemy, StateManager& stateManager)
    : m_window(window), m_player(player), m_enemy(enemy), playerTurn(true), m_stateManager(stateManager), playerDied(false), enemyDied(false), m_bossEnemy(enemy)
{

    if (!allBackground.loadFromFile("Assets/Texture/TX Tileset GrassBoss.png")) {
        std::cerr << "Error loading background texture\n";
    }

    currentHealthEnemy = m_enemy.getHp();
    currentHealthPlayer = m_player.getHp();

    barSize = sf::Vector2f(140.f, 10.f);
    healthBar.setSize(barSize);
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setOutlineColor(sf::Color::Black);
    healthBar.setOutlineThickness(2);
    healthBar.setPosition(325, 65);

    healthBarPlayer.setSize(barSize);
    healthBarPlayer.setFillColor(sf::Color::Green);
    healthBarPlayer.setOutlineColor(sf::Color::Black);
    healthBarPlayer.setOutlineThickness(2);
    healthBarPlayer.setPosition(325, 350);

    m_enemy.setScale(5.5f, 5.5f);
    m_enemy.setPosition(150, 60);

    grass.setTexture(allBackground);
    grass.setTextureRect(sf::IntRect(45 * 32, 0, 256, 256));

    stone.setTexture(allBackground);
	stone.setTextureRect(sf::IntRect(0, 26 * 32, 160, 160));
	stone.setScale(4.0f, 4.0f);

	font.loadFromFile("Assets/Font/DePixelSchmal.ttf");


    infoText.setFont(font);
    infoText.setCharacterSize(24);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(275, 550);


    m_player.setInitialPosition(m_player.getPosition());

    isBoss = true;
}




void FightState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (playerTurn && event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::A && !enemyDied && !playerDied) {
                playerAttack();
                playerTurn = false;
            }
        }
    }
}

void FightState::update(float deltaTime) {
    m_enemy.Update(deltaTime);
    m_player.Update(deltaTime);


    if (!playerTurn && !isBoss) {
        enemyAttack();
        playerTurn = true;
    }
    if (!playerTurn && isBoss) {
        
        bossEnemyAttack();

        if (isBleeding) {
            int damage = m_bossEnemy.getPoisonAttack();
            m_player.receiveDamage(damage);
            currentHealthPlayer = m_player.getHp();
            std::cout << "Sangrado: " << damage << std::endl;
        }
        
        
        playerTurn = true;
    }

    if (currentHealthEnemy <= 0 && contador == 0 && currentHealthPlayer > 0) {
        contador++;
        m_enemy.setDead();
        enemyDied = m_enemy.getDeadStatus();
        healthBar.setOutlineThickness(0);
        m_stateManager.setStateChanged(true);
    }

    if (currentHealthPlayer <= 0 && contador == 0 && currentHealthEnemy > 0) {
        contador++;
        m_player.setDead();
        playerDied = m_player.getDeadStatus( );
        healthBarPlayer.setOutlineThickness(0);
        m_stateManager.setStateChanged(true);
    }
}



void FightState::render(sf::RenderWindow& window) {
    window.clear();

    for (int row = 0; row < rows - 5; ++row) {
        for (int col = 0; col < cols; ++col) {
            grass.setPosition(col * (tileWidth * 4), row * (tileHeight * 4));
            stone.setPosition(col * (tileWidth * 4), row * (tileHeight * 4));
            window.draw(grass);
        }
    }


    m_player.setPosition(300, 400);
    m_player.setScale(4.0f, 4.0f);
    m_player.setRow(1);
   
    infoText.setString("(Press 'A' to Attack)");
    window.draw(infoText);

    float healthRatio = static_cast<float>(currentHealthEnemy) / maxHealthEnemy;
    healthBar.setSize(sf::Vector2f(barSize.x * healthRatio, barSize.y));

    float healthRatio2 = static_cast<float>(currentHealthPlayer) / maxHealth;
    healthBarPlayer.setSize(sf::Vector2f(barSize.x * healthRatio2, barSize.y));

    

        
    if (currentHealthEnemy <= 0) {
        m_enemy.setScale(0.0f, 0.0f);
        m_enemy.setPosition(300, 50);

        m_player.setScale(2.0f, 2.0f);
        m_player.setRow(3);
        m_player.setPosition(initialPosition.x, initialPosition.y);
    }

    window.draw(healthBar);

    window.draw(healthBarPlayer);
    m_enemy.Draw(window);
    m_player.Draw(window);
    window.display();
}

bool FightState::isEnemyDead()
{
    return enemyDied;
}

void FightState::setPlayerDead(bool playerD)
{
	playerDied = playerD;
}

void FightState::setEnemyDead(bool enemyD)
{
    enemyDied = enemyD;
}

bool FightState::isPlayerDead()
{
    return playerDied;
}

std::string FightState::getStateName() const
{
    return "FightState";
}

bool FightState::getBossState() const
{
    return isBoss;
}



void FightState::playerAttack() {
    int damage = 30;
    m_enemy.receiveDamage(damage);
    std::cout << "Enemy's HP: " << currentHealthEnemy << std::endl;
    currentHealthEnemy = m_enemy.getHp();
}

void FightState::enemyAttack() {
    int damage = m_enemy.getAttack() * m_enemy.randomMultiplier();
    std::cout << "Damage: " << damage << std::endl;
    m_player.receiveDamage(damage);
    currentHealthPlayer = m_player.getHp();
    std::cout << "Player's HP: " << currentHealthPlayer << std::endl;
}

void FightState::bossEnemyAttack() {
    if (!heavyAttackUsed && !poisonAttackUsed) {
        int random = rand() % 2; 
        if (random == 0) {

            int damage = m_bossEnemy.getHeavyAttack();
            
            m_player.receiveDamage(damage);
            currentHealthPlayer = m_player.getHp();
            std::cout << "Boss used Heavy Attack! Player's HP: " << currentHealthPlayer << std::endl;
            heavyAttackUsed = true; 
        }
        else {
            
            int damage = m_bossEnemy.getPoisonAttack();
            m_player.receiveDamage(damage);
            currentHealthPlayer = m_player.getHp();
            std::cout << "Boss used Bleed Attack! Player's HP: " << currentHealthPlayer << std::endl;
            m_player.setPoisoned();
            isBleeding = m_player.getPoisonedStatus();
            poisonAttackUsed = true; 
        }
    }
    else if (!heavyAttackUsed && poisonAttackUsed) {
       
        int damage = m_bossEnemy.getHeavyAttack();
        m_player.receiveDamage(damage);
        currentHealthPlayer = m_player.getHp();
        std::cout << "Boss used Heavy Attack! Player's HP: " << currentHealthPlayer << std::endl;
        heavyAttackUsed = true; 
    }
    else if (heavyAttackUsed && !poisonAttackUsed) {
        int damage = m_bossEnemy.getPoisonAttack();
        m_player.receiveDamage(damage);
        currentHealthPlayer = m_player.getHp();
        std::cout << "Boss used Bleed Attack! Player's HP: " << currentHealthPlayer << std::endl;
        poisonAttackUsed = true; 
        m_player.setPoisoned();
        isBleeding = m_player.getPoisonedStatus();
    }
    else {
        
        int damage = m_bossEnemy.getAttack ();
        m_player.receiveDamage(damage);
        currentHealthPlayer = m_player.getHp();
        std::cout << "Boss used Normal Attack! Player's HP: " << currentHealthPlayer << std::endl;
    }

}

