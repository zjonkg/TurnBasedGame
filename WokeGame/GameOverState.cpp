#include "GameOverState.h"

GameOverState::GameOverState(sf::RenderWindow& window, StateManager& stateManager, bool playerWon):
	m_window(window), m_stateManager(stateManager), m_playerWon(playerWon)
{
    if (!font.loadFromFile("Assets/Font/DePixelSchmal.ttf")) {
        std::cerr << "Error loading font\n";
    }

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(m_playerWon ? sf::Color::Green : sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setString(m_playerWon ? "You Win!" : "Game Over");

    gameOverText.setPosition(m_window.getSize().x / 2.0f - gameOverText.getGlobalBounds().width / 2.0f, m_window.getSize().y / 3.0f);

    instructionText.setFont(font);
    instructionText.setCharacterSize(30);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setString("Press Enter to Continue");
    instructionText.setPosition(m_window.getSize().x / 2.0f - instructionText.getGlobalBounds().width / 2.0f, m_window.getSize().y / 1.5f);

}

void GameOverState::handleInput(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				window.close();
				iniciar();
			}
		}
	}
}

void GameOverState::update(float deltaTime)
{

}

void GameOverState::render(sf::RenderWindow& window)
{
	window.clear();
	window.draw(gameOverText);
	window.draw(instructionText);
	window.display();

}

std::string GameOverState::getStateName() const
{
	return "GameOverState";
}
