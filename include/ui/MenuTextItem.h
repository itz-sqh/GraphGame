#pragma once
#include "MenuComponent.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <utility>

class MenuTextItem : public MenuComponent {
public:
    MenuTextItem(const sf::Font &font,
                 unsigned fontSize,
                 const std::string &text,
                 bool isSelectable = true,
                 bool isAdjustable = false);

    void handleEvent(const sf::Event &event) override;

    void update() override;

    void render(sf::RenderTarget &target) override;

    void setPosition(const sf::Vector2f &position) override;

    sf::FloatRect getBounds() const override;

    sf::FloatRect getLocalBounds() const;

    void setText(const std::string &text);

    void setTextProvider(std::function<std::string()> provider);

    void setSelected(bool selected);

    void setSelectable(bool selectable);

    void setAdjustable(bool adjustable);

    bool isSelectable() const { return m_selectable; }

private:
    sf::Text m_textItem;
    bool m_selectable;
    bool m_adjustable;
    bool m_isSelected = false;

    std::function<std::string()> textProvider;
};
