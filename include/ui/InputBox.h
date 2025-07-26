#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class InputBox {
public:
    InputBox();
    void draw(sf::RenderTarget& target, const std::string& text, sf::Color outlineColor);
private:
    sf::RectangleShape rect;
    sf::Font font;
};
