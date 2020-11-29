#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "graphics.hpp"
#include <string>
#include <fstream>
#include <chrono>

class Application {
    Graphics* gfx;
    SDL_Event* event;
    bool running;
    std::ifstream file;
    double velocity;
    std::chrono::high_resolution_clock::time_point time;
    int index;
    std::string line;
    std::string nextline;
    bool pause;

public:
    Application(std::string input, double velocity);

    bool isRunning() const;
    void update();
    void render();
    void processInput();
};

#endif
