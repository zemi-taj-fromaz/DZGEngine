#include "app/app.h"

#include <iostream>
#include <memory>

std::unique_ptr<Scene> CreateScene();

int main() {
    dzg app;
    auto s = CreateScene();
    try {
        app.run(s);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}