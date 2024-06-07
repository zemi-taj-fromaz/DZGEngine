#include "app/app.h"

#include <iostream>
#include <memory>
#include <Windows.h>
#include "MMSystem.h"


std::unique_ptr<Scene> CreateScene();

int main() {
    dzg app;
    auto s = CreateScene();

    try {

        PlaySound(TEXT("..\\resources\\music\\tetris.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
        app.run(s);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}