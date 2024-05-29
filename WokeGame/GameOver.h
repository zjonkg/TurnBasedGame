#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "State.h"

class GameOverState : public State {
public:
    GameOverState(sf::RenderWindow& window);

    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    std::string getStateName() const override;

private:
    sf::RenderWindow& m_window;
};

