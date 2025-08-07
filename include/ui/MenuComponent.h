#pragma once
#include <functional>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Event.hpp>

enum class MenuAction {
    None,
    Select,
    AdjustLeft,
    AdjustRight
};

class MenuComponent {
public:
    virtual ~MenuComponent() = default;

    virtual void handleEvent(const sf::Event &event) = 0;

    virtual void update() = 0;

    virtual void render(sf::RenderTarget &target) = 0;

    virtual void setPosition(const sf::Vector2f &position) = 0;

    [[nodiscard]] virtual sf::FloatRect getBounds() const = 0;

public:
    std::function<void()> onActivate;
    std::function<void(int)> onAdjust;
};
