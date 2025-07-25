#include "Game.h"
#include"Rng.h"
#include <iostream>
#include "Geometry.h"
#include "ExpressionException.h"


Game::Game() : shotDisplayTime(GameConstants::SHOT_DISPLAY_TIME), inputTextFont("ARIAL.TTF") {
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
    playersQueue = std::queue<std::shared_ptr<Player>>();
    constexpr sf::Vector2u size = {GameConstants::WIDTH, GameConstants::HEIGHT};
    for (int i = 0; i < GameConstants::PLAYER_COUNT; i++) {
        bool placed = false;
        sf::Vector2f point;
        while (!placed) {
            point = {
                    Rng::getFloat(GameConstants::MIN_X, GameConstants::MAX_X),
                    Rng::getFloat(GameConstants::MIN_Y, GameConstants::MAX_Y)
            };
            placed = true;
            for (const auto &p: players) {
                if (Geometry::dist(point, p->getPosition()) <
                    GameConstants::DISTANCE_BETWEEN_PLAYERS)
                    placed = false;
            }

            if (std::min(static_cast<float>(size.x) - Geometry::mapToWindow(point, size,GameConstants::MIN_X, GameConstants::MAX_X, GameConstants::MIN_Y, GameConstants::MAX_Y).x,
                         Geometry::mapToWindow(point, size,GameConstants::MIN_X, GameConstants::MAX_X, GameConstants::MIN_Y, GameConstants::MAX_Y).x) <
                GameConstants::PLAYER_WIDTH_OFFSET ||
                std::min(static_cast<float>(size.y) - Geometry::mapToWindow(point, size,GameConstants::MIN_X, GameConstants::MAX_X, GameConstants::MIN_Y, GameConstants::MAX_Y).y,
                         Geometry::mapToWindow(point, size,GameConstants::MIN_X, GameConstants::MAX_X, GameConstants::MIN_Y, GameConstants::MAX_Y).y) <
                GameConstants::PLAYER_HEIGHT_OFFSET)
                placed = false;
        }
        players.push_back(
                std::make_shared<Player>(point, GameConstants::PLAYER_COLOR[i % GameConstants::PLAYER_COUNT]));
        playersQueue.push(players.back());
    }
}

void Game::generateObstacles() {
    obstacles.clear();
    constexpr sf::Vector2u size = {GameConstants::WIDTH, GameConstants::HEIGHT};
    for (int i = 0; i < GameConstants::OBSTACLE_COUNT; ++i) {
        bool placed = false;
        sf::Vector2f point;
        while (!placed) {
            point = {
                    Rng::getFloat(GameConstants::MIN_X, GameConstants::MAX_X),
                    Rng::getFloat(GameConstants::MIN_Y, GameConstants::MAX_Y)
            };
            placed = true;
            for (const auto &p: players) {
                if (Geometry::dist(point, p->getPosition()) <
                    GameConstants::DISTANCE_BETWEEN_PLAYER_AND_OBSTACLE)
                    placed = false;
            }
            for (const auto &o: obstacles) {
                if (Geometry::dist(point, o->getPosition()) <
                    GameConstants::DISTANCE_BETWEEN_OBSTACLES)
                    placed = false;
            }
        }
        obstacles.push_back(std::make_unique<Obstacle>(sf::Vector2f(point)));
    }
}

void Game::run() {
    if (!playersQueue.empty()) {
        playersQueue.front()->switchCurrent();
    }
    while (isRunning()) {
        pollEvents();
        update();
        render();
    }
}

void Game::pollEvents() {
    while (const auto event = window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window->close();
        }
        if (auto *keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (gameOver) {
                window->close();
            }

            if (!showingShot && !gameOver) {
                if (keyEvent->code == sf::Keyboard::Key::Enter && !playerInput.empty()) {
                    try {
                        Expression expr = ExpressionParser::parse(playerInput);
                        fireExpression(expr);
                    } catch (const ExpressionException &exception) {
                        std::cerr << exception.what() << std::endl;
                        playerInput.clear();
                    }
                } else if (keyEvent->code == sf::Keyboard::Key::Backspace) {
                    if (!playerInput.empty()) {
                        playerInput.pop_back();
                    }
                }
            }
        }

        if (auto *textEvent = event->getIf<sf::Event::TextEntered>()) {
            if (!showingShot && !gameOver && textEvent->unicode >= 32 && textEvent->unicode != 127) {
                if (playerInput.size() >= GameConstants::MAX_INPUT_SIZE) {
                    //TODO EXCEPTION
                } else {
                    playerInput += static_cast<char>(textEvent->unicode);

                }
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

void Game::render() const {
    window->clear(sf::Color::White);


    for (const auto &obstacle: obstacles) {
        obstacle->draw(*window);
    }

    if (showingShot) {
        plotter->draw(*window, obstacles, players, playersQueue.front()->getPosition());
    }

    for (const auto &player: players) {
        player->draw(*window);
    }

    drawInputBox();
    window->display();
}

void Game::fireExpression(const Expression &expr) {
    plotter->update(expr, playersQueue.front()->getColor());
    showingShot = true;
    shotClock.restart();
}

void Game::nextTurn() {

    const auto prevPlayer = playersQueue.front();
    prevPlayer->switchCurrent();
    playersQueue.pop();
    playersQueue.push(prevPlayer);

    while (!playersQueue.empty() && !playersQueue.front()->isAlive()) {
        playersQueue.pop();
    }
    const auto newPlayer = playersQueue.front();
    if (newPlayer == prevPlayer) {
        gameOver = true;
    }
    newPlayer->switchCurrent();

    playerInput.clear();
}

void Game::drawInputBox() const {
    sf::RectangleShape inputBox({400, 40});
    inputBox.setFillColor(sf::Color(255, 255, 255, 150));
    inputBox.setOutlineColor(playersQueue.front()->getColor());
    inputBox.setOutlineThickness(2.f);
    inputBox.setPosition({(GameConstants::WIDTH - 400.f) / 2, GameConstants::HEIGHT - 40});
    sf::Text text(inputTextFont, playerInput);
    text.setFillColor(sf::Color::Black);
    while (text.getGlobalBounds().size.x - inputBox.getSize().x >= -2)
        text.setCharacterSize(text.getCharacterSize() - 1);
    text.setOrigin(text.getGlobalBounds().size / 2.f + text.getLocalBounds().position);
    text.setPosition(
            {inputBox.getPosition().x + inputBox.getSize().x / 2.f,
             inputBox.getPosition().y + inputBox.getSize().y / 2.f}
    );
    window->draw(inputBox);
    window->draw(text);
}