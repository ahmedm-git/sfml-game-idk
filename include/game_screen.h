#pragma once


#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <memory>

#include "../include/screen.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "event_bus.h"
#include "spdlog/spdlog.h"


class GameScreen : public Screen {
private:
    std::shared_ptr<EventBus> bus;
    sf::RectangleShape background;

public:
    GameScreen(int width, int height, std::shared_ptr<EventBus> bus) : bus(bus) {
        background.setPosition(0.f, 0.f);
        background.setSize(sf::Vector2f(width, height));
        background.setFillColor(sf::Color::Black);
    }
    void handleInput(sf::Event event) override {}
    void update() override {};
    void draw(sf::RenderWindow &window) override {
        spdlog::debug("Drawing GameScreen");
        window.draw(background);
    }
};


