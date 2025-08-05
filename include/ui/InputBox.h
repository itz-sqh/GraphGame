#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "core/GameConstants.h"
#include "objects/Projectile.h"


class InputBox {
public:
    InputBox();

    void draw(sf::RenderTarget &target, const std::string &text, sf::Color outlineColor);

    void drawInactive(sf::RenderTarget &target, const std::string &text);

private:
    sf::RectangleShape rect;
    sf::Font font;
};
