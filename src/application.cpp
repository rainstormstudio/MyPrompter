#include "application.hpp"

Application::Application(std::string input, double velocity) : velocity{velocity} {
    file.open(input);
    if (!file) {
        throw "Unable to open file: " + input;
        return;
    }
    gfx = new Graphics("Prompter", "./assets/tilesets/Vintl01.png", 16, 16, 0, "./assets/fonts/Monaco.ttf", 800, 40, 2, 80);
    event = new SDL_Event();
    running = true;
    pause = false;
    time = std::chrono::high_resolution_clock::now();
    index = -1;
}

bool Application::isRunning() const {
    return running;
}

void Application::update() {
    if (!pause) {
        if (index == -1) {
            index = 0;
            std::getline(file, line);
            std::getline(file, nextline);
            time = std::chrono::high_resolution_clock::now();
        }
        std::chrono::high_resolution_clock::time_point current;
        current = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> timespan = std::chrono::duration_cast<std::chrono::duration<double>>(current - time);
        if (timespan.count() >= velocity) {
            index ++;
            time = std::chrono::high_resolution_clock::now();
        }
        if (index >= line.length()) {
            index = 0;
            line = nextline;
            std::getline(file, nextline);
            time = std::chrono::high_resolution_clock::now();
        }
    } else {
        time = std::chrono::high_resolution_clock::now();
    }
}

void Application::render() {
    gfx->clear();
    std::string output = "";
    for (int i = index; i < line.length(); i ++) {
        output = output + line[i];
    }
    gfx->write(output, 0, 0);
    gfx->write(nextline, 0, 1, 255, 255, 255, 150);
    gfx->setBackColor(0, 200, 150, 255, 10, 0);
    gfx->render();
}

void Application::processInput() {
    while (SDL_PollEvent(event) != 0) {
        if (event->type == SDL_QUIT) {
            running = false;
        } else if (event->type == SDL_KEYDOWN) {
            if (event->key.keysym.sym == SDLK_a) {
                index = 0;
                time = std::chrono::high_resolution_clock::now();
            } else if (event->key.keysym.sym == SDLK_SPACE) {
                pause = !pause;
            } else if (event->key.keysym.sym == SDLK_d) {
                index ++;
                if (index > line.length()) {
                    index = 0;
                    line = nextline;
                    std::getline(file, nextline);
                }
                time = std::chrono::high_resolution_clock::now();
            }
        }
    }
}