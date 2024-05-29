#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "State.h"
#include "StateManager.h"
#include "GameStart.h"

class GameOverState : public State {
public:
    GameOverState(sf::RenderWindow& window, StateManager& stateManager, bool playerWon);

    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    std::string getStateName() const override;

private:
    sf::RenderWindow& m_window;
    StateManager& m_stateManager;
    bool m_playerWon;
    sf::Font font;
    sf::Text gameOverText;
    sf::Text instructionText;
};
