#include "Game.h"
#include"Rng.h"

#include <iostream>


Game::Game() : shotDisplayTime(GameConstants::SHOT_DISPLAY_TIME) {
    initWindow();
    initMap();
    plotter = std::make_unique<FunctionPlotter>(ExpressionParser::parse("0"), sf::Color::Red);
}

void Game::initWindow() {
    window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode({GameConstants::WIDTH, GameConstants::HEIGHT}),
        "Graph Game"
    );
    window->setFramerateLimit(60);
}
void Game::initMap() {
    generatePlayers();
    generateObstacles();
}
void Game::generatePlayers() {
    players.clear();
    sf::Vector2u size = {GameConstants::WIDTH, GameConstants::HEIGHT};
    for (int i = 0; i < GameConstants::PLAYER_COUNT; i++) {
        bool placed = false;
        sf::Vector2f point;
        while (!placed) {
            point = {
                Rng::getFloat(GameConstants::MIN_X, GameConstants::MAX_X),
                Rng::getFloat(GameConstants::MIN_Y, GameConstants::MAX_Y)
            };
            placed = true;
            for (const auto& p : players) {
                if (dist(mapToWindow(point,size),mapToWindow(p->getPosition(),size)) < GameConstants::DISTANCE_BETWEEN_PLAYERS)
                    placed = false;
            }
        }
        players.push_back(std::make_unique<Player>(point,
                    GameConstants::PLAYER_COLOR[i%GameConstants::PLAYER_COUNT]));
    }
}

void Game::generateObstacles() {
    obstacles.clear();
    sf::Vector2u size = {GameConstants::WIDTH,GameConstants::HEIGHT};
    for (int i = 0; i < GameConstants::OBSTACLE_COUNT; ++i) {
        bool placed = false;
        sf::Vector2f point;
        while (!placed) {
            point = {
                Rng::getFloat(GameConstants::MIN_X, GameConstants::MAX_X),
                Rng::getFloat(GameConstants::MIN_Y, GameConstants::MAX_Y)
            };
            placed = true;
            for (const auto& p : players) {
                if (dist(mapToWindow(point,size),mapToWindow(p->getPosition(),size)) < GameConstants::DISTANCE_BETWEEN_PLAYER_AND_OBSTACLE)
                    placed = false;
            }
            for (const auto& o : obstacles) {
                if (dist(mapToWindow(point,size),mapToWindow(o->getPosition(),size)) < GameConstants::DISTANCE_BETWEEN_OBSTACLES)
                    placed = false;
            }
        }
        obstacles.push_back(std::make_unique<Obstacle>(sf::Vector2f(point)));
    }
}
void Game::run() {
    while (isRunning()) {
        pollEvents();
        update();
        render();
    }
}
void Game::pollEvents() {
    while (auto event = window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window->close();
        }
        if (auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (gameOver) {
                window->close();
            }

            if (!showingShot && !gameOver) {
                if (keyEvent->code == sf::Keyboard::Key::Enter && !playerInput.empty()) {
                    try {
                        Expression expr = ExpressionParser::parse(playerInput);
                        fireExpression(expr);
                    } catch (sf::Exception exception) {
                        std::cerr << exception.what() << std::endl;
                        std::cerr << playerInput << std::endl;
                        playerInput.clear();
                    }
                }
                else if (keyEvent->code == sf::Keyboard::Key::Backspace) {
                    if (!playerInput.empty()) {
                        playerInput.pop_back();
                    }
                }
            }
        }

        if (auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
            if (!showingShot && !gameOver) {
                playerInput += static_cast<char>(textEvent->unicode);
            }
        }
    }
}

void Game::update() {
    if (showingShot) {
        if (shotClock.getElapsedTime().asSeconds() >= shotDisplayTime) {
            showingShot = false;
            nextTurn();
        }
    }
}

void Game::render() {
    window->clear(sf::Color::White);

    for (const auto& player : players) {
        player->draw(*window);
    }

    for (const auto& obstacle : obstacles) {
        obstacle->draw(*window);
    }

    if (showingShot) {
        plotter->draw(*window,players[currentPlayer]->getPosition());
    }

    drawInputBox();
    window->display();
}

void Game::fireExpression(const Expression& expr) {
    plotter->update(expr, players[currentPlayer]->getColor());
    showingShot = true;
    shotClock.restart();
}

void Game::nextTurn() {
    int startPlayer = currentPlayer;
    do {
        currentPlayer = (currentPlayer + 1) % players.size();
    } while (currentPlayer != startPlayer && !players[currentPlayer]->isAlive());

    int aliveCount = 0;
    for (const auto& player : players) {
        if (player->isAlive()) aliveCount++;
    }

    if (aliveCount == 5) {
        gameOver = true;
    }

    playerInput.clear();
}
void Game::drawInputBox() const {

}