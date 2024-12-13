#pragma once


#include <SFML/Graphics.hpp>


class Screen {
public:
    virtual ~Screen() = default;

    virtual void handleInput(sf::Event event) = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};

