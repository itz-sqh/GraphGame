    #pragma once
    #include "ExpressionParser/Expression.h"
    #include <SFML/Graphics.hpp>
    #include "CircleObject.h"
    #include"GameConstants.h"

    class Player : public CircleObject {
    public:
        Player(sf::Vector2f position, sf::Color color, float radius = GameConstants::PLAYER_RADIUS);

        void draw(sf::RenderTarget& target) const override;

        ~Player() override = default;

        [[nodiscard]] bool isAlive() const;
        [[nodiscard]] sf::Color getColor() const;
        void switchCurrent();

        bool getIsCurrent() const;

    private:
        bool gotHit = false;
        bool isCurrent = false;
        sf::Color color;
    };