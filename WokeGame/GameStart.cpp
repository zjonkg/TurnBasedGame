#include "GameStart.h"
#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "GameState.h"
#include "FightState.h"
#include "GameOverState.h"
#include <iostream>
#include <ctime>

void iniciar()
{
        sf::RenderWindow window(sf::VideoMode(800, 600), "WokeGame");

        StateManager stateManager;
        stateManager.pushState(std::make_shared<GameState>(window));

        sf::Clock clock;
        float deltaTime = 0.0f;

        while (window.isOpen()) {
            deltaTime = clock.restart().asSeconds();

            State* currentState = stateManager.getCurrentState();
            if (currentState) {
                currentState->handleInput(window);
                currentState->update(deltaTime);
                currentState->render(window);

                // Dynamic cast to GameState to check if we need to switch to FightState
                GameState* gameState = dynamic_cast<GameState*>(currentState);
                if (gameState && gameState->getFightState() && !gameState->getBossState()) {
                    stateManager.pushState(std::make_shared<FightState>(window, gameState->getPlayer(), gameState->getEnemy(), stateManager));
                    gameState->setFightState(false);
                }

                if (gameState && gameState->getFightState() && gameState->getBossState()) {
                    stateManager.pushState(std::make_shared<FightState>(window, gameState->getPlayer(), gameState->getBossEnemy(), stateManager));
                    gameState->setBossState(false);
                    gameState->setFightState(false);
                }
            }

            FightState* fightState = dynamic_cast<FightState*>(currentState);
            if (fightState && fightState->isEnemyDead() && !fightState->isPlayerDead() && !fightState->getBossState()) {
                std::cout << "ALIVE" << std::endl;
                stateManager.popState();
            }

            if (fightState && fightState->isPlayerDead() && !fightState->isEnemyDead() ) {
                std::cout << "YOU DIED" << std::endl;
                stateManager.popState();
                State* currentState = stateManager.getCurrentState();
                stateManager.pushState(std::make_shared<GameOverState>(window, stateManager, false));
            }

            if (fightState && !fightState->isPlayerDead() && fightState->isEnemyDead() && fightState->getBossState()) {
                std::cout << "YOU WON" << std::endl;
                stateManager.popState();
                State* currentState = stateManager.getCurrentState();
                stateManager.pushState(std::make_shared<GameOverState>(window, stateManager, true));
            }

            if (stateManager.hasStateChanged()) {
                stateManager.setStateChanged(false);
            }


        }

    }

