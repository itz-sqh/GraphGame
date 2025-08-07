#include "ui/MenuContainer.h"

void MenuContainer::addComponent(std::unique_ptr<MenuComponent> component) {
    m_components.push_back(std::move(component));
}

void MenuContainer::handleEvent(const sf::Event &event) {
    if (m_components.empty()) return;

    bool eventHandled = false;

    if (auto keyEvent = event.getIf<sf::Event::KeyPressed>()) {
        if (keyEvent->code == sf::Keyboard::Key::Up) {
            navigateUp();
            eventHandled = true;
        } else if (keyEvent->code == sf::Keyboard::Key::Down) {
            navigateDown();
            eventHandled = true;
        } else if (keyEvent->code == sf::Keyboard::Key::Enter) {
            activateSelected();
            eventHandled = true;
        }
    }

    // Only pass unhandled events to components
    if (!eventHandled) {
        m_components[m_selectedIndex]->handleEvent(event);
    }
}

void MenuContainer::update() {
    for (auto &component: m_components) {
        component->update();
    }
}

void MenuContainer::render(sf::RenderTarget &target) {
    for (auto &component: m_components) {
        component->render(target);
    }
}

void MenuContainer::setPosition(const sf::Vector2f &position) {
    float currentY = position.y;
    for (auto &component: m_components) {
        sf::FloatRect bounds = component->getBounds();
        component->setPosition({position.x, currentY});
        currentY += bounds.size.y + 30;
    }
}

sf::FloatRect MenuContainer::getBounds() const {
    if (m_components.empty()) return {};

    sf::Vector2f min(FLT_MAX, FLT_MAX);
    sf::Vector2f max(FLT_MIN, FLT_MIN);

    for (const auto &comp: m_components) {
        sf::FloatRect bounds = comp->getBounds();
        min.x = std::min(min.x, bounds.position.x);
        min.y = std::min(min.y, bounds.position.y);
        max.x = std::max(max.x, bounds.position.x + bounds.size.x);
        max.y = std::max(max.y, bounds.position.y + bounds.size.y);
    }

    return {min, max - min};
}

sf::FloatRect MenuContainer::getLocalBounds() const {
    return getBounds();
}

void MenuContainer::navigateUp() {
    if (m_components.empty()) return;

    size_t startIndex = m_selectedIndex;
    do {
        m_selectedIndex = (m_selectedIndex == 0) ? m_components.size() - 1 : m_selectedIndex - 1;
    } while (!isComponentSelectable(m_selectedIndex) && m_selectedIndex != startIndex);

    updateSelection();
}

void MenuContainer::navigateDown() {
    if (m_components.empty()) return;

    size_t startIndex = m_selectedIndex;
    do {
        m_selectedIndex = (m_selectedIndex + 1) % m_components.size();
    } while (!isComponentSelectable(m_selectedIndex) && m_selectedIndex != startIndex);

    updateSelection();
}

void MenuContainer::activateSelected() const {
    if (m_components[m_selectedIndex]->onActivate) {
        m_components[m_selectedIndex]->onActivate();
    }
}

void MenuContainer::setSelectedIndex(size_t index) {
    size_t newIndex = index;
    size_t startIndex = index;
    bool found = false;

    do {
        if (isComponentSelectable(newIndex)) {
            m_selectedIndex = newIndex;
            found = true;
            break;
        }
        newIndex = (newIndex + 1) % m_components.size();
    } while (newIndex != startIndex);

    if (found) {
        updateSelection();
    }
}

bool MenuContainer::isComponentSelectable(size_t index) const {
    if (auto item = dynamic_cast<MenuTextItem *>(m_components[index].get())) {
        return item->isSelectable();
    }
    return false;
}

void MenuContainer::updateSelection() const {
    for (size_t i = 0; i < m_components.size(); ++i) {
        if (auto item = dynamic_cast<MenuTextItem *>(m_components[i].get())) {
            item->setSelected(i == m_selectedIndex);
        }
    }
}
