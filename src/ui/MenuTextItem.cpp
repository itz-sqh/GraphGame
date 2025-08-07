#include "ui/MenuTextItem.h"

MenuTextItem::MenuTextItem(const sf::Font &font,
                           unsigned fontSize,
                           const std::string &text,
                           bool isSelectable,
                           bool isAdjustable)
    : m_textItem(font), m_selectable(isSelectable), m_adjustable(isAdjustable) {
    m_textItem.setCharacterSize(fontSize);
    m_textItem.setString(text);
    m_textItem.setFillColor(sf::Color::White);
    MenuTextItem::update();
}

void MenuTextItem::handleEvent(const sf::Event &event) {
    if (!m_selectable) return;

    if (auto keyEvent = event.getIf<sf::Event::KeyPressed>()) {
        if (keyEvent->code == sf::Keyboard::Key::Enter && onActivate) {
            onActivate();
        } else if (m_adjustable && onAdjust) {
            if (keyEvent->code == sf::Keyboard::Key::Left) {
                onAdjust(-1);
            } else if (keyEvent->code == sf::Keyboard::Key::Right) {
                onAdjust(1);
            }
        }
    }
}

void MenuTextItem::update() {
    if (textProvider) {
        m_textItem.setString(textProvider());
    }

    sf::FloatRect bounds = m_textItem.getLocalBounds();
    m_textItem.setOrigin(bounds.size / 2.f);
}

void MenuTextItem::render(sf::RenderTarget &target) {
    target.draw(m_textItem);
}

void MenuTextItem::setPosition(const sf::Vector2f &position) {
    m_textItem.setPosition(position);
}

sf::FloatRect MenuTextItem::getBounds() const {
    return m_textItem.getGlobalBounds();
}

sf::FloatRect MenuTextItem::getLocalBounds() const {
    return m_textItem.getLocalBounds();
}

void MenuTextItem::setText(const std::string &text) {
    m_textItem.setString(text);
}

void MenuTextItem::setTextProvider(std::function<std::string()> provider) {
    textProvider = std::move(provider);
}

void MenuTextItem::setSelected(bool selected) {
    m_isSelected = selected;
    if (!m_selectable) {
        m_textItem.setFillColor(sf::Color::White);
        return;
    }
    m_textItem.setFillColor(selected ? sf::Color::Red : sf::Color::White);
}

void MenuTextItem::setSelectable(bool selectable) {
    this->m_selectable = selectable;
    if (!selectable) setSelected(false);
}

void MenuTextItem::setAdjustable(bool adjustable) {
    this->m_adjustable = adjustable;
}
