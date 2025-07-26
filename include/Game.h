#pragma once

#include<SFML/Graphics/RenderWindow.hpp>
#include"FunctionPlotter.h"
#include"GameConstants.h"
#include<memory>
#include<vector>
#include<queue>
#include"Rng.h"
#include"Geometry.h"
#include"Player.h"
#include"Obstacle.h"

class Game {
public:
    Game();

    void run();

    bool isRunning() const { return window->isOpen() && !gameOver; }

private:
    std::unique_ptr<sf::RenderWindow> window;
    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::shared_ptr<Obstacle>> obstacles;
    bool gameOver = false;
    std::queue<std::shared_ptr<Player>> playersQueue;
    std::string playerInput;
    std::unique_ptr<FunctionPlotter> plotter = nullptr;
    bool showingShot = false;
    sf::Clock shotClock;
    float shotDisplayTime;
    sf::Font inputTextFont;


    void initWindow();

    void initMap();

    void generateObstacles();

    void generatePlayers();

    void nextTurn();

    void fireExpression(const Expression &expr);

    void drawInputBox() const;

    void update();

    void render() const;

    void pollEvents();
};