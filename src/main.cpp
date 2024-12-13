#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>
 
#include "game.h"
 

int main(int argc, char *argv[]) {
    // Initialize CLI11, handle args.
    CLI::App app("SFML game");
    std::string log_level;
    app.add_option(
        "--log-level",
        log_level,
        "Log level"
    )->default_val("INFO");

    int windowWidth = 1000, windowHeight = 1000;
    app.add_option(
        "--window-width",
        windowWidth,
        "Window width"
    )->default_val(1000);
    app.add_option(
        "--window-height",
        windowHeight,
        "Window height"
    )->default_val(1000);

    CLI11_PARSE(app, argc, argv);

    spdlog::set_level(spdlog::level::from_str(log_level));

    // Initialize the game.
    Game game = Game(windowWidth, windowHeight, new EventBus);

    return 0;
}

