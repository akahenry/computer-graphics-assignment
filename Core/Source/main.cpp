#include "engine.hpp"
#include "window.hpp"
#include "GLFW/linmath.h"

int main()
{
    Engine engine;

    engine.Initialize();

    Window window = Window(800, 600, "test");

    while (!window.ShouldClose())
    {
        window.ClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        window.PollEvents();
    }

    // Fim do programa
    return 0;
}