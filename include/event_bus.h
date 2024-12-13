#pragma once


#include <functional>
#include <vector>
#include <any>


// Event wrapper to hold any type of event data
struct Event {
    enum Type {
        NEW_SCREEN,
        CLOSE_SCREEN
    };

    Type type;
    std::any data;
};


using Callback = std::function<void(Event)>;


// EventBus class with type-erased callbacks and event data
class EventBus {
private:
    std::vector<Callback> subscribers;

public:

    // Subscribe to events with a callback
    void subscribe(const Callback &callback) {
        subscribers.push_back(callback);
    }

    // Publish an event to all subscribers
    void publish(Event event) {
        for (const auto &subscriber : subscribers) {
            subscriber(event);
        }
    }
};
