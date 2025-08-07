#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../core/ConfigManager.h"
#include "core/GameConstants.h"
#include "objects/Projectile.h"


class InputBox {
public:
    InputBox() = default;

    explicit InputBox(const ConfigManager &config);

    void draw(sf::RenderTarget &target, const std::string &text, sf::Color outlineColor);

    void drawInactive(sf::RenderTarget &target, const std::string &text);

private:
    sf::RectangleShape m_rect;
    sf::Font m_font;
};
