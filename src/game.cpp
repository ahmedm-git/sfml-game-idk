#include <any>
#include <memory>
#include <spdlog/spdlog.h>

#include "game.h"
#include "title_screen.h"


Game::Game(int windowWidth, int windowHeight, EventBus *bus) 
    : window(sf::VideoMode(windowWidth, windowHeight), "Test"), 
    bus(std::shared_ptr<EventBus>(bus)) {

    this->bus->subscribe([this, windowWidth, windowHeight](Event event) {
        if (event.type == Event::Type::NEW_SCREEN) {
            Screen *screen = std::any_cast<Screen *>(event.data);
            setActiveScreen(screen);
        }
    });

    this->bus->subscribe([this, windowWidth, windowHeight](Event event) {
        if (event.type == Event::Type::CLOSE_SCREEN) {
            spdlog::debug("User issued close screen event");
            closeActiveScreen();
        }
    });

    setActiveScreen(new TitleScreen(windowWidth, windowHeight, this->bus));

    while (window.isOpen()) {
        // Handle events.
        while (window.pollEvent(currentEvent)) {
            handleEvent(currentEvent);
        }

        display();
    }
}


void Game::display() {
    window.clear(sf::Color::White);
    if (getActiveScreen()) {
        getActiveScreen()->draw(this->window);
    } else {
        spdlog::debug("No active screen found, exiting...");
        exit(0);
    }
    window.display();
}


void Game::handleEvent(sf::Event &event) {
    switch (event.type) {
        case sf::Event::Closed:
            spdlog::debug("User issued close event");
            window.close();
            break;
        case sf::Event::Resized:
            if (event.type == sf::Event::Resized) {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            break;
        default:
            getActiveScreen()->handleInput(event);
            break;
    }
}


Game::~Game() {}

