#include "../../include/ui/InputBox.h"

#include "../../include/core/GameConstants.h"
#include "../../include/objects/Projectile.h"

InputBox::InputBox() {
    rect.setSize({400,40});
    rect.setFillColor(sf::Color(255,255,255,150));
    rect.setPosition({(GameConstants::WIDTH - 400.f) /2,GameConstants::HEIGHT-40.f});

    if (!font.openFromFile("resources/ARIAL.TTF")) {
        //TODO handle error
    }
}

void InputBox::draw(sf::RenderTarget &target, const std::string &text, sf::Color outlineColor) {
    rect.setOutlineColor(outlineColor);
    rect.setOutlineThickness(2.f);
    target.draw(rect);

    sf::Text textDisplay(font, text);

    textDisplay.setFillColor(sf::Color::Black);

    while (textDisplay.getGlobalBounds().size.x - rect.getSize().x >= -2)
        textDisplay.setCharacterSize(textDisplay.getCharacterSize()-1);

    textDisplay.setOrigin(textDisplay.getGlobalBounds().size / 2.f + textDisplay.getLocalBounds().position);
    textDisplay.setPosition(rect.getPosition() + rect.getSize()/2.f);

    target.draw(textDisplay);


    target.draw(textDisplay);
}

