#include "ui/InputBox.h"


InputBox::InputBox(const ConfigManager &config) {
    if (!m_font.openFromFile("resources/ARIAL.TTF")) {
        // TODO handle error
    }
    float width = static_cast<float>(config.getResolution().x);
    float height = static_cast<float>(config.getResolution().y);
    m_rect.setSize({width * 0.5f, height * 0.05f});
    m_rect.setFillColor(sf::Color(255, 255, 255, 150));
    m_rect.setPosition({(width - m_rect.getSize().x) / 2.f, height - m_rect.getSize().y});
}

void InputBox::drawInactive(sf::RenderTarget &target, const std::string &text) {
    m_rect.setFillColor(sf::Color(200, 200, 200, 150));
    draw(target, text, sf::Color(100, 100, 100));
}

void InputBox::draw(sf::RenderTarget &target, const std::string &text, sf::Color outlineColor) {
    m_rect.setOutlineColor(outlineColor);
    m_rect.setOutlineThickness(2.f);

    target.draw(m_rect);

    sf::Text textDisplay(m_font, text);

    textDisplay.setFillColor(sf::Color::Black);


    while (textDisplay.getGlobalBounds().size.x - m_rect.getSize().x >= -2)
        textDisplay.setCharacterSize(textDisplay.getCharacterSize() - 1);

    textDisplay.setOrigin(textDisplay.getGlobalBounds().size / 2.f + textDisplay.getLocalBounds().position);
    textDisplay.setPosition(m_rect.getPosition() + m_rect.getSize() / 2.f);


    target.draw(textDisplay);
}
