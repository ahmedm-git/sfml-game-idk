#pragma once


#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>

#include "event_bus.h"
#include "screen.h"


class Game {
private:
    std::shared_ptr<EventBus> bus;

    sf::Event currentEvent;
    sf::RenderWindow window;

    std::stack<std::unique_ptr<Screen>> screenStack;

    bool running = true;
    int windowWidth, windowHeight;

public:
    Game(int windowWidth, int windowHeight, EventBus *bus);
    ~Game();

    void display();
    void handleEvent(sf::Event &);

    Screen *getActiveScreen() { return screenStack.top().get(); }
    void setActiveScreen(Screen *screen) { screenStack.push(std::unique_ptr<Screen>(screen)); }
    void closeActiveScreen() { screenStack.pop(); }
};

