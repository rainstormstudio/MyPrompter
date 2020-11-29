#include "application.hpp"

#include <string>
#include <cmath>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Please specify a file name and the velocity!" << std::endl;
        return 1;
    }
    std::string filename = std::string(argv[1]);
    double v = std::stod(argv[2]);

    try {

    Application* app = new Application(filename, v);

    while (app->isRunning()) {
        app->update();

        app->render();

        app->processInput();
    }

    delete app;
    } catch (std::string &e) {
        std::cerr << e << std::endl;
    }

    return 0;
}