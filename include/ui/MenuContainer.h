#pragma once
#include "MenuComponent.h"
#include <vector>
#include <memory>
#include <SFML/Window/Event.hpp>
#include "ui/MenuTextItem.h"
#include <cfloat>

class MenuContainer : public MenuComponent {
public:
    void addComponent(std::unique_ptr<MenuComponent> component);

    void handleEvent(const sf::Event &event) override;

    void update() override;

    void render(sf::RenderTarget &target) override;

    void setPosition(const sf::Vector2f &position) override;

    [[nodiscard]] sf::FloatRect getBounds() const override;

    [[nodiscard]] sf::FloatRect getLocalBounds() const;

    void navigateUp();

    void navigateDown();

    void activateSelected() const;

    [[nodiscard]] size_t getSelectedIndex() const { return m_selectedIndex; }

    void setSelectedIndex(size_t index);

    [[nodiscard]] bool isComponentSelectable(size_t index) const;

private:
    std::vector<std::unique_ptr<MenuComponent> > m_components;
    size_t m_selectedIndex = 0;

private:
    void updateSelection() const;
};
