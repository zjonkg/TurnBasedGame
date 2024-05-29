#include "GameOver.h"

// Constructor
GameOverState::GameOverState(sf::RenderWindow& window)
    : m_window(window) {
}

// Manejar la entrada del usuario
void GameOverState::handleInput() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                // Aquí puedes cambiar el estado a un nuevo juego o menú principal
                // m_stateManager.pushState(new MainMenuState(m_window, m_stateManager));
                // O simplemente salir del juego:
                m_window.close();
            }
        }
    }
}

// Actualizar lógica del juego
void GameOverState::update(float deltaTime) {
    // No hay lógica específica de actualización en el estado de Game Over
}

// Renderizar contenido en pantalla
void GameOverState::render() {
    m_window.clear();

    // Crear y configurar el texto de Game Over
    sf::Font font;
    if (!font.loadFromFile("Assets/Font/DePixelSchmal.ttf")) {
        std::cerr << "Error loading font\n";
    }

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(m_window.getSize().x / 2.0f - gameOverText.getGlobalBounds().width / 2.0f, m_window.getSize().y / 3.0f);

    sf::Text instructionText;
    instructionText.setFont(font);
    instructionText.setString("Press Enter to Exit");
    instructionText.setCharacterSize(30);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(m_window.getSize().x / 2.0f - instructionText.getGlobalBounds().width / 2.0f, m_window.getSize().y / 1.5f);

    // Dibujar el texto en la ventana
    m_window.draw(gameOverText);
    m_window.draw(instructionText);

    m_window.display();
}

// Implementación de getStateName
std::string GameOverState::getStateName() const {
    return "GameOverState";
}
