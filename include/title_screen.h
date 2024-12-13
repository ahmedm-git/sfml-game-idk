#pragma once


#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

#include "event_bus.h"
#include "game_screen.h"
#include "screen.h"
#include "spdlog/spdlog.h"


class TitleScreen : public Screen {
private:
    std::shared_ptr<EventBus> bus;
    sf::RectangleShape background;
    sf::Font font;
    sf::Text title, startButton, quitButton;

public:
    TitleScreen(int width, int height, std::shared_ptr<EventBus> bus) : bus(bus) {
        background.setPosition(0.f, 0.f);
        background.setSize(sf::Vector2f(width, height));
        background.setFillColor(sf::Color::Black);

        font = sf::Font();
        font.loadFromFile("/home/ahmed/repos/ahmed-cpp/Hack-Regular.ttf");

        title.setString("Epic Game");
        title.setFont(font);
        title.setStyle(title.Bold);
        title.setFillColor(sf::Color::White);
        title.setCharacterSize(90);
        title.setPosition(width / 2 - title.getLocalBounds().width / 2, 50);

        startButton.setString("Start");
        startButton.setFont(font);
        startButton.setFillColor(sf::Color::White);
        startButton.setCharacterSize(40);
        startButton.setPosition(width * (1.f / 3.f) - startButton.getLocalBounds().width / 2, height * 0.75 - startButton.getLocalBounds().height);

        quitButton.setString("Quit");
        quitButton.setFont(font);
        quitButton.setFillColor(sf::Color::White);
        quitButton.setCharacterSize(40);
        quitButton.setPosition(width * (2.f / 3.f) - quitButton.getLocalBounds().width / 2, height * 0.75 - quitButton.getLocalBounds().height);
    }

    void handleInput(sf::Event event) override {
        // Handle start and quit.
        switch (event.type) {
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (startButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        spdlog::info("Start button clicked.");
                        this->bus->publish({ 
                            Event::Type::NEW_SCREEN,
                            static_cast<Screen *>(new GameScreen(background.getSize().x, background.getSize().y, bus)) 
                        });
                    } else if (quitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        spdlog::info("Quit button clicked.");
                        this->bus->publish({ 
                            Event::Type::CLOSE_SCREEN,
                            nullptr
                        });
                    }
                }
                break;
            case sf::Event::MouseMoved:
                if (startButton.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                    startButton.setFillColor(sf::Color::Cyan);
                } else {
                    startButton.setFillColor(sf::Color::White);
                }
                if (quitButton.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                    quitButton.setFillColor(sf::Color::Cyan);
                } else {
                    quitButton.setFillColor(sf::Color::White);
                }
                break;
            default:
                break;
        }
    }

    void update() override {};

    void draw(sf::RenderWindow &window) override {
        spdlog::debug("Drawing TitleScreen");
        window.draw(background);
        window.draw(title);
        window.draw(startButton);
        window.draw(quitButton);
    }
};


