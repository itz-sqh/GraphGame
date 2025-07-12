#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "FunctionPlotter/FunctionPlotter.h"
#include "GameConstants.h"
#include <memory>
#include <random>
#include <vector>
#include "Player.h"
#include "Obstacle.h"

class Game {
public:
    Game();
    void run();
    constexpr bool isRunning() const { return window->isOpen() && !gameOver; }

private:
    std::unique_ptr<sf::RenderWindow> window;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<Obstacle>> obstacles;
    bool gameOver = false;
    int currentPlayer = 0;
    std::string playerInput;
    std::unique_ptr<FunctionPlotter> plotter = nullptr;
    bool showingShot = false;
    sf::Clock shotClock;
    float shotDisplayTime;




    void initWindow();
    void initMap();
    void generateObstacles();
    void generatePlayers();
    void nextTurn();
    void fireExpression(const Expression& expr);
    void drawInputBox() const;
    void update();
    void render();
    void pollEvents();
};